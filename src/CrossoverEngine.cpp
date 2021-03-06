/**
 * @file CrossoverEngine.cpp
 * @brief crossover implementation
 */
#include "../include/CrossoverEngine.hpp"

namespace clusterer
{

namespace backend
{

void CrossoverEngine::crossover(const ClusterEncoding& parent1, const ClusterEncoding& parent2,
                                ClusterEncoding& child1, ClusterEncoding& child2)
{
    for (size_t i = 0; i < parent1.size(); i++)
    {
        child1.addToCluster(i, parent1.getClusterOfVertex(i));
        child2.addToCluster(i, parent2.getClusterOfVertex(i));
    }
}


}   //end namespace backend
}   //end namespace clusterer