#include "Utils/Guards.hxx"
#include "Types/Color.hxx"
#include "Logging/Logger.hxx"
#include "Logging/LogHelpers.hxx"
#include "Image/ImageManipulator.hxx"
#include "Image/TargaWriter.hxx"

#include "Fx/Noise.hxx"

// TODO: implement a sprite/tile set generator

//----------------------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    try
    {
        using namespace Core4;

        size_t width = 512;
        size_t height = 256;

        std::list<IEffect*> effects;
        effects.push_back(new Noise(Color(0, 128, 0, 255), 32));

        ImageManipulator im = ImageManipulator(width, height);

        for (std::list<IEffect*>::iterator it = effects.begin(); it != effects.end(); it++)
        {
            (*it)->applyEffect(im);
        }
        TargaWriter().writeImage("out.tga", im.getRawData(), width, height);

        for (std::list<IEffect*>::iterator it = effects.begin(); it != effects.end(); it++)
        {
            delete (*it);
        }
    }
    catch (const std::exception & ex)
    {
        CORE4_LOG_ERROR(ex.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
