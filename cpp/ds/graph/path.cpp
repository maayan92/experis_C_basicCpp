#include "path.h"

static Vertex::VertexCItr GetVertexIterator(const Vertex& a_vrtx, const Path::VisitedVertices& a_visited) {

        Vertex::VertexCItr itr = a_vrtx.GetBeginEdge();
        while(itr != a_vrtx.GetEnd() && (find(a_visited.begin(), a_visited.end(), itr->GetName()) != a_visited.end())) {
                ++itr;
        }
        return itr;
}

static void SetToContainers(char a_vrtxName, Path::VisitedVertices& a_visited, Path::PathContainer& a_path) {
      
        a_path.push(a_vrtxName);
        a_visited.push_back(a_vrtxName);
}

Path::Path(const Graph& a_graph)
: m_graph(a_graph) {
}

Path::PathContainer Path::DFS(Vertex& a_begin, const Vertex& a_end) const {

        PathContainer path;
        if(!m_graph.Has(a_begin) || !m_graph.Has(a_end)) {
                return path;
        }
        
        VisitedVertices visited;
        SetToContainers(a_begin.GetName(), visited, path);

        while(!(a_begin == a_end || path.empty()) {
        
                Vertex::VertexCItr itr = GetVertexIterator(a_begin, visited);
                
                if(itr == a_begin.GetEnd()) {
                        path.pop();
                        a_begin = m_graph.GetVertexByName(path.top());
                }
                else {
                        a_begin = m_graph.GetVertexByName(itr->GetName());
                        SetToContainers(a_begin.GetName(), visited, path);
                }
        }
        
        return path;
}

Path::VisitedVertices Path::BFS(const Vertex& a_begin, const Vertex& a_end) const {

        if(!m_graph.Has(a_begin) || !m_graph.Has(a_end)) {
                return path;
        }
        
        
        
        
        
        
}








