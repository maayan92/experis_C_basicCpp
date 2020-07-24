#ifndef __NAME_WEIGHT_H__
#define __NAME_WEIGHT_H__

#include "vertex.hpp"

//namespace experis {

class NameWeight {
    friend class Path;
    typedef Vertex::VertexName VertexName;
    typedef Vertex::EdgeWeight EdgeWeight;
public:
    NameWeight(const VertexName& a_name, const EdgeWeight& m_weight);
    //NameWeight(const NameWeight& a_nameWeight) = default;
    //NameWeight& operator=(const NameWeight& a_nameWeight) = default;

protected:
    ~NameWeight() {}

private:
    VertexName m_name;
    EdgeWeight m_weight;

};

//} // experis

//namespace experis {

NameWeight::NameWeight(const VertexName& a_name, const EdgeWeight& a_weight)
: m_name(a_name)
, m_weight(a_weight) {
}

//} // experis

#endif