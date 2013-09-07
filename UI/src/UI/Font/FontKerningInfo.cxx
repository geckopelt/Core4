#include "UI/Font/FontKerningInfo.hxx"

namespace Core4
{
    //--------------------------------------------------------------------------------------------
    void FontKerningInfo::addKerningInfo(wchar_t left, wchar_t right, float amount)
    {
        Kernings::iterator it = m_kernings.find(left);
        if (it != m_kernings.end())
        {
            CharacterKernings kernings = it->second;
            kernings[right] = amount;
        }
        else
        {
            CharacterKernings kernings;
            kernings[right]  = amount;
            m_kernings[left] = kernings; 
        }
    }

    //--------------------------------------------------------------------------------------------
    size_t FontKerningInfo::getKerningsCount() const
    {
        return m_kernings.size();
    }

    //--------------------------------------------------------------------------------------------
    float FontKerningInfo::getKerning(wchar_t left, wchar_t right) const
    {
        Kernings::const_iterator it = m_kernings.find(left);
        if (it != m_kernings.end())
        {
            const CharacterKernings & other = it->second;
            CharacterKernings::const_iterator it2 = other.find(right);
            if (it2 != other.end())
            {
                return it2->second;
            }
        }
        return 0.f;
    }
} // namespace Core4
