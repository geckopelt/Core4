// TODO: a dirty header-reference hack. Current Serialization implementation should be improved to avoid such problems.
#include "Serialization/Serializeable.hxx"

#include "Tiles/TileBasics.hxx"

namespace Core4
{
    const float TileBasics::TileWidth  = 64;
    const float TileBasics::TileHeight = 32;

    //--------------------------------------------------------------------------------------------------------
    const Point TileBasics::getNeighbourCell(const Point & from, IsoDirection direction)
    {
        int x = from.x();
        int y = from.y();
	    switch(direction)
	    {
            case North:
    		    y -= 2;
    		    break;
            case NorthEast:
	            x += (y & 1);
	    		y--;
		        break;
	        case East:
                x++;
                break;
            case SouthEast:
                x += (y & 1);
                y++;
                break;
            case South:
                y += 2;
                break;
            case SouthWest:
			    x += ((y & 1) - 1);
			    y++;
		        break;
	        case West:
	            x--;
	            break;
	        case NorthWest:
	            x += ((y & 1) - 1);
                y--;
		        break;
            default:
                break;
	    }
	    return Point(x, y);
    }

    //--------------------------------------------------------------------------------------------------------
    const Vector2 TileBasics::getTileScreenPos(const Point & tile)
    {
	    Vector2 pos;
        pos.setX(tile.x() * TileWidth + (tile.y() & 1) * (TileWidth / 2));
	    pos.setY(tile.y() * (TileHeight / 2));
	    return pos;
    }
} // namespace Core4