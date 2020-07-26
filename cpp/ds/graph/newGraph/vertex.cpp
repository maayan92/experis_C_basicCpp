#include "vertex.hpp"

struct Equals {
        Equals(const Vertex::VertexName& a_name) : m_name(a_name) {}
        bool operator()(const Vertex::Edge& a_edge) { return a_edge.first.GetName() == m_name; }

        Vertex::VertexName m_name;
};

Vertex::Vertex(VertexName a_name)
: m_name(a_name)
, m_edges() {
}

void Vertex::AddEdge(const Vertex& a_vrtx) {
        addNewEdge(a_vrtx, 0);
}

bool Vertex::Has(const Vertex& a_vrtx) const {
        return (m_edges.end() != find_if(m_edges.begin(), m_edges.end(), Equals(a_vrtx.GetName())));
}

bool Vertex::operator==(const Vertex& a_vrtx) const {
        return m_name == a_vrtx.m_name;
}

bool Vertex::operator<(const Vertex& a_vrtx) const {
        return m_name < a_vrtx.m_name;
}

Vertex::VertexName Vertex::GetName() const {
        return m_name;
}

Vertex Vertex::GetEdgeByPosition(unsigned int a_position) const {
        
        if(a_position >= m_edges.size()) {
                throw ExcInvalidPosition();
        }
        return m_edges[a_position].first;
}

Vertex::EdgeWeight Vertex::GetVertexWeightByPosition(unsigned int a_position) const {
        
        if(a_position >= m_edges.size()) {
                throw ExcInvalidPosition();
        }
        return m_edges[a_position].second;
}

void Vertex::AddEdgeWithWeight(const Vertex& a_vrtx, const EdgeWeight& a_weight) {
        addNewEdge(a_vrtx, a_weight);
}

void Vertex::addNewEdge(const Vertex& a_vrtx, const EdgeWeight& a_weight) {

        if(Has(a_vrtx)) {
                throw ExcEdgeExist();
        }
        m_edges.push_back(Edge(a_vrtx, a_weight));
}