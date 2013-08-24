#include <fstream>
#include "Location/IsoDirection.hxx"
#include "Utils/Guards.hxx"
#include "Logging/Logger.hxx"
#include "Logging/StdOutLogger.hxx"
#include "Logging/LogHelpers.hxx"
#include "Image/TargaLoader.hxx"
#include "Image/ImageManipulator.hxx"

using namespace Core4;

//--------------------------------------------------------------------------------------------------------
void setupLogger()
{
    const std::string loggerName("stdout");
    Logger::getSingleton().reg<StdOutLogger>(loggerName);
    Logger::getSingleton().addListener(loggerName);
}

//--------------------------------------------------------------------------------------------------------
const std::string directionToString(const IsoDirection direction)
{
    switch(direction)
    {
        case North:
            return "North";
        case NorthEast:
            return "NorthEast";
        case East:
            return "East";
        case SouthEast:
            return "SouthEast";
        case South:
            return "South";
        case SouthWest:
            return "SouthWest";
        case West:
            return "West";
        case NorthWest:
            return "NorthWest";
        case UnknownDirection:
            return "UnknownDirection";
        default:
            throw std::logic_error("Unknown direction");
    }
}

//--------------------------------------------------------------------------------------------------------
void writeMouseMap(const std::string & filename, size_t width, size_t height, const std::vector<IsoDirection> & directions)
{
    std::ofstream dest(filename);
    const size_t MaxPerLine(8);
    size_t perLine(0);
    dest << "// Auto-generated, do not edit" << std::endl;
    std::vector<IsoDirection>::const_iterator last = (--directions.end()); 
    for (std::vector<IsoDirection>::const_iterator it = directions.begin(); it != directions.end(); it++)
    {
        dest << directionToString(*it);
        if (it != last)
        {
            dest << ", ";
        }
        if (perLine < MaxPerLine - 1)
            perLine++;
        else
        {
            perLine = 0;
            dest << std::endl;
        }
    }
}

//--------------------------------------------------------------------------------------------------------
IsoDirection fromColor(const Color & color)
{
    IsoDirection direction;
    if (Color::Red == color)
        direction = NorthWest;
    else if (Color::Green == color)
        direction = NorthEast;
    else if (Color::Yellow == color)
        direction = SouthEast;
    else if (Color::Blue == color)
        direction = SouthWest;
    else if (Color::Red == color)
        direction = NorthWest;
    else if (Color::White == color)
        direction = UnknownDirection;
    else
        throw std::invalid_argument("Unknown color found");
    return direction;
}

//--------------------------------------------------------------------------------------------------------
std::vector<IsoDirection> createMouseMap(const std::string & filename, size_t & width, size_t & height)
{
    std::vector<unsigned char> data(TargaLoader().loadImage(filename, width, height));
    ImageManipulator im(data, width, height);

    std::vector<IsoDirection> mouseMap;
    mouseMap.resize(width * height);
    for (size_t y = 0; y < im.getHeight(); y++)
    for (size_t x = 0; x < im.getWidth(); x++)
    {
        mouseMap[y * width + x] = fromColor(im.getPixel(x, y));
    }
    return mouseMap;
}

//--------------------------------------------------------------------------------------------------------
int main(int argc, char * argv[])
{
    setupLogger();
    try
    {
        CORE4_CHECK(3 == argc, "Usage: MouseMapGenerator <MouseMapFile.tga> <MouseMapFile.hxx>");
        const std::string inputFile(argv[1]);
        const std::string outputFile(argv[2]);
        CORE4_LOG_MESSAGE("Generating mousemap: \"" + inputFile + "\" -> \"" + outputFile + "\"");

        size_t width(0), height(0);
        std::vector<IsoDirection> mouseMap(createMouseMap(inputFile, width, height));
        writeMouseMap(outputFile, width, height, mouseMap);
    }
    catch (const std::exception & ex)
    {
        CORE4_LOG_ERROR(ex.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}