#include <map>
#include "Utils/Singleton.hxx"
#include "win32/Win32Common.hxx"
#include "win32/ButtonTranslator.hxx"

namespace Core4
{
    namespace
    {
        class ButtonMapper : public Singleton<ButtonMapper>
        {
            std::map<int, Buttons::Type> m_map;
        public:
            ButtonMapper()
            {
                m_map[VK_BACK]    = Buttons::Backspace;
                m_map[VK_TAB]     = Buttons::Tab;
                m_map[VK_RETURN]  = Buttons::Enter;
                m_map[VK_SHIFT]   = Buttons::Shift;
                m_map[VK_CONTROL] = Buttons::Control;
                m_map[VK_MENU]    = Buttons::Alt;
                m_map[VK_PAUSE]   = Buttons::Pause;
                m_map[VK_CAPITAL] = Buttons::CapsLock;
                m_map[VK_ESCAPE]  = Buttons::Escape;
                m_map[VK_SPACE]   = Buttons::Space;
                m_map[VK_PRIOR]   = Buttons::PageUp;
                m_map[VK_NEXT]    = Buttons::PageDown;
                m_map[VK_END]     = Buttons::End;
                m_map[VK_HOME]    = Buttons::Home;
                m_map[VK_LEFT]    = Buttons::Left;
                m_map[VK_UP]      = Buttons::Up;
                m_map[VK_RIGHT]   = Buttons::Right;
                m_map[VK_DOWN]    = Buttons::Down;
                m_map[VK_PRINT]   = Buttons::PrintScreen;
                m_map[VK_INSERT]  = Buttons::Insert;
                m_map[VK_DELETE]  = Buttons::Delete;
                m_map[0x30] = Buttons::Zero;
                m_map[0x31] = Buttons::One;
                m_map[0x32] = Buttons::Two;
                m_map[0x33] = Buttons::Three;
                m_map[0x34] = Buttons::Four;
                m_map[0x35] = Buttons::Five;
                m_map[0x36] = Buttons::Six;
                m_map[0x37] = Buttons::Seven;
                m_map[0x38] = Buttons::Eight;
                m_map[0x39] = Buttons::Nine;
                m_map[0x41] = Buttons::A;
                m_map[0x42] = Buttons::B;
                m_map[0x43] = Buttons::C;
                m_map[0x44] = Buttons::D;
                m_map[0x45] = Buttons::E;
                m_map[0x46] = Buttons::F;
                m_map[0x47] = Buttons::G;
                m_map[0x48] = Buttons::H;
                m_map[0x49] = Buttons::I;
                m_map[0x4A] = Buttons::J;
                m_map[0x4B] = Buttons::K;
                m_map[0x4C] = Buttons::L;
                m_map[0x4D] = Buttons::M;
                m_map[0x4E] = Buttons::N;
                m_map[0x4F] = Buttons::O;
                m_map[0x50] = Buttons::P;
                m_map[0x51] = Buttons::Q;
                m_map[0x52] = Buttons::R;
                m_map[0x53] = Buttons::S;
                m_map[0x54] = Buttons::T;
                m_map[0x55] = Buttons::U;
                m_map[0x56] = Buttons::V;
                m_map[0x57] = Buttons::W;
                m_map[0x58] = Buttons::X;
                m_map[0x59] = Buttons::Y;
                m_map[0x5A] = Buttons::Z;
                m_map[VK_NUMPAD0] = Buttons::Numpad0;
                m_map[VK_NUMPAD1] = Buttons::Numpad1;
                m_map[VK_NUMPAD2] = Buttons::Numpad2;
                m_map[VK_NUMPAD3] = Buttons::Numpad3;
                m_map[VK_NUMPAD4] = Buttons::Numpad4;
                m_map[VK_NUMPAD5] = Buttons::Numpad5;
                m_map[VK_NUMPAD6] = Buttons::Numpad6;
                m_map[VK_NUMPAD7] = Buttons::Numpad7;
                m_map[VK_NUMPAD8] = Buttons::Numpad8;
                m_map[VK_NUMPAD9] = Buttons::Numpad9;
                m_map[VK_MULTIPLY]  = Buttons::Multiply;
                m_map[VK_ADD]       = Buttons::Add;
                m_map[VK_SEPARATOR] = Buttons::Separator;
                m_map[VK_SUBTRACT]  = Buttons::Subtract;
                m_map[VK_DECIMAL]   = Buttons::Decimal;
                m_map[VK_DIVIDE]    = Buttons::Divide;
                m_map[VK_F1] = Buttons::F1;
                m_map[VK_F2] = Buttons::F2;
                m_map[VK_F3] = Buttons::F3;
                m_map[VK_F4] = Buttons::F4;
                m_map[VK_F5] = Buttons::F5;
                m_map[VK_F6] = Buttons::F6;
                m_map[VK_F7] = Buttons::F7;
                m_map[VK_F8] = Buttons::F8;
                m_map[VK_F9] = Buttons::F9;
                m_map[VK_F10] = Buttons::F10;
                m_map[VK_NUMLOCK] = Buttons::NumLock; 
                m_map[VK_SCROLL]  = Buttons::ScrollLock;
            };

            Buttons::Type translate(int vk) const
            {
                std::map<int, Buttons::Type>::const_iterator it = m_map.find(vk);
                return it == m_map.end() ? Buttons::Unknown : it->second;
            }
        };
    }

    //------------------------------------------------------------------------------------------------------------
    Buttons::Type ButtonTranslator::translateButton(int virtualKey)
    {
        return ButtonMapper::getSingleton().translate(virtualKey);
    }
} // namespace Core4

