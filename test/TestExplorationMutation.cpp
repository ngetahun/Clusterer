#include "TestExplorationMutation.hpp"
#include <iostream>
CPPUNIT_TEST_SUITE_REGISTRATION(TestExplorationMutation);

void TestExplorationMutation::setUp(void)
{

}

void TestExplorationMutation::tearDown(void)
{

}

void TestExplorationMutation::printSol(const ClusterEncoding& clusterSol,int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout<<clusterSol.getClusterOfVertex(i)<<" ";
    }
    std::cout<<"\n";
}

void TestExplorationMutation::testMutateFunction(void)
{
    clb::CombinedMutation mutator(&mt);
    clb::Graph graph;

    graph.addVertex(Vertex(0));
    graph.addVertex(Vertex(1));
    graph.addVertex(Vertex(2));
    graph.addVertex(Vertex(3));
    graph.addVertex(Vertex(4));

    graph.addEdge(Vertex(0), Vertex(1), 0.125);
    graph.addEdge(Vertex(0), Vertex(2), 0.125);
    graph.addEdge(Vertex(0), Vertex(3), 0.125);

    graph.addEdge(Vertex(1), Vertex(0), 0.25);
    graph.addEdge(Vertex(1), Vertex(2), 0.25);
    graph.addEdge(Vertex(1), Vertex(3), 0.25);

    graph.addEdge(Vertex(2), Vertex(0), 0.5);
    graph.addEdge(Vertex(2), Vertex(1), 0.5);
    graph.addEdge(Vertex(2), Vertex(3), 0.5);

    graph.addEdge(Vertex(3), Vertex(0), 0.75);
    graph.addEdge(Vertex(3), Vertex(1), 0.75);
    graph.addEdge(Vertex(3), Vertex(2), 0.75);

    graph.addEdge(Vertex(4), Vertex(0), 0.55);
    graph.addEdge(Vertex(4), Vertex(1), 0.55);

    clb::IntegerVectorEncoding solution(&graph);

    solution.addToCluster(0,0);
    solution.addToCluster(1,2);
    solution.addToCluster(2,2);
    solution.addToCluster(3,1);
    solution.addToCluster(4,3);

    std::cout<<"before mutate--test\n";
    clb::IntegerVectorEncoding result1 = solution;
    mutator.mutate(result1);

    clb::IntegerVectorEncoding result2 = solution;
    mutator.mutate(result2);

    clb::IntegerVectorEncoding result3 = solution;
    mutator.mutate(result3);

    clb::IntegerVectorEncoding result4 = solution;
    mutator.mutate(result4);

    clb::IntegerVectorEncoding result5 = solution;
    mutator.mutate(result5);

    //int checker1,checker2,checker3,checker4,checker5;
    //checker1 = checker2 = checker3 = checker4 = checker5 = 0;

    int solClusterCount = solution.getClusterCount();
    int result1CC = result1.getClusterCount();
    int result2CC = result2.getClusterCount();
    int result3CC = result3.getClusterCount();
    int result4CC = result4.getClusterCount();
    int result5CC = result5.getClusterCount();

    CPPUNIT_ASSERT(std::abs(solClusterCount-result1CC) <= 2 &&
                   std::abs(solClusterCount-result2CC) <= 2 &&
                   std::abs(solClusterCount-result3CC) <= 2 &&
                   std::abs(solClusterCount-result4CC) <= 2 &&
                   std::abs(solClusterCount-result5CC) <= 2);
}
