#pragma once

#include "Generators/GraphGenerator.h"

class WattsStrogatzGenerator : public GraphGenerator
{
    public:
        WattsStrogatzGenerator(int seed, int n, int k, double b) : GraphGenerator(seed, "Watts-Strogatz"), m_n(n), m_k(k), m_b(b) {}
        Graph* GenerateGraph();
        int GetMaxSize() { return m_n; }

    private:
        int m_n;
        int m_k;
        double m_b;
};