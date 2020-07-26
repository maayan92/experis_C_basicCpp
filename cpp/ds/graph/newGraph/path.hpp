#ifndef __PATH_H__
#define __PATH_H__

#include "graph.hpp"
#include "nameWeight.hpp"
#include <stack>
#include <map>
#include <queue>

class Path {
        typedef Vertex::VertexName VertexName;
        typedef Vertex::EdgeWeight EdgeWeight;
        typedef std::map<VertexName,VertexName> ChildFather;
        typedef std::map<VertexName, NameWeight> ChildFatherWeight;
        typedef ChildFatherWeight::iterator ChildFatherWeightItr;
        typedef std::queue<VertexName> GoOverVertices;
        typedef std::set<VertexName> Visited;
public:
        typedef std::stack<VertexName> PathStack;

        Path(const Graph& a_graph);
        //Path(const Path& a_path) = default;
        //Path& operator=(const Path& a_path) = default;
        //~Path() = default;
        
        PathStack Dfs(Vertex& a_src, const Vertex& a_dest);
        PathStack Bfs(Vertex& a_src, const Vertex& a_dest);
        PathStack Dijkstra(Vertex& a_src, const Vertex& a_dest);

private:
        void dfsRec(Vertex& a_src, const Vertex& a_dest);
        void addToContainersDfs(VertexName a_name);
        void clearDfsContainers();
        
        void addToContainersBfs(VertexName a_chlidName, VertexName a_fatherName);
        void goOnVertexEdges(VertexName a_vrtxName);
        void setResult(VertexName a_vrtxName);
        void clearContainers();

        void setVerticesWeight(Vertex& a_src);
        VertexName findVertexWithMinWeight();
        void setWeightToVertexEdges(VertexName a_vrtxName);
        bool checkIfNeedToUpdateEdge(Vertex& a_vrtxChild, EdgeWeight a_newWeight);
        void setDijkstraResult(VertexName& a_vrtxName);
        
        Graph m_graph;
        ChildFather m_childFather;
        GoOverVertices m_goOverVertices;
        Visited m_visited;
        PathStack m_path;
        ChildFatherWeight m_childFatherWeight;
};

#endif