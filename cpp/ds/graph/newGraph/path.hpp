#ifndef __PATH_H__
#define __PATH_H__

#include "graph.hpp"
#include <stack>
#include <map>
#include <queue>

class Path {
        typedef std::map<char,char> ChildFather;
        typedef std::queue<char> GoOverVertices;
public:
        typedef std::stack<char> PathStack;
        typedef std::set<char> Visited;

        Path(const Graph& a_graph);
        //Path(const Path& a_path) = default;
        //Path& operator=(const Path& a_path) = default;
        //~Path() = default;
        
        PathStack Dfs(Vertex& a_src, const Vertex& a_dest);
        PathStack Bfs(Vertex& a_src, const Vertex& a_dest);
private:
        void DfsRec(Vertex& a_src, const Vertex& a_dest);
        void addToContainersDfs(char a_name);
        void ClearDfsContainers();
        
        void AddToContainersBfs(char a_chlidName, char a_fatherName);
        void GoOnVertexEdges(char a_vrtxName);
        void SetResult(char a_vrtxName);
        void ClearContainers();
        
        Graph m_graph;
        ChildFather m_childFather;
        GoOverVertices m_goOverVertices;
        Visited m_visited;
        PathStack m_path;
};

#endif
