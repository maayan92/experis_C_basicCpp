#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "vertex.hpp"
#include <set>

class ExcVertexNotExist : public std::exception {};

class ExcVertexAlreadyExist : public std::exception {};

class ExcFailedToAdd : public std::exception {};

class Graph {
        typedef std::vector<Vertex> Vertices;
        typedef Vertices::iterator VerticesItr;
public:
        //Graph() = default;
        //Graph(const Graph& a_graph) = default;
        //Graph& operator=(const Graph& a_graph) = default;
        //~Graph() = default;

        void AddVertex(const Vertex& a_newVrtx);
        void AddEdge(Vertex& a_vrtxSrc, const Vertex& a_vrtxDest);
        bool Has(const Vertex& a_vrtx) const;
        
        Vertex GetVertexByName(char a_name);
private:
        Vertices m_vertices;
        Vertex* GetVertexByNamePointer(char a_name);
};

#endif
