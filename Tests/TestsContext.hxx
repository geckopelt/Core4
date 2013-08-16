#pragma once

#include <string>
#include "Utils/Singleton.hxx"

class TestsContext : public Core4::Singleton<TestsContext>
{
public:
    void setTestDataFolder(const std::string & name)
    {
        m_testDataFolder = name;
    }

    const std::string & getTestDataFolder() const
    {
        return m_testDataFolder;
    }

    void setTempOutputFolder(const std::string & name)
    {
        m_tempOutputFolder = name;
    }

    const std::string & getTempOutputFolder() const
    {
        return m_tempOutputFolder;
    }

    bool init(int argc, char * argv[])
    {
        if (3 == argc)
        {
            setTestDataFolder(argv[1]);
            setTempOutputFolder(argv[2]);
            return true;
        }
        return false;
    }
private:
    std::string m_testDataFolder;
    std::string m_tempOutputFolder;
};