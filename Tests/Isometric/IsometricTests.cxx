#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Utils/StringUtils.hxx"
using namespace Core4;
#include "SpriteManagerTests.hxx"
#include "PathTests.hxx"
#include "LocationMapTests.hxx"
#include "MouseMapTests.hxx"

//----------------------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    CppUnit::Test * suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(suite);
    runner.setOutputter( new CppUnit::CompilerOutputter(&runner.result(), std::cerr ));
    return runner.run() ? EXIT_SUCCESS : EXIT_FAILURE;
}
