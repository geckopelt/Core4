#pragma once

#include "Serialization/Serializer.hxx"
#include "Types/Vector2.hxx"
#include "Tiles/TileBasics.hxx"
#include "Tiles/MouseMap.hxx"

class MouseMapTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(MouseMapTests);
        CPPUNIT_TEST(tileWalkerTest);
        CPPUNIT_TEST(mouseMapTest);
    CPPUNIT_TEST_SUITE_END();

    void tileWalkerTest()
    {
        const Point src(2, 5);
        CPPUNIT_ASSERT(Point(1, 5) == TileBasics::getNeighbourCell(src, West));
        CPPUNIT_ASSERT(Point(2, 4) == TileBasics::getNeighbourCell(src, NorthWest));
        CPPUNIT_ASSERT(Point(2, 3) == TileBasics::getNeighbourCell(src, North));
        CPPUNIT_ASSERT(Point(3, 4) == TileBasics::getNeighbourCell(src, NorthEast));
        CPPUNIT_ASSERT(Point(3, 5) == TileBasics::getNeighbourCell(src, East));
        CPPUNIT_ASSERT(Point(3, 6) == TileBasics::getNeighbourCell(src, SouthEast));
        CPPUNIT_ASSERT(Point(2, 7) == TileBasics::getNeighbourCell(src, South));
        CPPUNIT_ASSERT(Point(2, 6) == TileBasics::getNeighbourCell(src, SouthWest));
        CPPUNIT_ASSERT(src == TileBasics::getNeighbourCell(src, UnknownDirection));
    }

    void mouseMapTest()
    {
        const Point src(2, 5);
        const Vector2 screenPos = TileBasics::getTileScreenPos(src);
        const Vector2 scrollPos;

        const float & width  = TileBasics::TileWidth;
        const float & height = TileBasics::TileHeight;

        MouseMap mouseMap;

        // West
        CPPUNIT_ASSERT(
            TileBasics::getNeighbourCell(src, West) == 
            mouseMap.screenToTile(Vector2(screenPos.x() - width / 2, screenPos.y() + height / 2), scrollPos));

        // NorthWest
        CPPUNIT_ASSERT(
            TileBasics::getNeighbourCell(src, NorthWest) == 
            mouseMap.screenToTile(Vector2(screenPos.x(), screenPos.y()), scrollPos));

        CPPUNIT_ASSERT(
            TileBasics::getNeighbourCell(src, North) == 
            mouseMap.screenToTile(Vector2(screenPos.x() + width / 2, screenPos.y() - height / 2), scrollPos));


        /* TODO: check
        
        // North
        
        // NorthEast
        CPPUNIT_ASSERT(Point(3, 4) == mouseMap.screenToTile(Vector2(screenPos.x() + width - 1, screenPos.y()), scrollPos));
        
        // East
        CPPUNIT_ASSERT(Point(3, 5) == mouseMap.screenToTile(Vector2(screenPos.x() + width + 1, screenPos.y() + height / 2), scrollPos));
        
        // SouthEast
        CPPUNIT_ASSERT(Point(3, 6) == mouseMap.screenToTile(Vector2(screenPos.x() + width / 2, screenPos.y() + height / 2), scrollPos));
        
        // South
        CPPUNIT_ASSERT(Point(2, 7) == mouseMap.screenToTile(Vector2(screenPos.x() + width / 2, screenPos.y() + height / 2), scrollPos));
        
        // SouthWest
        CPPUNIT_ASSERT(Point(2, 6) == mouseMap.screenToTile(Vector2(screenPos.x() + width / 2, screenPos.y() + height / 2), scrollPos));

        // UnknownDirection
        CPPUNIT_ASSERT(cellPos == mouseMap.screenToTile(Vector2(screenPos.x() + width / 2, screenPos.y() + height / 2), scrollPos));
        */
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MouseMapTests);
