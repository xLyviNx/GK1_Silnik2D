// ApplicationData.h
#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
namespace Engine2D
{
    /**
     * @brief Enumeracja reprezentuj�ca r�ne tryby wy�wietlania aplikacji.
     */
    enum DisplayMode
    {
        Windowed,    ///< Tryb okienkowy.
        Fullscreen,  ///< Tryb pe�noekranowy.
    };

    /**
     * @brief Struktura przechowuj�ca dane aplikacji.
     */
    struct ApplicationData
    {
        sf::String ApplicationName; ///< Nazwa aplikacji.
        sf::Vector2<int> WindowSize; ///< Rozmiar okna aplikacji.
        DisplayMode displayMode; ///< Tryb wy�wietlania.
        int maxFramerate; ///< Maksymalna liczba klatek na sekund�.

        /**
         * @brief Konstruktor struktury ApplicationData z parametrami.
         * @param appName Nazwa aplikacji.
         * @param Width Szeroko�� okna.
         * @param Height Wysoko�� okna.
         * @param dispMode Tryb wy�wietlania.
         * @param maxFps Maksymalna liczba klatek na sekund�.
         */
        ApplicationData(sf::String appName, int Width, int Height, DisplayMode dispMode, int maxFps);

        /**
         * @brief Domy�lny konstruktor struktury ApplicationData.
         */
        ApplicationData();
    };

    /**
     * @brief Wska�nik na obiekt ApplicationData, przechowuj�cy globalne dane aplikacji.
     */
    extern ApplicationData* appData;

    /**
     * @brief Funkcja odpowiedzialna za wczytanie danych aplikacji.
     */
    void LoadAppData();

    /**
     * @brief Funkcja tworz�ca obiekt ApplicationData, je�li nie istnieje.
     * @param data Wska�nik na dane aplikacji.
     */
    void createApplicationDataIfNone(ApplicationData* data);
}
