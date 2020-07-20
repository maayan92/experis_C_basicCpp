#include "path.h"


int main() {
        std::list<Vertex> va, vb ,vc, vd; 
        
        Vertex a('a', va), b('b', vb), c('c', vc), d('d', vd);
       
        a.AddNewEdge(b);
        a.AddNewEdge(d);
        
        b.AddNewEdge(c);
        b.AddNewEdge(a);
        
        d.AddNewEdge(b);
        
        Graph g;
        g.AddVertex(a);
        g.AddVertex(b);
        g.AddVertex(c);
        g.AddVertex(d);
        
        Path p(g);
        std::stack<char> result = p.DFS(a, c);

        std::cout << result.top();
        result.pop();
        
        while(!result.empty()) {
                
                std::cout << " <- " << result.top();
                result.pop();
        }

        std::cout << std::endl;

        return 0;
}
