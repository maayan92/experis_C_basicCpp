#include "path.hpp"

Path::Path(const Graph& a_graph)
: m_graph(a_graph) {
}

void Path::addToContainersDfs(char a_name) {

        m_path.push(a_name);
        m_visited.insert(a_name);
}

Path::PathStack Path::Dfs(Vertex& a_src, const Vertex& a_dest) {

        ClearDfsContainers();
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
        
        DfsRec(a_src, a_dest);
        return m_path;
}

void Path::DfsRec(Vertex& a_src, const Vertex& a_dest) {
        
        if(a_src == a_dest || m_path.empty()) {
                return;
        }
        
        unsigned int position = 0;
        while(position < a_src.GetNumOfEdges()) {
        
                Vertex vrtx = a_src.GetVertexByPosition(position);
                if(m_visited.end() == std::find(m_visited.begin(), m_visited.end(), vrtx.GetName())) {
                        vrtx = m_graph.GetVertexByName(vrtx.GetName());
                        addToContainersDfs(vrtx.GetName());
                        DfsRec(vrtx, a_dest);
                }
                ++position;
        }
        if(!(m_path.top() == a_dest.GetName())) {
                m_path.pop();
        }
}

Path::PathStack Path::Bfs(Vertex& a_src, const Vertex& a_dest) {
        
        ClearContainers();
        AddToContainersBfs(a_src.GetName(), a_src.GetName());

        if(!m_graph.Has(a_src) || !m_graph.Has(a_dest)) {
                return m_path;
        }
        
        while(!m_goOverVertices.empty()) {
        
                char vrtxName = m_goOverVertices.front();
                m_goOverVertices.pop();
                
                if(vrtxName == a_dest.GetName()) {
                        SetResult(vrtxName);
                        return m_path;
                }
                
                GoOnVertexEdges(vrtxName);
        }
}

void Path::AddToContainersBfs(char a_chlidName, char a_fatherName) {
        
        m_goOverVertices.push(a_chlidName);
        m_visited.insert(a_chlidName);
        m_childFather[a_chlidName] = a_fatherName;
}

void Path::GoOnVertexEdges(char a_vrtxName) {

        unsigned int position = 0;
        Vertex vrtx = m_graph.GetVertexByName(a_vrtxName);
        
        while(position < vrtx.GetNumOfEdges()) {
        
                char vrtxEdgeName = vrtx.GetVertexByPosition(position).GetName();
                
                if(m_visited.end() == std::find(m_visited.begin(), m_visited.end(), vrtxEdgeName)) {
                        AddToContainersBfs(vrtxEdgeName, vrtx.GetName());
                }

                ++position;
        }
}

void Path::SetResult(char a_vrtxName) {

        m_path.push(a_vrtxName);
        while(m_childFather[a_vrtxName] != a_vrtxName) {
                m_path.push(m_childFather[a_vrtxName]);
                a_vrtxName = m_childFather[a_vrtxName];
        }
}

void Path::ClearContainers() {

        m_childFather.clear();     
        ClearDfsContainers();
        
        while(!m_goOverVertices.empty()) {
               m_goOverVertices.pop();
        }
}

void Path::ClearDfsContainers() {
        
        while(!m_path.empty()) {
               m_path.pop(); 
        }
        m_visited.clear();
}
