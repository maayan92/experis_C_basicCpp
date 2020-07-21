#include "path.hpp"

Path::Path(const Graph& a_graph)
: m_graph(a_graph) {
}

static void addToContainersDfs(char a_name, Path::PathStack& a_path, Path::Visited& a_visited) {

        a_path.push(a_name);
        a_visited.insert(a_name);
}

Path::PathStack Path::Dfs(Vertex& a_src, const Vertex& a_dest) {

        PathStack path;
        if(m_graph.Has(a_src) || m_graph.Has(a_src)) {
                path;
        }
        
        try {
                a_src = m_graph.GetVertexByName(a_src.GetName());
        }catch(const ExcVertexNotExist& exc) {
                return path;
        }
        
        Visited visited;
        addToContainersDfs(a_src.GetName(), path, visited);
        
        DfsRec(a_src, a_dest, path, visited);
        return path;
}

void Path::DfsRec(Vertex& a_src, const Vertex& a_dest, PathStack& a_path, Visited& a_visited) {
        
        if(a_src == a_dest || a_path.empty()) {
                return;
        }
        
        unsigned int position = 0;
        while(position < a_src.GetNumOfEdges()) {
        
                Vertex vrtx = a_src.GetVertexByPosition(position);
                if(a_visited.end() == std::find(a_visited.begin(), a_visited.end(), vrtx.GetName())) {
                        vrtx = m_graph.GetVertexByName(vrtx.GetName());
                        addToContainersDfs(vrtx.GetName(), a_path, a_visited);
                        DfsRec(vrtx, a_dest, a_path, a_visited);
                }
                ++position;
        }
        if(!(a_path.top() == a_dest.GetName())) {
                a_path.pop();
        }
}

