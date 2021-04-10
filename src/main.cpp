#include "ArgProcessor.h"

#include "Generators/Generators.h"
#include "Generators/GeneratorCreator.h"

#include "Benchmarking/Stopwatch.h"

#include "JobSystem/JobQueue.h"

#include "Statistics/Statistics.h"

#include "Plotter.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

class Graph;

int main(int argc, char* argv[])
{

    // Process command line args
    ArgProcessor args;

    int res = args.Process(argc, argv);
    
    if (res)
    {   
        if (res == 2) return 0;
        std::cout << "Encountered an error parsing CLA's. Use '--help' for help" << std::endl;
        return 1;
    }
    
    // Create correct graph generator
    GenerationOpts* opts = args.GetOpts();

    std::random_device r;

    int seed = (args.HasSeed()) ? args.GetSeed() : r();

    GraphGenerator* gen = GeneratorCreator::CreateGenerator(opts, seed);
    if (gen == nullptr)
    {
        std::cout << "Couldn't find correct graph generator" << std::flush;
        return 1;
    }

    int max_node_count = gen->GetMaxSize();

    // Generate graphs
    Stopwatch sw;

    std::vector<Graph*>& graphs = gen->GenerateGraphs(opts->num_graphs);

    std::cout<<"Generated "<<opts->num_graphs<<" graphs in ";
    sw.PrintElapsedTime();

    // Create statistic calc objects
    std::vector<IStatisticCalculator*> stats;

    int stat_flags = args.GetStatistics();

    if (stat_flags & DEGREE) stats.push_back(new DegreeCalculator());
    if (stat_flags & DIAMETER) stats.push_back(new DiameterCalculator());
    if (stat_flags & BTWN_CENT) stats.push_back(new BetweenCentCalculator());
    if (stat_flags & COMPONENTS) stats.push_back(new ComponentCountCalculator());
    if (stat_flags & GLOB_CLUSTER) stats.push_back(new GlobalClusterCalculator());
    if (stat_flags & DEGENERACY) stats.push_back(new DegeneracyCalculator());

    // Split graph vector almost-equally over the number of threads
    int thread_count = (args.HasThreads()) ? args.GetThreads() : 1;

    std::vector<std::vector<Graph*>::iterator> thread_start_positions;

    int job_count = thread_count;
    int graphs_per_thread_base = graphs.size() / thread_count;
    int remainder = graphs.size() % thread_count;
    if (graphs_per_thread_base < 1) 
    {
        graphs_per_thread_base = 1;
        remainder = 0;
        job_count = graphs.size();
    }

    thread_start_positions.push_back(graphs.begin());
    for(int i = 1; i < job_count; ++i)
    {
        thread_start_positions.push_back(thread_start_positions.back() + graphs_per_thread_base + ((i < remainder + 1 && i > 0) ? 1 : 0));
    }

    // Add jobs to job queue
    JobQueue jq;

    for(auto stat = stats.begin(); stat != stats.end(); ++stat)
    {
        for(auto start_pos_it = thread_start_positions.begin(); start_pos_it != thread_start_positions.end(); ++start_pos_it)
        {
            auto end_pos_it = (start_pos_it+1);
            auto end_pos = (end_pos_it == thread_start_positions.end()) ? graphs.end() : *end_pos_it;
            jq.EnqueueJob([=]{ (*stat)->ThreadRun(*start_pos_it, end_pos); });
        }
    }

    // Process all the jobs
    sw.Reset();
    
    jq.ProcessAllJobs(thread_count);

    std::cout<<"Completed all jobs in ";
    sw.PrintElapsedTime();

    // Get string name of graph model (used for graph titles)
    std::string model_name (gen->GetName());

    // Plot data from stat objects
    auto stat_it = stats.begin();

    for(auto stat_it = stats.begin(); stat_it != stats.end(); ++stat_it)
    {
        IStatisticCalculator* stat = *stat_it;

        Plotter::PlotStat(stat, model_name);
    }
}