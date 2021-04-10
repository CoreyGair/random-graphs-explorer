#pragma once

#include <vector>
#include <map>
#include <utility>
#include <string>

class Graph
{
    public:
        Graph(int size, std::vector<std::vector<int>>* _adj_list) : m_size(size), m_adj_list(std::move(*_adj_list)) {}
        std::string* to_string();

        int GetSize() { return m_size; }
        std::vector<std::vector<int>>* GetAdjList() { return &m_adj_list; }

    private:
        int m_size;
        std::vector<std::vector<int>> m_adj_list;

};