#include "path.hpp"

Path::Path(const Graph& a_graph)
: m_graph(a_graph) {
}

void Path::addToContainersDfs(VertexName a_name) {

        m_path.push(a_name);
        m_visited.insert(a_name);
}

Path::PathStack Path::Dfs(Vertex& a_src, const Vertex& a_dest) {

        clearDfsContainers();
        if(m_graph.Has(a_src) || m_graph.Has(a_src)) {
                m_path;
        }
        
        try {
                a_src = m_graph.GetVertexByName(a_src.GetName());
        }catch(const ExcVertexNotExist& exc) {
                return m_path;
        }
        
        Visited visited;
        addToContainersDfs(a_src.GetName());
        
        dfsRec(a_src, a_dest);
        return m_path;
}

void Path::dfsRec(Vertex& a_src, const Vertex& a_dest) {
        
        if(a_src == a_dest || m_path.empty()) {
                return;
        }
        
        unsigned int position = 0;
        while(position < a_src.GetNumOfEdges()) {
        
                Vertex vrtx = a_src.GetVertexByPosition(position);
                if(m_visited.end() == std::find(m_visited.begin(), m_visited.end(), vrtx.GetName())) {
                        vrtx = m_graph.GetVertexByName(vrtx.GetName());
                        addToContainersDfs(vrtx.GetName());
                        dfsRec(vrtx, a_dest);
                }
                ++position;
        }
        if(!(m_path.top() == a_dest.GetName())) {
                m_path.pop();
        }
}

Path::PathStack Path::Bfs(Vertex& a_src, const Vertex& a_dest) {
        
        clearContainers();
        addToContainersBfs(a_src.GetName(), a_src.GetName());

        if(!m_graph.Has(a_src) || !m_graph.Has(a_dest)) {
                return m_path;
        }
        
        while(!m_goOverVertices.empty()) {
        
                VertexName vrtxName = m_goOverVertices.front();
                m_goOverVertices.pop();
                
                if(vrtxName == a_dest.GetName()) {
                        setResult(vrtxName);
                        return m_path;
                }
                
                goOnVertexEdges(vrtxName);
        }
}

void Path::addToContainersBfs(VertexName a_chlidName, VertexName a_fatherName) {
        
        m_goOverVertices.push(a_chlidName);
        m_visited.insert(a_chlidName);
        m_childFather[a_chlidName] = a_fatherName;
}

void Path::goOnVertexEdges(VertexName a_vrtxName) {

        unsigned int position = 0;
        Vertex vrtx = m_graph.GetVertexByName(a_vrtxName);
        
        while(position < vrtx.GetNumOfEdges()) {
        
                VertexName vrtxEdgeName = vrtx.GetVertexByPosition(position).GetName();
                
                if(m_visited.end() == std::find(m_visited.begin(), m_visited.end(), vrtxEdgeName)) {
                        addToContainersBfs(vrtxEdgeName, vrtx.GetName());
                }

                ++position;
        }
}

void Path::setResult(VertexName a_vrtxName) {

        m_path.push(a_vrtxName);
        while(m_childFather[a_vrtxName] != a_vrtxName) {
                m_path.push(m_childFather[a_vrtxName]);
                a_vrtxName = m_childFather[a_vrtxName];
        }
}

void Path::clearContainers() {

        m_childFather.clear();     
        clearDfsContainers();
        
        while(!m_goOverVertices.empty()) {
               m_goOverVertices.pop();
        }
}

void Path::clearDfsContainers() {
        
        while(!m_path.empty()) {
               m_path.pop(); 
        }
        m_visited.clear();
}

/*

 1  function Dijkstra(Graph, source):
 2
 3      create vertex set Q
 4
 5      for each vertex v in Graph:             
 6          dist[v] ← INFINITY                  
 7          prev[v] ← UNDEFINED                 
 8          add v to Q                      
10      dist[source] ← 0                        
11      
12      while Q is not empty:
13          u ← vertex in Q with min dist[u]    
14                                              
15          remove u from Q 
16          
17          for each neighbor v of u:           // only v that are still in Q
18              alt ← dist[u] + length(u, v)
19              if alt < dist[v]:               
20                  dist[v] ← alt 
21                  prev[v] ← u 
22
23      return dist[], prev[]

*/
/*
Path::PathStack Path::Dijkstra(Vertex& a_src, const Vertex& a_dest) {

        SetVerticesWeight();
        m_visited.push(a_src.GetName());
        m_goOverVertices.push(a_src.GetName());

        while(!m_goOverVertices.empty()) {

                Vertex vrtx = FindVertexWithMinWeight();

                if(vrtx == a_dest) { //TODO operator==
                        SetDijkstraResult();
                        return m_path;
                }

                SetWeightToVertexEdges(vrtx.GetName());
        }
}

void Path::SetVerticesWeight() {

        GetVertex
        m_graph
}
*/