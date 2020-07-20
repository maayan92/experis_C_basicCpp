#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <iostream>
#include <list>

class Vertex {
public:
        typedef typename std::list<Vertex> Edges;
        typedef Edges::const_iterator VertexCItr;

        Vertex(char a_name);
        Vertex(char a_name, Edges a_vertexConnect);
        //Vertex(const Vertex& a_vrtx) = default;
        //~Vertex() = default;
        
        Vertex& operator=(const Vertex& a_vertx);
        
        bool operator==(const Vertex& a_vertx) const;
        
        void AddNewEdge(const Vertex& a_newVertex);
        char GetName() const { return m_name; }
        
        VertexCItr GetBeginEdge() const { return m_vertexConnect.begin(); }
        VertexCItr GetEnd() const { return m_vertexConnect.end(); }

private:
        char m_name;
        Edges m_vertexConnect;
};

#endif

