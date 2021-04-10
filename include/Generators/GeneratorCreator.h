#pragma once

#include "Generators/Generators.h"

#include "ArgProcessor.h"

class GeneratorCreator
{
    public:
        static GraphGenerator* CreateGenerator(GenerationOpts* opts, int seed)
        {
            GraphGenerator* gen = nullptr;
            if (opts->model == GenerationModel::ErdosRenyi)
            {
                gen = new ErdosRenyiGenerator(seed, ((ErdosOpts*)opts)->n, ((ErdosOpts*)opts)->p);
            }
            else if (opts->model == GenerationModel::WattsStrogatz)
            {
                gen = new WattsStrogatzGenerator(seed, ((WattsOpts*)opts)->n, ((WattsOpts*)opts)->k, ((WattsOpts*)opts)->b);
            }
            else if (opts->model == GenerationModel::BarabasiAlbert)
            {
                gen = new BarabasiAlbertGenerator(seed, ((BarabasiOpts*)opts)->n_init, ((BarabasiOpts*)opts)->n_add, ((BarabasiOpts*)opts)->m_new_conn);
            }

            return  gen;
        }
};