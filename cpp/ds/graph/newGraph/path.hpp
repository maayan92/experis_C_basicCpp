#ifndef __PATH_H__
#define __PATH_H__

#include "graph.hpp"
#include <stack>

class Path {
public:
        typedef std::stack<char> PathStack;
        typedef std::set<char> Visited;

        Path(const Graph& a_graph);
        //Path(const Path& a_path) = default;
        //Path& operator=(const Path& a_path) = default;
        //~Path() = default;
        
        PathStack Dfs(Vertex& a_src, const Vertex& a_dest);
private:
        void DfsRec(Vertex& a_src, const Vertex& a_dest, PathStack& a_path, Visited& a_visited);
        
        Graph m_graph;
};

#endif
