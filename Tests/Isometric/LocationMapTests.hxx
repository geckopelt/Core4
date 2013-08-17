#pragma once

#include "Utils/StringUtils.hxx"
#include "Serialization/Serializer.hxx"
#include "Sprites/ISpriteManager.hxx"
#include "Location/LocationMap.hxx"
#include "Tiles/TileBasics.hxx"

class LocationMapTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(LocationMapTests);
        CPPUNIT_TEST(locationMapSerializationTest);
    CPPUNIT_TEST_SUITE_END();

    // A simple smoke test.
    void locationMapSerializationTest()
    {
        const size_t MapWidth = 32;
        const size_t MapHeight = 64;
        const size_t NumObjects = 8;
        const size_t NumLights = 3;

        LocationMap map;
        map.create(MapWidth, MapHeight);
        for (size_t x = 0; x < MapWidth; x++)
        for (size_t y = 0; y < MapHeight; y++)
        {
            LocationMapCell & cell = map.getCell(Point(x, y));
            cell.setFloorTile(rand() % 100);
        }

        for (size_t i = 0; i < NumObjects; i++)
        {
            LocationMapObject object;
            object.setMapPos(Point(i * 2, i));
            object.setDirection(SouthWest);
            object.setName("Object_" + StringUtils::intToString(i + 1));
            map.addObject(object);
        }

        for (size_t i = 0; i < NumLights; i++)
        {
            Light light;
            light.setComponents(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
            light.setRange(rand() % 512);
            light.setMapPos(Vector2(100.f + i * 100.f, 200.f + i * 200.f));
            map.addLight(light);
        }

        const std::string NodeName("location");

        std::string xml = Serializer::serialize(&map, NodeName);

        LocationMap otherMap;
        Serializer::deserialize(xml, NodeName, &otherMap);

        // TODO: need better tests
        CPPUNIT_ASSERT(MapWidth == otherMap.getWidth());
        CPPUNIT_ASSERT(MapHeight == otherMap.getHeight());
        CPPUNIT_ASSERT(NumObjects == otherMap.getNumObjects());
        CPPUNIT_ASSERT(NumLights == otherMap.getLights().size());
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(LocationMapTests);

