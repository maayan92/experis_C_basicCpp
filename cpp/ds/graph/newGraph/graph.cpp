#include "graph.hpp"

void Graph::AddVertex(const Vertex& a_newVrtx) {

        if(Has(a_newVrtx)) {
                throw ExcVertexAlreadyExist();
        }
        m_vertices.push_back(a_newVrtx);
}

void Graph::AddEdge(Vertex& a_vrtxSrc, const Vertex& a_vrtxDest) {

        if(!Has(a_vrtxDest)) { throw ExcVertexNotExist(); }
        
        Vertex* vrtxSrc = getVertexByNamePointer(a_vrtxSrc.GetName());
        
        vrtxSrc->AddEdge(a_vrtxDest);
}

bool Graph::Has(const Vertex& a_vrtx) const {

        return (m_vertices.end() != std::find(m_vertices.begin(), m_vertices.end(), a_vrtx));
}

Vertex Graph::GetVertexByName(VertexName a_name) {
        
        Vertex* vrtx = getVertexByNamePointer(a_name);
        if(!vrtx) {
                throw ExcVertexNotExist();
        }
        return *vrtx;
}

Vertex Graph::GetVertexByPosition(unsigned int m_position) {

        if(m_position >= m_vertices.size()) {
                throw ExcInvalidPosition();
        }

        return m_vertices[m_position];
}

void Graph::AddEdgeWithWeight(Vertex& a_vrtxSrc, const Vertex& a_vrtxDest, const EdgeWeight& a_weight) {

        if(!Has(a_vrtxDest)) { throw ExcVertexNotExist(); }
        
        Vertex* vrtxSrc = getVertexByNamePointer(a_vrtxSrc.GetName());
        
        vrtxSrc->AddEdgeWithWeight(a_vrtxDest, a_weight);
}

// private functions

Vertex* Graph::getVertexByNamePointer(VertexName a_name) {
        
        unsigned int position = 0;
        
        while(position < m_vertices.size()) {
                
                if(m_vertices[position].GetName() == a_name) {
                        return &(m_vertices[position]);
                }
                ++position;
        }
        
        throw ExcVertexNotExist();
}
