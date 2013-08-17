#pragma once

#include "Serialization/Serializer.hxx"
#include "Sprites/SpriteManager.hxx"
#include "Sprites/SpriteDescriptionsLoader.hxx"

#define TEST_DATA_FOLDER "../../Tests/Isometric/TestData/SpriteManager/"

class SpriteManagerTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(SpriteManagerTests);
        CPPUNIT_TEST(simpleTest);
        CPPUNIT_TEST(complexTest);
    CPPUNIT_TEST_SUITE_END();
public:
    void tearDown()
    {
        SpriteManager::getSingleton().clear();
    }

    void simpleTest()
    {
        ISpriteManager * mgr = &SpriteManager::getSingleton();

        SpriteDescriptionsLoader::load(TEST_DATA_FOLDER + std::string("SimpleSpriteList.xml"), mgr);
        CPPUNIT_ASSERT(5 == mgr->getNumSprites());
        CPPUNIT_ASSERT(2 == mgr->getCategoryCount());

        CPPUNIT_ASSERT(mgr->spriteExists("Category1.SimpleSprite1"));
        CPPUNIT_ASSERT(mgr->spriteExists("Category1.SimpleSprite2"));
        CPPUNIT_ASSERT(mgr->spriteExists("Category2.AnimatedSprite1"));
        CPPUNIT_ASSERT(mgr->spriteExists("Category2.SimpleSprite3"));
        CPPUNIT_ASSERT(mgr->spriteExists("Category2.SimpleSprite4"));
        CPPUNIT_ASSERT(!mgr->spriteExists("Something else"));

        const Sprite & simple1  = mgr->getSprite("Category1.SimpleSprite1");
        const Sprite & simple2  = mgr->getSprite("Category1.SimpleSprite2");
        const Sprite & simple3  = mgr->getSprite("Category2.SimpleSprite3");
        const Sprite & simple4  = mgr->getSprite("Category2.SimpleSprite4");
        const Sprite & animated = mgr->getSprite("Category2.AnimatedSprite1");

        CPPUNIT_ASSERT(simple1.getFrameCount() == 1);
        CPPUNIT_ASSERT(simple2.getFrameCount() == 1);
        CPPUNIT_ASSERT(simple3.getFrameCount() == 1);
        CPPUNIT_ASSERT(simple4.getFrameCount() == 1);
        CPPUNIT_ASSERT(animated.getFrameCount() == 11);

        CPPUNIT_ASSERT(simple1.getTextureName() == "Simple.tga");
        CPPUNIT_ASSERT(simple2.getTextureName() == "Simple.tga");
        CPPUNIT_ASSERT(simple3.getTextureName() == "Simple.tga");
        CPPUNIT_ASSERT(simple4.getTextureName() == "Simple2.tga");
        CPPUNIT_ASSERT(animated.getTextureName() == "Critters/Hero_Walk.tga");

        checkSpriteFrame(simple1, 0, 0,   0,  64,  32, true);
        checkSpriteFrame(simple2, 0, 64,  0,  64,  32, true);
        checkSpriteFrame(simple3, 0, 128, 0,  64,  32, true);
        checkSpriteFrame(simple4, 0, 8,   16, 128, 192, false);

        CPPUNIT_ASSERT(animated.getFPS() == 12);

        for (size_t i = 0; i < animated.getFrameCount(); i++)
        {
            checkSpriteFrame(animated, i, i * 64.0f, 0, 64, 64, true);
        }
    }

    void complexTest()
    {
        ISpriteManager * mgr = &SpriteManager::getSingleton();

        SpriteDescriptionsLoader::load(TEST_DATA_FOLDER + std::string("ComplexSpriteList.xml"), mgr);
        CPPUNIT_ASSERT(7 == mgr->getNumSprites());
        CPPUNIT_ASSERT(3 == mgr->getCategoryCount());
    }

    void checkSpriteFrame(
        const Sprite & sprite, 
        size_t frameIndex, 
        float expectedX, 
        float expectedY, 
        float expectedWidth, 
        float expectedHeight,
        bool expectedAlpha)
    {
        const SpriteFrame & frame = sprite.getFrame(frameIndex);
        CPPUNIT_ASSERT(frame.textureX == expectedX);
        CPPUNIT_ASSERT(frame.textureY == expectedY);
        CPPUNIT_ASSERT(frame.width == expectedWidth);
        CPPUNIT_ASSERT(frame.height == expectedHeight);
        CPPUNIT_ASSERT(frame.alpha == expectedAlpha);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(SpriteManagerTests);

