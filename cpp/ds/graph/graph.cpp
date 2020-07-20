#include "graph.h"

Graph::Graph()
: m_graphCon() {
}

Graph::Graph(GraphContainer a_graphCon)
: m_graphCon(a_graphCon) {
}

bool Graph::AddVertex(const Vertex& a_newVertex) {

        if(Has(a_newVertex)) {
                return false;
        }
        m_graphCon.push_back(a_newVertex);
        return true;
}

bool Graph::Has(const Vertex& a_newVertex) const {

        return (find(m_graphCon.begin(), m_graphCon.end(), a_newVertex) != m_graphCon.end());
}

Vertex Graph::GetVertexByName(char m_vrtxName) const {
        
        GraphCIter itr = find_if(m_graphCon.begin(), m_graphCon.end(), Name(m_vrtxName));
        if(itr == m_graphCon.end()) {
                throw Exception();
        }
        return *itr;
}
