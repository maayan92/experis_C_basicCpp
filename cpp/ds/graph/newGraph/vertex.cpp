#include "vertex.hpp"

Vertex::Vertex(char a_name)
: m_name(a_name)
, m_edges() {
}

void Vertex::AddEdge(const Vertex& a_vrtx) {

        if(Has(a_vrtx)) {
                throw ExcEdgeExist();
        }
        m_edges.push_back(a_vrtx);
}

bool Vertex::Has(const Vertex& a_vrtx) const {

        return (m_edges.end() != std::find(m_edges.begin(), m_edges.end(), a_vrtx));
}

bool Vertex::operator==(const Vertex& a_vrtx) const {
        return m_name == a_vrtx.m_name;
}

bool Vertex::operator<(const Vertex& a_vrtx) const {
        return m_name < a_vrtx.m_name;
}

char Vertex::GetName() const {
        return m_name;
}

Vertex Vertex::GetVertexByPosition(unsigned int a_position) const {
        
        if(a_position >= m_edges.size()) {
                throw ExcInvalidPosition();
        }
        return m_edges[a_position];
}
