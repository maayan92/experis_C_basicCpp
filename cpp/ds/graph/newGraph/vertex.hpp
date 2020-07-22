#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <iosfwd>
#include <exception>
#include <algorithm>
#include <vector>

class ExcEdgeExist : public std::exception {};

class ExcInvalidPosition : public std::exception {};

class Vertex {
        typedef std::vector<Vertex> Edges;
public:
        Vertex(char a_name);
        //Vertex(const Vertex& a_vrtx) = default;
        //Vertex& operator=(const Vertex& a_vrtx) = default;
        //~Vertex() = default;

        bool operator==(const Vertex& a_vrtx) const;
        bool operator<(const Vertex& a_vrtx) const;
        void AddEdge(const Vertex& a_vrtx);
        bool Has(const Vertex& a_vrtx) const;
        
        char GetName() const;
        Vertex GetVertexByPosition(unsigned int a_position) const;
        unsigned int GetNumOfEdges() const { return m_edges.size(); }
private:
        char m_name;
        Edges m_edges;
};

#endif
