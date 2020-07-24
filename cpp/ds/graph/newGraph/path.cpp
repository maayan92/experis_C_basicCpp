#include "path.hpp"

const unsigned int INFINITI = 0xfffffffff;

Path::Path(const Graph& a_graph)
: m_graph(a_graph)
, m_childFather()
, m_goOverVertices()
, m_visited()
, m_path()
, m_childFatherWeight() {
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
        
                Vertex vrtx = a_src.GetEdgeByPosition(position);
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
        
                VertexName vrtxEdgeName = vrtx.GetEdgeByPosition(position).GetName();
                
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

Path::PathStack Path::Dijkstra(Vertex& a_src, const Vertex& a_dest) {

        // clean containers
        clearDfsContainers();
        m_childFatherWeight.clear();
        if(!m_graph.Has(a_src) || !m_graph.Has(a_dest)) {
                m_path;
        }
        
        setVerticesWeight(a_src);

        m_visited.insert(a_src.GetName());
        m_goOverVertices.push(a_src.GetName());

        while(!m_goOverVertices.empty()) {

                VertexName vrtxName = findVertexWithMinWeight();
                m_visited.insert(vrtxName);

                if(vrtxName == a_dest.GetName()) {
                        setDijkstraResult(vrtxName);
                        return m_path;
                }

                setWeightToVertexEdges(vrtxName);
        }
}

void Path::setVerticesWeight(Vertex& a_src) {

        unsigned int position = 0;
        while(position < m_graph.GetNumberOfVertices()) {

                Vertex vrtx = m_graph.GetVertexPosition(position);
                m_childFatherWeight[vrtx.GetName()] = NameWeight(vrtx.GetName(), INFINITI);
        
                ++position;
        }
        m_childFatherWeight[a_src.GetName()] = NameWeight(a_src.GetName(), 0);
}


Path::VertexName Path::findVertexWithMinWeight() {

        return min_element(m_childFatherWeight.begin(), m_childFatherWeight.end(), FindMin())->first;
}

void Path::setWeightToVertexEdges(VertexName a_vrtxName) {

        Vertex vrtx = m_graph.GetVertexByName(a_vrtxName);
        unsigned int position = 0;

        while(position < vrtx.GetNumOfEdges()) {

                Vertex vrtxChild = m_graph.GetVertexByName(a_vrtxName);
                EdgeWeight edgeWeight = vrtxChild.GetVertexWeightByPosition(position);
                EdgeWeight newWeight = m_childFatherWeight[a_vrtxName].m_weight + edgeWeight;
                
                if(checkIfNeedToUpdateEdge(vrtx, vrtxChild, newWeight)) {
                        m_childFatherWeight[vrtxChild.GetName()].m_weight = newWeight;
                        m_childFatherWeight[vrtxChild.GetName()].m_name = a_vrtxName;
                }

                ++position;
        }
}

bool Path::checkIfNeedToUpdateEdge(Vertex& a_vrtx, Vertex& a_vrtxChild, EdgeWeight a_newWeight) {

        VertexName vrtxName = a_vrtx.GetName();

        bool isWeightSmaller = (a_newWeight < m_childFatherWeight[a_vrtxChild.GetName()].m_weight);
        bool isNotVisited = (m_visited.end() == std::find(m_visited.begin(), m_visited.end(), vrtxName));
        
        return (isNotVisited && isWeightSmaller);
}

void Path::setDijkstraResult(VertexName& a_vrtxName) {

        m_path.push(a_vrtxName);
        while(m_childFatherWeight[a_vrtxName].m_name != a_vrtxName) {
                m_path.push(m_childFatherWeight[a_vrtxName].m_name);
                a_vrtxName = m_childFatherWeight[a_vrtxName].m_name;
        }
}