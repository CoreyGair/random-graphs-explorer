#include "Graph/Graph.h"

#include <string>

std::string* Graph::to_string()
{
    std::string* s = new std::string("{");
    for(int i = 0; i < m_size; ++i)
    {
        s->append("{");
        s->append(std::to_string(i));
        s->append(": ");
        for(auto j = m_adj_list.at(i).begin(); j != m_adj_list.at(i).end(); ++j)
        {
            s->append(std::to_string(*j));
            s->append(",");
        }
        s->append("}");
    }
    s->append("}");

    return s;
}