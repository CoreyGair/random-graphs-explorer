#pragma once

#include "Statistics/Statistics.h"

#include "matplotlibcpp.h"

#include <iostream>
#include <map>
#include <string>

class Plotter
{
    public:
        // Determines the StatisticCalc type from an IStatisticCalc obj, then calls corresponding plot func
        static void PlotStat(IStatisticCalculator* stat, std::string& model_name)
        {
            int stat_type = stat->GetType();

            std::string stat_name = "None";
            switch(stat_type)
            {
                case DEGREE:
                    stat_name = "Degree";
                    break;
                case DIAMETER:
                    stat_name = "Diameter";
                    break;
                case COMPONENTS:
                    stat_name = "Component count";
                    break;
                case BTWN_CENT:
                    stat_name = "Betweenness centrality";
                    break;
                case GLOB_CLUSTER:
                    stat_name = "Global clustering coefficient";
                    break;
                case DEGENERACY:
                    stat_name = "Degeneracy";
                    break;
            }

            if (stat_type & INT_STATS)
            {
                PlotIntStat((StatisticCalculator<int>*)stat, model_name, stat_name);
            }
            else if (stat_type & DOUBLE_STATS)
            {
                PlotDoubleStat((StatisticCalculator<double>*)stat, model_name, stat_name);
            }
        }

    private:        
        static void PlotIntStat(StatisticCalculator<int>* stat, std::string& model_name, std::string& stat_name)
        {
            std::vector<int> stats = stat->GetSamples();

            auto [min_it,max_it] = std::minmax_element(stats.begin(), stats.end());

            int min_bar = *min_it;
            int max_bar = *max_it;
            int n_bar = max_bar-min_bar+1;

            std::vector<int> bar_x (n_bar);
            std::vector<int> bar_heights (n_bar,0);

            for(int i = 0; i < n_bar; ++i)
            {
                bar_x.at(i) = i + min_bar;
            }

            for(auto v = stats.begin(); v != stats.end(); ++v)
            {
                int bar = (int)round(*v) - min_bar;
                bar_heights.at(bar) += 1;
            }

            //// matplotlib-cpp lib stuff

            matplotlibcpp::bar(bar_x, bar_heights);

            matplotlibcpp::title(stat_name + " distribution for " + model_name + " random graphs");
            
            matplotlibcpp::show();
        }

        static void PlotDoubleStat(StatisticCalculator<double>* stat, std::string& model_name, std::string& stat_name)
        {
            std::vector<double> stats = stat->GetSamples();

            auto [min_it,max_it] = std::minmax_element(stats.begin(), stats.end());

            double range = *max_it - *min_it;

            // if the range is small (for coeffs e.g. glob cluster coeff), then instead of having integer bars have thinner bars
            // also using a line plot as cant get the plot library to do thin bars
            if (range < 1.005)
            {
                // scaling stuff with range to get a good amount of bars for the range
                double scaled_range = 10*range;
                int rounded_scaled_range = std::ceil(scaled_range);
                if (rounded_scaled_range > 10) rounded_scaled_range = 10;
                int n_bar = rounded_scaled_range * 10;

                double bar_width = range / n_bar;

                int min_bar = (int)round(*min_it / bar_width);
                int max_bar = (int)round(*max_it / bar_width);

                std::vector<int> bar_x_int (n_bar+1);
                std::vector<int> bar_heights_int (n_bar+1,0);

                for(int i = 0; i < n_bar+1; ++i)
                {
                    bar_x_int.at(i) = i + min_bar;
                }

                for(auto v = stats.begin(); v != stats.end(); ++v)
                {
                    int bar = (int)round(*v / bar_width) - min_bar;
                    bar_heights_int.at(bar) += 1;
                }

                std::vector<double> bar_x (n_bar+1);
                std::vector<double> bar_heights (bar_heights_int.begin(), bar_heights_int.end());   
                for(int i = 0; i < n_bar+1; ++i)
                {
                    bar_x[i] = ((double)bar_x_int[i]) * bar_width;
                }

                matplotlibcpp::plot(bar_x, bar_heights);
            }
            else
            {
                int min_bar = (int)round(*min_it);
                int max_bar = (int)round(*max_it);
                int n_bar = max_bar-min_bar+1;

                std::vector<int> bar_x (n_bar);
                std::vector<int> bar_heights (n_bar,0);

                for(int i = 0; i < n_bar; ++i)
                {
                    bar_x.at(i) = i + min_bar;
                }

                for(auto v = stats.begin(); v != stats.end(); ++v)
                {
                    int bar = (int)round(*v) - min_bar;
                    bar_heights.at(bar) += 1;
                }  

                matplotlibcpp::bar(bar_x, bar_heights);
            }
            
            //// matplotlib-cpp lib stuff
            matplotlibcpp::title(stat_name + " distribution for " + model_name + " random graphs");
            
            matplotlibcpp::show();
        }
};