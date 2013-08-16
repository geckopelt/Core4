#pragma once

#include <string>
#include "Image/TargaLoader.hxx"
#include "Image/TargaWriter.hxx"
#include "Image/ImageManipulator.hxx"

// TODO: test input & output folders abstraction needed
class ImageTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(ImageTests);
        CPPUNIT_TEST(imageManipulatorTest);
        CPPUNIT_TEST(targaPreCreatedImageTest);
        CPPUNIT_TEST(targaImageCreationTest);
    CPPUNIT_TEST_SUITE_END();

    void imageManipulatorTest()
    {
        const size_t Width  = 32;
        const size_t Height = 16;
        ImageManipulator im(Width, Height);
        im.setPixel(1, 7, Color::Red);
        CPPUNIT_ASSERT(Color::Red == im.getPixel(1, 7));
    }

    void targaPreCreatedImageTest()
    {
        size_t width, height;
        std::vector<unsigned char> data = TargaLoader().loadImage("../../Tests/Common/TestData/test.tga", width, height);
        CPPUNIT_ASSERT(64 == width);
        CPPUNIT_ASSERT(32 == height);
        CPPUNIT_ASSERT(Color::Red == ImageManipulator(data, width, height).getPixel(31, 0));
    }

    void targaImageCreationTest()
    {
        const size_t x = 2;
        const size_t y = 3;
        const size_t createdWidth  = 8;
        const size_t createdHeight = 4;   
        const std::string outfile("created.tga"); // TODO TMP: use a temporary path
   
        ImageManipulator im1(createdWidth, createdHeight);
        im1.setPixel(x, y, Color::Blue);
        CPPUNIT_ASSERT(Color::Blue == im1.getPixel(x, y));
        TargaWriter().writeImage(outfile, im1.getRawData(), createdWidth, createdHeight);

        size_t width, height;
        std::vector<unsigned char> data = TargaLoader().loadImage(outfile, width, height);

        CPPUNIT_ASSERT(createdWidth == width);
        CPPUNIT_ASSERT(createdHeight == height);
        CPPUNIT_ASSERT(data.size() == width * height * 4);

        ImageManipulator im2(data, width, height);
        CPPUNIT_ASSERT(Color::Blue == im2.getPixel(x, y));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(ImageTests);
