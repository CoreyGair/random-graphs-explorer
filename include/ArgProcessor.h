#pragma once

#include "Statistics/StatisticDefines.h"

class GenerationOpts;

class ArgProcessor
{
    public:
        int Process(int argc, char* argv[]);

        GenerationOpts* GetOpts() { return opts; }
        int GetStatistics() { return statistics; }
        int GetSeed() { return seed; }
        bool HasSeed() { return has_seed; }
        int GetThreads() { return threads; }
        bool HasThreads() { return has_threads; }

    private:
        // Generation
        GenerationOpts* opts = nullptr;
        int statistics = 0;
        int seed;
        bool has_seed = false;
        int threads;
        bool has_threads = false;
};

enum GenerationModel { None, ErdosRenyi, WattsStrogatz, BarabasiAlbert };

struct GenerationOpts
{
    public:
        GenerationOpts(GenerationModel m) : model{m} {}
        int num_graphs;
        GenerationModel model;
};

struct ErdosOpts : public GenerationOpts
{
    public:
        ErdosOpts() : GenerationOpts(ErdosRenyi) {}
        int n;
        double p;
};

struct WattsOpts : public GenerationOpts
{
    public:
        WattsOpts() : GenerationOpts(WattsStrogatz) {}
        int n;
        int k;
        double b;
};

struct BarabasiOpts : public GenerationOpts
{
    public:
        BarabasiOpts() : GenerationOpts(BarabasiAlbert) {}
        int n_init;
        int n_add;
        int m_new_conn;
};