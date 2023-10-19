#include "ApplicationData.h"
#include <fstream>
#define ApplicationDataFile "applicationData"
namespace GRUPA3
{
    ApplicationData* appData = nullptr;
    void LoadAppData()
	{
        if (appData==NULL)
            appData = new ApplicationData();
        //createApplicationDataIfNone(appData);
        fstream file(ApplicationDataFile, ios::in);
        if (file.is_open())
        {
            getline(file, appData->ApplicationName);
            file >> appData->WindowSize.x >> appData->WindowSize.y;
        }

        file.close();
	}
    void createApplicationDataIfNone(ApplicationData* data)
    {
        fstream file(ApplicationDataFile, ios::in);
        if (!file.is_open())
        {
            file.open(ApplicationDataFile, ios::out);
            file << data->ApplicationName << endl;
            file << data->WindowSize.x << " " << data->WindowSize.y << endl;
            file.close();
        }
    }
    ApplicationData::ApplicationData(string appName, int Width, int Height)
    {
        this->ApplicationName = appName;
        this->WindowSize = sf::Vector2<int>(Width, Height);
    }
    ApplicationData::ApplicationData()
    {
        this->ApplicationName = "Application";
        this->WindowSize = sf::Vector2<int>(1280, 720);
    }
}