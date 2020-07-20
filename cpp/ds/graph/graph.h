#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "vertex.h"
#include <exception>
#include <algorithm>

class Exception : std::exception {
};

struct Name {
        Name(char a_name) : m_name(a_name) {}
        bool operator()(const Vertex& a_vrtx) const { return (a_vrtx.GetName() == m_name); }
        
        char m_name;
};

class Graph {
        typedef std::list<Vertex> GraphContainer;
        typedef GraphContainer::iterator GraphIter;
        typedef GraphContainer::const_iterator GraphCIter;
public:
        Graph(GraphContainer a_graphCon);
        Graph();
        //Graph(const Graph& a_graph) = default;
        //~Graph() = default;
        
        //Graph& operator=(const Graph& a_graph) = default;
        
        bool AddVertex(const Vertex& a_newVertex);
        bool Has(const Vertex& a_newVertex) const;
        Vertex GetVertexByName(char m_vrtxName) const;
private:
        GraphContainer m_graphCon;
};

#endif
