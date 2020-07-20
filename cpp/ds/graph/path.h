#ifndef __PATH_H__
#define __PATH_H__

#include "graph.h"
#include <vector>
#include <stack>

class Path {
public:
        typedef std::vector<char> VisitedVertices;
        typedef std::stack<char> PathContainer;

        Path(const Graph& a_graph);
        //~Path() = default;
        
        PathContainer DFS(Vertex& a_begin, const Vertex& a_end) const;
        //VisitedVertices BFS(const Vertex& a_begin, const Vertex& a_end) const;

private:
        Graph m_graph;
};

#endif
