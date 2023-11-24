// ApplicationData.h
#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
namespace Engine2D
{
    /**
     * @brief Enumeracja reprezentuj¹ca ró¿ne tryby wyœwietlania aplikacji.
     */
    enum DisplayMode
    {
        Windowed,    ///< Tryb okienkowy.
        Fullscreen,  ///< Tryb pe³noekranowy.
    };

    /**
     * @brief Struktura przechowuj¹ca dane aplikacji.
     */
    struct ApplicationData
    {
        sf::String ApplicationName; ///< Nazwa aplikacji.
        sf::Vector2<int> WindowSize; ///< Rozmiar okna aplikacji.
        DisplayMode displayMode; ///< Tryb wyœwietlania.
        int maxFramerate; ///< Maksymalna liczba klatek na sekundê.

        /**
         * @brief Konstruktor struktury ApplicationData z parametrami.
         * @param appName Nazwa aplikacji.
         * @param Width Szerokoœæ okna.
         * @param Height Wysokoœæ okna.
         * @param dispMode Tryb wyœwietlania.
         * @param maxFps Maksymalna liczba klatek na sekundê.
         */
        ApplicationData(sf::String appName, int Width, int Height, DisplayMode dispMode, int maxFps);

        /**
         * @brief Domyœlny konstruktor struktury ApplicationData.
         */
        ApplicationData();
    };

    /**
     * @brief WskaŸnik na obiekt ApplicationData, przechowuj¹cy globalne dane aplikacji.
     */
    extern ApplicationData* appData;

    /**
     * @brief Funkcja odpowiedzialna za wczytanie danych aplikacji.
     */
    void LoadAppData();

    /**
     * @brief Funkcja tworz¹ca obiekt ApplicationData, jeœli nie istnieje.
     * @param data WskaŸnik na dane aplikacji.
     */
    void createApplicationDataIfNone(ApplicationData* data);
}
