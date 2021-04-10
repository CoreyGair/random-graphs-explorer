#include "ArgProcessor.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>

// Possible args:

// -m / --model : random graph model : ErdosRenyi(num nodes = n, prob = p)

// -n / --numgraphs : number of graphs to sample : positive integer

// -s / --seed : rng seed : integer

// -t / --threads : num threads : positive int

// Statistics options : 
//      -d / --degree
//      -D / --diameter
//      -B / --betweencentrality
//      -c / --components
//      -C / --clustering
//      -k / --degeneracy

int ArgProcessor::Process(int argc, char* argv[])
{
    bool has_model = false;
    bool has_count = false;
    for(int i = 1; i < argc; ++i)
    {
        std::string arg (argv[i]);

        if (arg == "-m" || arg == "--model")
        {
            has_model = true;
            std::string model_name (argv[++i]);

            if (model_name == "erdosrenyi")
            {
                ErdosOpts* erdos_opts = new ErdosOpts();
                opts = erdos_opts;

                try
                {
                    int n = std::stoi(argv[++i]);
                    if (n < 1)
                    {
                        std::cout << "Positive node count required for Erdos-Renyi model" << std::endl;
                        return 1;
                    }
                    erdos_opts->n = n;

                    double p = std::stod(argv[++i]);
                    if (p < 0 || p > 1)
                    {
                        std::cout << "Invalid p for Erdos-Renyi model (p in [0,1] required)" << std::endl;
                        return 1;
                    }
                    erdos_opts->p = p;
                }
                catch (std::invalid_argument e)
                {
                    std::cout<<"Invalid argument for Erdos-Renyi model"<<std::endl;
                    return 1;
                }
            }
            else if (model_name == "wattsstrogatz")
            {
                WattsOpts* watts_opts = new WattsOpts();
                opts = watts_opts;

                try
                {
                    int n = std::stoi(argv[++i]);
                    if (n < 2)
                    {
                        std::cout << "Greater than 1 node count N required for Watts-Strogatz model" << std::endl;
                        return 1;
                    }
                    watts_opts->n = n;

                    int k = std::stoi(argv[++i]);
                    if (k > n)
                    {
                        std::cout << "Initial edge count K must be less than the node count N for Watts-Strogatz model" << std::endl;
                        return 1;
                    }
                    watts_opts->k = k;

                    double b = std::stod(argv[++i]);
                    if (b < 0 || b > 1)
                    {
                        std::cout << "Invalid beta for Watts-Strogatz model (beta in [0,1] required)" << std::endl;
                        return 1;
                    }
                    watts_opts->b = b;
                }
                catch (std::invalid_argument e)
                {
                    std::cout<<"Invalid argument for Watts-Strogatz model"<<std::endl;
                    return 1;
                }
            }
            else if (model_name == "barabasialbert")
            {
                BarabasiOpts* barabasi_opts = new BarabasiOpts();
                opts = barabasi_opts;

                try
                {
                    int n_init = std::stoi(argv[++i]);
                    if (n_init < 1)
                    {
                        std::cout << "Positive initial node count required for Barabási–Albert model" << std::endl;
                        return 1;
                    }
                    barabasi_opts->n_init = n_init;

                    int n_add = std::stoi(argv[++i]);
                    if (n_add < 1)
                    {
                        std::cout << "Positive additional node count required for Barabási–Albert model" << std::endl;
                        return 1;
                    }
                    barabasi_opts->n_add = n_add;

                    double m_conn = std::stod(argv[++i]);
                    if (m_conn < 1)
                    {
                        std::cout << "Positive additional node degree required for Barabási–Albert model" << std::endl;
                        return 1;
                    }
                    if (m_conn > n_init)
                    {
                        std::cout << "Additional node degree must be less than the initial node count for Barabási–Albert model" << std::endl;
                        return 1;
                    }
                    barabasi_opts->m_new_conn = m_conn;
                }
                catch (std::invalid_argument e)
                {
                    std::cout<<"Invalid argument for Watts-Strogatz model"<<std::endl;
                    return 1;
                }
            }
            else 
            {
                std::cout<<"Invalid generator name"<<std::endl;
                return 1;
            }
        }
        else if (arg == "-n" || arg == "--numgraphs")
        {
            has_count=true;
            try
            {
                int count = std::stoi(argv[++i]);
                if (count < 1)
                {
                    std::cout << "Positive graph count required" << std::endl;
                    return 1;
                }
                opts->num_graphs = count;
            }
            catch (std::invalid_argument e)
            {
                std::cout<<"Invalid graph count"<<std::endl;
                return 1;
            }
        }
        else if (arg == "-s" || arg == "--seed")
        {
            try
            {
                seed = std::stoi(argv[++i]);
                has_seed = true;
            }
            catch (std::invalid_argument e)
            {
                std::cout<<"Invalid integer seed"<<std::endl;
                return 1;
            }
        }
        else if(arg == "-t" || arg == "--threads")
        {
            try
            {
                threads = std::stoi(argv[++i]);
                if (threads < 1)
                {
                    std::cout << "Positive thread count required" << std::endl;
                    return 1;
                }
                has_threads = true;
            }
            catch (std::invalid_argument e)
            {
                std::cout<<"Invalid integer threads"<<std::endl;
                return 1;
            }
        }
        else if(arg == "-d" || arg == "--degree") statistics |= DEGREE;
        else if(arg == "-D" || arg == "--diameter") statistics |= DIAMETER;
        else if(arg == "-B" || arg == "--betweencentrality") statistics |= BTWN_CENT;
        else if(arg == "-c" || arg == "--components") statistics |= COMPONENTS;
        else if(arg == "-C" || arg == "--clustering") statistics |= GLOB_CLUSTER;
        else if(arg == "-k" || arg == "--degeneracy") statistics |= DEGENERACY;
        else if(arg == "-h" || arg == "--help")
        {
            // Print help information, then quit
            // dont know how to do this better, maybe a text file

            std::cout<<"\nUsage:\n\n";

            std::cout<<"\t./random-graphs-explorer [generation options] [statistics]\n\n";

            std::cout<<"Required generation options: model, numgraphs\n\n";

            std::cout<<"Generation options:\n";

            std::cout   <<std::setw(32)<<std::left<<"-m, --model [name] [params]"
                        <<std::setw(1)<<std::left<<"= "<<"random graph model to use, along with parameters\n";
            std::cout   <<std::setw(32)<<std::left<<"-n, --numgraphs"
                        <<std::setw(1)<<std::left<<"= "<<"number of graphs to generate\n";
            std::cout   <<std::setw(32)<<std::left<<"-s, --seed"
                        <<std::setw(1)<<std::left<<"= "<<"seed for random generaton (chosen randomly if not present)\n";
            std::cout   <<std::setw(32)<<std::left<<"-t, --threads"
                        <<std::setw(1)<<std::left<<"= "<<"number of threads to use (1 if not present)\n";

            std::cout<<"\nRequired: at least one statistic to process\n\n";

            std::cout<<"Statistics:\n";
            
            std::cout   <<std::setw(32)<<std::left<<"-d, --degree"
                        <<std::setw(1)<<std::left<<"= "<<"vertex degree\n";
            std::cout   <<std::setw(32)<<std::left<<"-D, --diameter"
                        <<std::setw(1)<<std::left<<"= "<<"graph diameter\n";
            std::cout   <<std::setw(32)<<std::left<<"-B, --betweencentrality"
                        <<std::setw(1)<<std::left<<"= "<<"vertex betweenness centrality\n";
            std::cout   <<std::setw(32)<<std::left<<"-c, --components"
                        <<std::setw(1)<<std::left<<"= "<<"count of connected components in graph\n";
            std::cout   <<std::setw(32)<<std::left<<"-C, --clustering"
                        <<std::setw(1)<<std::left<<"= "<<"global clustering coefficient, ratio of closed vertex triplets to all vertex triplets\n";
            std::cout   <<std::setw(32)<<std::left<<"-k, --degeneracy"
                        <<std::setw(1)<<std::left<<"= "<<"degeneracy of graph, smallest k such that the graph is k-degenerate\n";

            std::cout<<"\n"<<std::setw(32)<<std::left<<"-h,--help"<<std::setw(1)<<std::left<<"= "<<"outputs usage info, then quits\n";

            std::cout<<std::endl;
            return 2;
        }
        else
        {
            std::cout<<"Unrecognised argument " << arg << std::endl;
            return 1;
        }
    }

    if (!has_model)
    {
        std::cout<<"Missing model option"<<std::endl;
        return 1;
    }
    if (!has_count)
    {
        std::cout<<"Missing numgraphs option"<<std::endl;
        return 1;
    }
    if (!statistics)
    {
        std::cout<<"Missing model option"<<std::endl;
        return 1;
    }

    return 0;
}