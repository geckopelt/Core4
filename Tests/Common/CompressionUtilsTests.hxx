#pragma once
#include "Compression/CompressionUtils.hxx"

class CompressionUtilsTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(CompressionUtilsTests);
        CPPUNIT_TEST(compressionTest);
    CPPUNIT_TEST_SUITE_END();

    void compressionTest()
    {
        const std::string msg("Hello, compression! Hello ololo lolo lolo lololololo llloollll");
        const std::vector<char> data(msg.begin(), msg.end());

        std::vector<char> compressed;
        CompressionUtils::compress(data, compressed);
        CPPUNIT_ASSERT(compressed.size() < data.size());

        std::vector<char> decompressed;
        CompressionUtils::decompress(compressed, decompressed, data.size());
        CPPUNIT_ASSERT(decompressed == data);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(CompressionUtilsTests);