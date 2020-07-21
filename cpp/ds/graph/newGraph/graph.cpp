#include "graph.hpp"

void Graph::AddVertex(const Vertex& a_newVrtx) {

        if(Has(a_newVrtx)) {
                throw ExcVertexAlreadyExist();
        }
        m_vertices.push_back(a_newVrtx);
}

void Graph::AddEdge(Vertex& a_vrtxSrc, const Vertex& a_vrtxDest) {

        if(!Has(a_vrtxDest)) { throw ExcVertexNotExist(); }
        
        Vertex* vrtxSrc = GetVertexByNamePointer(a_vrtxSrc.GetName());
        
        if(!vrtxSrc) { throw ExcVertexNotExist(); }
        
        vrtxSrc->AddEdge(a_vrtxDest);
}

bool Graph::Has(const Vertex& a_vrtx) const {

        return (m_vertices.end() != std::find(m_vertices.begin(), m_vertices.end(), a_vrtx));
}

Vertex* Graph::GetVertexByNamePointer(char a_name) {
        
        unsigned int position = 0;
        
        while(position < m_vertices.size()) {
                
                if(m_vertices[position].GetName() == a_name) {
                        return &(m_vertices[position]);
                }
                ++position;
        }
        
        return 0;
}

Vertex Graph::GetVertexByName(char a_name) {
        
        Vertex* vrtx = GetVertexByNamePointer(a_name);
        if(!vrtx) {
                throw ExcVertexNotExist();
        }
        return *vrtx;
}

