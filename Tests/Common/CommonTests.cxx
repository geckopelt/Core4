#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Utils/StringUtils.hxx"

using namespace Core4;
#include "StringUtilsTests.hxx"
#include "TypeConverterTests.hxx"
#include "SerializationTests.hxx"
#include "CompressionUtilsTests.hxx"
#include "UtilsTests.hxx"
#include "ImageTests.hxx"

//----------------------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    CppUnit::Test * suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(suite);
    runner.setOutputter( new CppUnit::CompilerOutputter(&runner.result(), std::cerr ));
    return runner.run() ? EXIT_SUCCESS : EXIT_FAILURE;
}
