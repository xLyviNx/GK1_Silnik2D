#include "ApplicationData.h"
#include <fstream>
#include <iostream>
#define ApplicationDataFile "applicationData"
namespace GRUPA3
{
    ApplicationData* appData = nullptr;
    void LoadAppData()
    {
        if (appData == NULL)
            appData = new ApplicationData();
        createApplicationDataIfNone(appData);
        fstream file(ApplicationDataFile, ios::in);
        if (file.is_open())
        {
            file >> appData->WindowSize.x >> appData->WindowSize.y;
            int dm = 0;
            file >> dm;
            appData->displayMode = (DisplayMode)dm;
            file >> appData->maxFramerate;
        }

        file.close();
    }
    void createApplicationDataIfNone(ApplicationData* data)
    {
        fstream file(ApplicationDataFile, ios::in);
        if (!file.is_open())
        {
            file.open(ApplicationDataFile, ios::out);
            file << data->WindowSize.x << " " << data->WindowSize.y << endl;
            file << (int)appData->displayMode << endl;
            file << (int)appData->maxFramerate << endl;
            file.close();
        }
    }
    ApplicationData::ApplicationData(sf::String appName, int Width, int Height, DisplayMode dispMode, int maxFps)
    {
        this->ApplicationName = appName;
        this->WindowSize = sf::Vector2<int>(Width, Height);
        this->displayMode = dispMode;
        this->maxFramerate = maxFps;
    }
    ApplicationData::ApplicationData()
    {
        this->ApplicationName = "Application";
        this->WindowSize = sf::Vector2<int>(1280, 720);
        this->displayMode = Windowed;
        this->maxFramerate = 144;
    }
}