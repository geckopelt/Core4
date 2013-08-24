#include "Tiles/TileBasics.hxx"
#include "Tiles/MouseMap.hxx"

namespace Core4
{
    namespace 
    {
        IsoDirection directions[] = 
        {
            #include "Tiles/MouseMapDirections.hxx"
        };
    }

    //--------------------------------------------------------------------------------------------------------
    MouseMap::MouseMap()
    {
        const size_t MouseMapSize(static_cast<size_t>(TileBasics::TileWidth * TileBasics::TileHeight));
        m_mouseMap.resize(MouseMapSize);
        memcpy(&m_mouseMap[0], directions, sizeof(IsoDirection) * MouseMapSize);
    }

    //--------------------------------------------------------------------------------------------------------
    const Point MouseMap::screenToTile(const Vector2 & screen, const Vector2 & scrollPos) const
    {
        const size_t TileWidth  = static_cast<size_t>(TileBasics::TileWidth);
        const size_t TileHeight = static_cast<size_t>(TileBasics::TileHeight);

        // 1. Screen to world
        float x(screen.x() + scrollPos.x());
        float y(screen.y() + scrollPos.y());
        
        // 2. Mousemap coords
        int coarseX(static_cast<int>(x) / TileWidth);
        int coarseY(static_cast<int>(y) / TileHeight);
        int fineX(static_cast<int>(x) % TileWidth);
        int fineY(static_cast<int>(y) % TileHeight);

	    if (fineX < 0)
	    {
            fineX += TileWidth;
            coarseX--;
	    }
	    if (fineY < 0)
	    {
		    fineY += TileHeight;
            coarseY--;
	    }

	    // 3. Coarse tilewalk
	    Point map;
        
        // move north
	    while (coarseY < 0)
	    {
		    coarseY++;
            map = TileBasics::getNeighbourCell(map, North);
	    }
	    // move south
	    while (coarseY > 0)
	    {
		    coarseY--;
		    map = TileBasics::getNeighbourCell(map, South);
	    }
	    // move east
	    while (coarseX > 0)
	    {
		    coarseX--;
		    map = TileBasics::getNeighbourCell(map, East);
	    }
	    // move west
	    while (coarseX < 0)
	    {
		    coarseX++;
		    map = TileBasics::getNeighbourCell(map, West);
	    }

        // 4. Fine tilewalk
        IsoDirection direction = m_mouseMap.at(fineY * TileWidth + fineX);
        if (direction == NorthWest ||
            direction == NorthEast ||
            direction == SouthWest ||
            direction == SouthEast)
        {
            map = TileBasics::getNeighbourCell(map, direction);
        }
	    return map;
    }
} // namespace Core4


