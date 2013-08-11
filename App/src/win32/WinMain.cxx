#include <algorithm>
#include "Utils/Singleton.hxx"
#include "Utils/Guards.hxx"
#include "Configuration/Configuration.hxx"
#include "Logging/LogHelpers.hxx"
#include "Logging/TextFileLogger.hxx"
#include "Win32/Win32App.hxx"
#include "BuildInfo.hxx"
using namespace Core4;

namespace
{
    //------------------------------------------------------------------------------------------------------------
    LRESULT CALLBACK wndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch(message)
        {
            case WM_DESTROY:
                PostQuitMessage(0);
                break;

                /* TODO
            case WM_ACTIVATE:
                CORE4_SINGLE(Win32App).setActive(LOWORD(wParam) != WA_INACTIVE);
                break;

            case WM_KEYDOWN:
                CORE4_SINGLE(C4::GUI).onKeyDown(C4::translateButton(wParam));
                break;

            case WM_CHAR:
                CORE4_SINGLE(C4::GUI).onChar(wParam);
                break;

            case WM_KEYUP:
                CORE4_SINGLE(C4::GUI).onKeyUp(C4::translateButton(wParam));
                break;

            case WM_LBUTTONDOWN:
                CORE4_SINGLE(C4::GUI).onKeyDown(C4::Buttons::MouseLB);
                break;

            case WM_LBUTTONUP:
                CORE4_SINGLE(C4::GUI).onKeyUp(C4::Buttons::MouseLB);
                break;

            case WM_RBUTTONDOWN:
                CORE4_SINGLE(C4::GUI).onKeyDown(C4::Buttons::MouseRB);
                break;

            case WM_RBUTTONUP:
                CORE4_SINGLE(C4::GUI).onKeyUp(C4::Buttons::MouseRB);
                break;

            case WM_MBUTTONDOWN:
                CORE4_SINGLE(C4::GUI).onKeyDown(C4::Buttons::MouseMB);
                break;

            case WM_MBUTTONUP:
                CORE4_SINGLE(C4::GUI).onKeyUp(C4::Buttons::MouseMB);
                break;

            case WM_MOUSEWHEEL:
                if (HIWORD(wParam) > 0 )
                    CORE4_SINGLE(C4::GUI).onKeyDown(C4::Buttons::MWheelUp);
                else
                    CORE4_SINGLE(C4::GUI).onKeyDown(C4::Buttons::MWheelDown);
                break;

            case WM_MOUSEMOVE:
                CORE4_SINGLE(C4::GUI).onMouseMove(C4::Vector2(LOWORD(lParam), HIWORD(lParam)));
                break; */

            default:
                return DefWindowProc(hwnd, message, wParam, lParam);
        }
        return 0;
    }
} // anonymous namespace

bool isSpace(char c) { return c == ' '; }

HWND createWindow(HINSTANCE instance)
{
    CORE4_LOG_SECTION("Creating window");
    const std::string appName = Configuration::getSingleton().getAppName();
    CORE4_LOG_MESSAGE("App name: \"" + appName + "\"");
    std::string wndClassName = appName + "Class";
    std::replace_if(wndClassName.begin(), wndClassName.end(), isSpace, '_');
    CORE4_LOG_MESSAGE("Registering window class: \"" + wndClassName + "\"");

    const UINT DesktopWidth  = GetSystemMetrics(SM_CXMAXIMIZED);
    const UINT DesktopHeight = GetSystemMetrics(SM_CYMAXIMIZED);
    const UINT WindowWidth   = Configuration::getSingleton().screenWidth()  + GetSystemMetrics(SM_CXBORDER) * 2;
    const UINT WindowHeight  = Configuration::getSingleton().screenHeight() + GetSystemMetrics(SM_CYBORDER) * 2 +
                               GetSystemMetrics(SM_CYCAPTION);

    WNDCLASSEX wincl;
    ZeroMemory(&wincl, sizeof(WNDCLASSEX));
    wincl.hInstance     = instance;
    wincl.lpszClassName = wndClassName.c_str();
    wincl.lpfnWndProc   = wndProc;
    wincl.style         = CS_DBLCLKS;
    wincl.cbSize        = sizeof(WNDCLASSEX);
    wincl.hIcon         = NULL; // TODO
    wincl.hIconSm       = NULL; // TODO
    wincl.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName  = NULL;
    wincl.cbClsExtra    = 0;
    wincl.cbWndExtra    = 0;
    wincl.hbrBackground = GetSysColorBrush(COLOR_BACKGROUND);
    CORE4_CHECK(RegisterClassEx(&wincl), "Could not register window class");

    HWND hwnd = CreateWindowEx(0,
                               wndClassName.c_str(),
                               appName.c_str(),
                               WS_OVERLAPPEDWINDOW,
                               (DesktopWidth  - WindowWidth) / 2,
                               (DesktopHeight - WindowHeight) / 2,
                               WindowWidth,
                               WindowHeight,
                               HWND_DESKTOP,
                               NULL,
                               instance,
                               NULL);
    CORE4_CHECK(NULL != hwnd, "Could not create app window");
    return hwnd;
}

void preInit()
{
    CORE4_LOG_MESSAGE("Starting " + std::string(C4_BUILD_INFO));
    const std::string LogType = "txt";
    Logger::getSingleton().setName(Configuration::getSingleton().getAppName());
    Logger::getSingleton().reg<TextFileLogger>(LogType);
    Logger::getSingleton().addListener(LogType);
}

//------------------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE prevInstance,
                   LPSTR arg,
                   int cmdShow)
{
    int exitCode(EXIT_SUCCESS);
    try
    {
        preInit();

        HWND hwnd = createWindow(hInstance);
        ShowWindow(hwnd, cmdShow);
        Win32App::getSingleton().init(hwnd);

        MSG  msg;
        bool gotMsg(false);
        do
        {
            bool isActive = Win32App::getSingleton().isActive();
            gotMsg = isActive ?
                (PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) != 0) :
                (GetMessage(&msg, NULL, 0U, 0U ) != 0);
            if (gotMsg)
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                if (isActive)
                {
                    Win32App::getSingleton().render();
                }
            }
        } while (WM_QUIT != msg.message); // TODO && !CORE4_SINGLE(C4::Engine).needToQuit());
    }
    catch (const std::exception & ex)
    {
        ::MessageBox(HWND_DESKTOP, ex.what(), "Fatal Error", MB_OK | MB_ICONSTOP);
        exitCode = EXIT_FAILURE;
    }
    Win32App::getSingleton().deinit();
    return exitCode;
}

