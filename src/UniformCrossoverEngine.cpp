/**
 * @file UniformCrossoverEngine.cpp
 * @brief Interface of uniform crossover
 */

// internal headers
#include "../include/UniformCrossoverEngine.hpp"
#include "../include/IntegerVectorEncoding.hpp"

/**
* @namespace clusterer
* @brief The namespace clusterer is the main namespace of the clusterer project.
*/
namespace clusterer
{

/**
* @namespace backend
* @brief The namespace backend is the namespace for all backend components of the
* project.
*/
namespace backend
{

    std::mt19937 UniformCrossoverEngine::rng;
    std::uniform_int_distribution<unsigned> UniformCrossoverEngine::uni_dist(0, 1);

    bool UniformCrossoverEngine::getTrueOrFalse()
    {
        return uni_dist(rng) == 1;
    }

    void UniformCrossoverEngine::crossover(const ClusterEncoding& parent1, 
                                           const ClusterEncoding& parent2,
                                           ClusterEncoding& child)
    {
        unsigned i;
        unsigned n = parent1.size();
        for (i = 0; i < n; i++)
        {
            // Put vertex i in the cluster it is in one of the parents
            // With probability 50% for picking each parent
            if (getTrueOrFalse() == true)
            {
                child.addToCluster(i, parent1.getClusterOfVertex(i));
            } 
            else
            {
                child.addToCluster(i, parent2.getClusterOfVertex(i));
            }
        }
    }

    UniformCrossoverEngine::~UniformCrossoverEngine() {}

}
}
