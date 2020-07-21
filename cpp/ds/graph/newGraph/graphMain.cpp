#include "path.hpp"
#include <iostream>

static void VertexCTORTest() {

        Vertex vrtx('a');
        static int testNumber = 0;
        std::cout << "vertex CTOR test " <<  ++testNumber << ": \t\t"
                << ((vrtx.GetName() == 'a') ? "SUCCEEDED" : "FAILED") << std::endl;
}

static void VertexOperatorCompareTest(const Vertex& a_vrtxLeft, const Vertex& a_vrtxRight, bool a_isEqual) {

        static int testNumber = 0;
        std::cout << "vertex operator== test " <<  ++testNumber << ": \t"
                << ((a_isEqual == (a_vrtxLeft == a_vrtxRight)) ? "SUCCEEDED" : "FAILED") << std::endl;
}

static void VertexOperatorSmallerTest(const Vertex& a_vrtxLeft, const Vertex& a_vrtxRight, bool a_isSmaller) {

        static int testNumber = 0;
        std::cout << "vertex operator< test " <<  ++testNumber << ": \t"
                << ((a_isSmaller == (a_vrtxLeft < a_vrtxRight)) ? "SUCCEEDED" : "FAILED") << std::endl;
}

static void VertexAddEdgeTest(Vertex& a_vrtx, const Vertex& a_vrtxToAdd, bool a_addSucceed) {

        static int testNumber = 0;
        std::cout << "vertex add edge test " <<  ++testNumber << ": \t";
        
        try {
                a_vrtx.AddEdge(a_vrtxToAdd);
        }catch(const ExcEdgeExist& exc) {
                std::cout << ((!a_addSucceed) ? "SUCCEEDED" : "FAILED") << std::endl;
                return;
        }
        
        std::cout << ((a_addSucceed == (a_vrtx.Has(a_vrtxToAdd))) ? "SUCCEEDED" : "FAILED") << std::endl;
}

static void VertexHasTest(Vertex& a_vrtx, const Vertex& a_vrtxToAdd, bool a_has) {

        static int testNumber = 0;
        std::cout << "vertex has test " <<  ++testNumber << ": \t\t"
                << ((a_has == (a_vrtx.Has(a_vrtxToAdd))) ? "SUCCEEDED" : "FAILED") << std::endl;
}

static void GraphAddVertexTest(Graph& a_graph, const Vertex& a_vrtx, bool a_addSucceed) {

        static int testNumber = 0;
        std::cout << "graph add vertex test " <<  ++testNumber << ": \t";
        
        try {
                a_graph.AddVertex(a_vrtx);
        }catch(const ExcVertexAlreadyExist& exc) {
                std::cout << ((!a_addSucceed) ? "SUCCEEDED" : "FAILED") << std::endl;
                return;
        }catch(const ExcFailedToAdd& exc) {
                std::cout << "error occurred" << std::endl;
                return;
        }
        
        std::cout << ((a_addSucceed == (a_graph.Has(a_vrtx))) ? "SUCCEEDED" : "FAILED") << std::endl;
}

static void GraphAddEdgeTest(Graph& a_graph, Vertex& a_vrtx, Vertex& a_vrtxToAdd, bool a_addSucceed) {

        static int testNumber = 0;
        std::cout << "graph add edge test " <<  ++testNumber << ": \t\t";
        
        try {
                a_graph.AddEdge(a_vrtx, a_vrtxToAdd);
        }catch(const ExcVertexNotExist& exc) {
                std::cout << ((!a_addSucceed) ? "SUCCEEDED" : "FAILED") << std::endl;
                return;
        }
        
        std::cout << ((a_addSucceed == (a_graph.Has(a_vrtxToAdd))) ? "SUCCEEDED" : "FAILED") << std::endl;
}

static void DfsTest(const Graph& a_graph, const std::stack<char>& pathResult, Vertex& a_src, const Vertex& a_dest) {

        static int testNumber = 0;
        
        Path p(a_graph);
        std::stack<char> path = p.Dfs(a_src, a_dest);
        
        bool result = (path == pathResult);
        
        std::cout << "path DFS test " <<  ++testNumber << ": \t\t"
                << ((result) ? "SUCCEEDED" : "FAILED") << std::endl;
        
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
        
        Graph graphForPath;
        Vertex vrtxB('b');
        
        graphForPath.AddVertex(vrtxA);
        graphForPath.AddVertex(vrtxB);
        graphForPath.AddVertex(vrtxC);
        graphForPath.AddVertex(vrtxD);
        
        graphForPath.AddEdge(vrtxA, vrtxB);
        graphForPath.AddEdge(vrtxA, vrtxD);
        graphForPath.AddEdge(vrtxB, vrtxC);
        graphForPath.AddEdge(vrtxB, vrtxA);
        graphForPath.AddEdge(vrtxD, vrtxB);
        
        std::stack<char> result;
        
        Vertex notInGraph('s');
        DfsTest(graphForPath, result, notInGraph, vrtxD);
        
        result.push(vrtxB.GetName());
        
        DfsTest(graphForPath, result, vrtxB, vrtxB);
        
        result.push(vrtxA.GetName());
        result.push(vrtxD.GetName());
        
        DfsTest(graphForPath, result, vrtxB, vrtxD);
        
   
        return 0;
}
