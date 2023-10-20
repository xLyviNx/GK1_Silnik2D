// ApplicationData.h
#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
namespace GRUPA3
{
    enum DisplayMode
    {
        Windowed,
        Fullscreen,
    };
    struct ApplicationData
    {
        sf::String ApplicationName;
        sf::Vector2<int> WindowSize;
        DisplayMode displayMode;
        int maxFramerate;
        struct ApplicationData(sf::String appName, int Width, int Height, DisplayMode dispMode, int maxFps);
        struct ApplicationData();
    };
    extern ApplicationData* appData;
    void LoadAppData();
    void createApplicationDataIfNone(ApplicationData* data);

}