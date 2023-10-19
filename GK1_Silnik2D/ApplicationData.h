// ApplicationData.h
#pragma once
#include <SFML/System/Vector2.hpp>
#include <string>
using namespace std;
namespace GRUPA3
{
    struct ApplicationData
    {
        string ApplicationName;
        sf::Vector2<int> WindowSize;
        struct ApplicationData(string appName, int Width, int Height);
        struct ApplicationData();
    };
    extern ApplicationData* appData;
    void LoadAppData();
    void createApplicationDataIfNone(ApplicationData* data);
}