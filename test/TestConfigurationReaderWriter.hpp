#ifndef TEST_BASIC_CONF_HPP
#define TEST_BASIC_CONF_HPP

#include <iostream>
#include <fstream>

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

#include "../include/ConfigurationReaderWriter.hpp"

using namespace CppUnit;
using namespace std;
using namespace clb;

class TestConfigurationReaderWriter:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(TestConfigurationReaderWriter);
        CPPUNIT_TEST(testReadConfiguration);
        CPPUNIT_TEST(testWriteConfiguration);
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testReadConfiguration(void);
        void testWriteConfiguration(void);

    private:
        ConfigurationReaderWriter* cTestObj;
};

#endif
