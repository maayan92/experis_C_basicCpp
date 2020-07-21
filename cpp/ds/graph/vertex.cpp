#include "vertex.h"

Vertex::Vertex(char a_name)
: m_name(a_name)
, m_vertexConnect() {
}
s
Vertex& Vertex::operator=(const Vertex& a_vertx) {
        
        if(this != &a_vertx) {
                m_name = a_vertx.m_name;
                m_vertexConnect = a_vertx.m_vertexConnect;
        }
        return *this;
}

bool Vertex::operator==(const Vertex& a_vertx) const {
        return m_name == a_vertx.m_name;
}

void Vertex::AddNewEdge(const Vertex& a_newVertex) {

        m_vertexConnect.push_back(a_newVertex);
}
