#ifndef TEST_BACKEND_MUTATION_HPP
#define TEST_BACKEND_MUTATION_HPP

// standard headers
#include <random>
#include <typeinfo>
// external headers
#include <cppunit/TestCase.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestFixture.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

//internal headers
#include "../include/Graph.hpp"
#include "../include/IntegerVectorEncoding.hpp"
#include "../include/ClusterEncoding.hpp"
#include "../include/ExplorationMutation.hpp"
#include "../include/ExplorationSplit.hpp"
#include "../include/ExplorationJoin.hpp"
#include "../include/CombinedMutation.hpp"

using namespace CppUnit;
using namespace std;
using namespace clb;

class TestExplorationMutation : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(TestExplorationMutation);
        CPPUNIT_TEST(testMutateFunction);
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        // test mutation function
        void testMutateFunction(void);

    private:
        std::mt19937 mt;
        void printSol(const ClusterEncoding&,int);
};

#endif


