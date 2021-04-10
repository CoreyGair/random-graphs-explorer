#pragma once

#include "Generators/GraphGenerator.h"

class BarabasiAlbertGenerator : public GraphGenerator
{
    public:
        BarabasiAlbertGenerator(int seed, int n_init, int n_additional, double new_conn) :  GraphGenerator(seed, "Barabási–Albert"),
                                                                                            m_n_initial(n_init), 
                                                                                            m_n_additional(n_additional), 
                                                                                            m_m_new_connections(new_conn)
                                                                                            {}
        Graph* GenerateGraph();
        int GetMaxSize() { return m_n_initial + m_n_additional; }

    private:
        int m_n_initial;
        int m_n_additional;
        int m_m_new_connections;
};