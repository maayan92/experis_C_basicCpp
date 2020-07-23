#include "path.hpp"
#include <iostream>

static void VertexCTORTest() {

        Vertex vrtx('a');
        static int testNumber = 0;
        std::cout << "vertex CTOR test " <<  ++testNumber << ": \t\t\033[1;31m"
                << ((vrtx.GetName() == 'a') ? "SUCCEEDED" : "FAILED") << "\033[0m" << std::endl;
}

static void VertexOperatorCompareTest(const Vertex& a_vrtxLeft, const Vertex& a_vrtxRight, bool a_isEqual) {

        static int testNumber = 0;
        std::cout << "vertex operator== test " <<  ++testNumber << ": \t\033[1;31m"
                << ((a_isEqual == (a_vrtxLeft == a_vrtxRight)) ? "SUCCEEDED" : "FAILED") 
                        << "\033[0m" << std::endl;
}

static void VertexOperatorSmallerTest(const Vertex& a_vrtxLeft, const Vertex& a_vrtxRight, bool a_isSmaller) {

        static int testNumber = 0;
        std::cout << "vertex operator< test " <<  ++testNumber << ": \t\033[1;31m"
                << ((a_isSmaller == (a_vrtxLeft < a_vrtxRight)) ? "SUCCEEDED" : "FAILED") 
                        << "\033[0m" << std::endl;
}

static void VertexAddEdgeTest(Vertex& a_vrtx, const Vertex& a_vrtxToAdd, bool a_addSucceed) {

        static int testNumber = 0;
        std::cout << "vertex add edge test " <<  ++testNumber << ": \t\033[1;31m";
        
        try {
                a_vrtx.AddEdge(a_vrtxToAdd);
        }catch(const ExcEdgeExist& exc) {
                std::cout << ((!a_addSucceed) ? "SUCCEEDED" : "FAILED") << "\033[0m" << std::endl;
                return;
        }
        
        std::cout << ((a_addSucceed == (a_vrtx.Has(a_vrtxToAdd))) ? "SUCCEEDED" : "FAILED") 
                        << "\033[0m" << std::endl;
}

static void VertexHasTest(Vertex& a_vrtx, const Vertex& a_vrtxToAdd, bool a_has) {

        static int testNumber = 0;
        std::cout << "vertex has test " <<  ++testNumber << ": \t\t\033[1;31m"
                << ((a_has == (a_vrtx.Has(a_vrtxToAdd))) ? "SUCCEEDED" : "FAILED") << "\033[0m" << std::endl;
}

static void GraphAddVertexTest(Graph& a_graph, const Vertex& a_vrtx, bool a_addSucceed) {

        static int testNumber = 0;
        std::cout << "graph add vertex test " <<  ++testNumber << ": \t\033[1;31m";
        
        try {
                a_graph.AddVertex(a_vrtx);
        }catch(const ExcVertexAlreadyExist& exc) {
                std::cout << ((!a_addSucceed) ? "SUCCEEDED" : "FAILED") << "\033[0m" << std::endl;
                return;
        }catch(const ExcFailedToAdd& exc) {
                std::cout << "error occurred" << std::endl;
                return;
        }
        
        std::cout << ((a_addSucceed == (a_graph.Has(a_vrtx))) ? "SUCCEEDED" : "FAILED") 
                        << "\033[0m" << std::endl;
}

static void GraphAddEdgeTest(Graph& a_graph, Vertex& a_vrtx, Vertex& a_vrtxToAdd, bool a_addSucceed) {

        static int testNumber = 0;
        std::cout << "graph add edge test " <<  ++testNumber << ": \t\t\033[1;31m";
        
        try {
                a_graph.AddEdge(a_vrtx, a_vrtxToAdd);
        }catch(const ExcVertexNotExist& exc) {
                std::cout << ((!a_addSucceed) ? "SUCCEEDED" : "FAILED") << "\033[0m" << std::endl;
                return;
        }catch(const ExcEdgeExist& exc) {
                std::cout << ((!a_addSucceed) ? "SUCCEEDED" : "FAILED") << "\033[0m" << std::endl;
                return;
        }
        
        std::cout << ((a_addSucceed == (a_graph.Has(a_vrtxToAdd))) ? "SUCCEEDED" : "FAILED") 
                        << "\033[0m" << std::endl;
}

static void DfsTest(const Graph& a_graph, const Path::PathStack& pathResult, Vertex& a_src, const Vertex& a_dest) {

        static int testNumber = 0;
        
        Path p(a_graph);
        Path::PathStack path = p.Dfs(a_src, a_dest);
        
        bool result = (path == pathResult);
        
        std::cout << "path DFS test " <<  ++testNumber << ": \t\t\033[1;31m"
                << ((result) ? "SUCCEEDED" : "FAILED") << "\033[0m" << std::endl;
        
}

static void BfsTest(const Graph& a_graph, const Path::PathStack& pathResult, Vertex& a_src, const Vertex& a_dest) {

        static int testNumber = 0;
        
        Path p(a_graph);
        Path::PathStack path = p.Bfs(a_src, a_dest);
        
        bool result = (path == pathResult);
        
        std::cout << "path BFS test " <<  ++testNumber << ": \t\t\033[1;31m"
                        << ((result) ? "SUCCEEDED" : "FAILED") << "\033[0m" << std::endl;
        
}

int main() {

        ///// vertex tests:
        std::cout << "----- vertex -----" << std::endl << std::endl;
        
        VertexCTORTest();

        Vertex vrtxA('a'), vrtxEqual('a'), vrtxC('c'), vrtxD('d');

        VertexOperatorCompareTest(vrtxA, vrtxEqual, true);
        VertexOperatorCompareTest(vrtxA, vrtxC, false);
        
        VertexOperatorSmallerTest(vrtxA, vrtxC, true);
        VertexOperatorSmallerTest(vrtxA, vrtxEqual, false);
        VertexOperatorSmallerTest(vrtxC, vrtxA, false);
        
        VertexAddEdgeTest(vrtxA, vrtxC, true);
        VertexAddEdgeTest(vrtxA, vrtxC, false);
        
        VertexHasTest(vrtxA, vrtxC, true);
        VertexHasTest(vrtxA, vrtxD, false);
        
        ///// graph tests:
        std::cout << std::endl << "----- graph -----" << std::endl << std::endl;
        
        Graph graph;
        
        GraphAddVertexTest(graph, vrtxA, true);
        GraphAddVertexTest(graph, vrtxA, false);
        
        GraphAddEdgeTest(graph, vrtxA, vrtxA, true);
        GraphAddEdgeTest(graph, vrtxD, vrtxA, false);
        GraphAddEdgeTest(graph, vrtxA, vrtxD, false);
        
        ///// path tests:
        std::cout << std::endl << "----- path -----" << std::endl << std::endl;
        
        Vertex vrtxPathA('a'), vrtxPathB('b'), vrtxPathC('c'), vrtxPathD('d');
        Graph graphForPath;
        
        graphForPath.AddVertex(vrtxPathA);
        graphForPath.AddVertex(vrtxPathB);
        graphForPath.AddVertex(vrtxPathC);
        graphForPath.AddVertex(vrtxPathD);
        
        graphForPath.AddEdge(vrtxPathA, vrtxPathD);
        graphForPath.AddEdge(vrtxPathA, vrtxPathB);
        graphForPath.AddEdge(vrtxPathB, vrtxPathC);
        graphForPath.AddEdge(vrtxPathB, vrtxPathA);
        graphForPath.AddEdge(vrtxPathD, vrtxPathB);
        
        Path::PathStack result;
        
        Vertex notInGraph('s');

        // DFS:
        DfsTest(graphForPath, result, notInGraph, vrtxPathD);
        
        result.push(vrtxPathB.GetName());
        DfsTest(graphForPath, result, vrtxPathB, vrtxPathB);
        
        result.push(vrtxPathA.GetName());
        result.push(vrtxPathD.GetName());
        
        DfsTest(graphForPath, result, vrtxPathB, vrtxPathD);

        // BFS:
        Path::PathStack resultBfs;

        BfsTest(graphForPath, resultBfs, notInGraph, vrtxPathD);
        resultBfs.push(vrtxPathD.GetName());

        BfsTest(graphForPath, resultBfs, vrtxPathD, vrtxPathD);

        resultBfs.push(vrtxPathA.GetName());
        resultBfs.push(vrtxPathB.GetName());
        
        BfsTest(graphForPath, resultBfs, vrtxPathB, vrtxPathD);
   
        return 0;
}
