#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <iosfwd>
#include <exception>
#include <algorithm>
#include <vector>
#include <map>

class ExcEdgeExist : public std::exception {};

class ExcInvalidPosition : public std::exception {};

class Vertex {
public:
        typedef unsigned int EdgeWeight;
        typedef std::pair<Vertex, EdgeWeight> Edge;
        typedef std::vector< Edge > Edges;
        typedef char VertexName;
        Vertex(VertexName a_name);
        //Vertex(const Vertex& a_vrtx) = default;
        //Vertex& operator=(const Vertex& a_vrtx) = default;
        //~Vertex() = default;

        bool operator==(const Vertex& a_vrtx) const;
        bool operator<(const Vertex& a_vrtx) const;
        void AddEdge(const Vertex& a_vrtx);
        bool Has(const Vertex& a_vrtx) const;
        
        VertexName GetName() const;
        Vertex GetEdgeByPosition(unsigned int a_position) const;
        unsigned int GetNumOfEdges() const { return m_edges.size(); }
        EdgeWeight GetVertexWeightByPosition(unsigned int a_position) const;
private:
        VertexName m_name;
        Edges m_edges;
        //Edges m_edges 
};

#endif