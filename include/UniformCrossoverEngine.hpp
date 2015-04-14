/**
 * @file UniformCrossoverEngine.hpp
 * @brief Interface of uniform crossover
 */
#ifndef CLUSTERER_BACKEND_UNIFROM_CROSSOVER_ENGINE_HPP
#define CLUSTERER_BACKEND_UNIFROM_CROSSOVER_ENGINE_HPP

// standard headers
#include <stdint.h>
// external headers

// internal headers
#include "CrossoverEngine.hpp"

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

/**
 * @class UniformCrossoverEngine
 * @brief Interface for the uniform crossover method
 */
class UniformCrossoverEngine : public virtual CrossoverEngine
{
    public:
        /**
         * @brief Performs a Crossover on 2 encodings and creates a new one
         * @param parent1 The first parent contributing to the crossover
         * @param parent2 The second parent contributing to the crossover
         * @param child The encoding object that will hold the child
         */
        void crossover(const ClusterEncoding& parent1,
                                  const ClusterEncoding& parent2,
                                  ClusterEncoding& child);

        /**
         * @brief standard destructor
         */
        ~UniformCrossoverEngine();
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
