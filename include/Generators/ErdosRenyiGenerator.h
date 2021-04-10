#pragma once

#include "Generators/GraphGenerator.h"

class ErdosRenyiGenerator : public GraphGenerator
{
    public:
        ErdosRenyiGenerator(int seed, int n, double p) : GraphGenerator(seed, "Erdős–Rényi"), m_n(n), m_p(p) {}
        Graph* GenerateGraph();
        int GetMaxSize() { return m_n; }

    private:
        int m_n;
        double m_p;
};