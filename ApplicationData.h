// ApplicationData.h
#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
namespace Engine2D
{
    /**
     * @brief Enumeracja reprezentujaca rozne tryby wyswietlania aplikacji.
     */
    enum DisplayMode
    {
        Windowed,    ///< Tryb okienkowy.
        Fullscreen,  ///< Tryb pelnoekranowy.
    };

    /**
     * @brief Struktura przechowujaca dane aplikacji.
     */
    struct ApplicationData
    {
        sf::String ApplicationName; ///< Nazwa aplikacji.
        sf::Vector2<int> WindowSize; ///< Rozmiar okna aplikacji.
        DisplayMode displayMode; ///< Tryb wyswietlania.
        int maxFramerate; ///< Maksymalna liczba klatek na sekunde.

        /**
         * @brief Konstruktor struktury ApplicationData z parametrami.
         * @param appName Nazwa aplikacji.
         * @param Width Szerokosc okna.
         * @param Height Wysokosc okna.
         * @param dispMode Tryb wyswietlania.
         * @param maxFps Maksymalna liczba klatek na sekunde.
         */
        ApplicationData(sf::String appName, int Width, int Height, DisplayMode dispMode, int maxFps);

        /**
         * @brief Domyslny konstruktor struktury ApplicationData.
         */
        ApplicationData();
    };

    /**
     * @brief Wskaznik na obiekt ApplicationData, przechowujacy globalne dane aplikacji.
     */
    extern ApplicationData* appData;

    /**
     * @brief Funkcja odpowiedzialna za wczytanie danych aplikacji.
     */
    void LoadAppData();

    /**
     * @brief Funkcja tworzaca obiekt ApplicationData, jesli nie istnieje.
     * @param data Wskaznik na dane aplikacji.
     */
    void createApplicationDataIfNone(ApplicationData* data);
}
