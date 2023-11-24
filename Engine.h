#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "ApplicationData.h"
#include <iostream>
#include <string>
#include "InputReader.h"
#include <fstream>
#include "UpdatableObject.h"

#define LOGFILE "log.txt"
#define LOGFILE_OLD "log-old.txt"

namespace Engine2D
{
    /**
     * @brief Klasa reprezentujaca silnik gry.
     *
     * Klasa Engine odpowiada za zarzadzanie glowna petla gry, inicjalizacje, sprzatanie
     * i inne aspekty zarzadzania gra.
     */
    class Engine
    {
    private:
        /**
         * @brief Inicjalizuje gre.
         */
        void InitGame();

        /**
         * @brief Glowna petla gry.
         */
        void EngineLoop();

        bool enabled; ///< Flaga wskazujaca, czy silnik jest wlaczony.

        /**
         * @brief Funkcja czyszczaca zasoby silnika.
         */
        void Cleanup();

        /**
         * @brief Funkcja czyszczaca scene gry.
         */
        void CleanupScene();

        bool keyboardInputEnabled; ///< Flaga wskazujaca, czy obsluga klawiatury jest wlaczona.
        bool mouseInputEnabled; ///< Flaga wskazujaca, czy obsluga myszy jest wlaczona.
        sf::Vector2i mousePosition; ///< Aktualna pozycja myszy.

        /**
         * @brief Inicjalizuje logi.
         */
        static void InitLogs();

        /**
         * @brief Funkcja inicjalizujaca nowa gre.
         */
        void SpawnGame();

        /**
         * @brief Usuwa obiekty oczekujace na usuniecie.
         */
        void removeAwaitingObjects();

    protected:
        static Engine* singleton; ///< Jedynka instancja silnika.

    public:
        static float Gravity; ///< Stala grawitacyjna.

        /**
         * @brief Konstruktor silnika.
         */
        Engine();

        /**
         * @brief Destruktor silnika.
         */
        ~Engine();

        /**
         * @brief Wypisuje log do pliku.
         *
         * @param log Tekst logu do wypisania.
         */
        static void PrintLog(const std::string& log);

        sf::RenderWindow* Window; ///< Okno gry.

        /**
         * @brief Pobiera jedyna instancje silnika.
         *
         * @param flag Flaga (nieokreslona) - bez znaczenia w komentarzach.
         * @return Wskaznik do jedynego obiektu klasy Engine.
         */
        static Engine* GetSingleton(bool);

        double deltaTime; ///< Czas, ktory uplynal miedzy klatkami gry.

        /**
         * @brief Konwertuje kat na radiany.
         *
         * @param angle Kat w stopniach.
         * @return Wartosc kata w radianach.
         */
        static double AngleToRad(float angle);

        /**
         * @brief Sprawdza, czy klawisz zostal nacisniety.
         *
         * @param key Klawisz do sprawdzenia.
         * @return true, jesli klawisz zostal nacisniety, w przeciwnym razie false.
         */
        bool isKeyTriggered(sf::Keyboard::Key key);

        sf::Font baseFont; ///< Czcionka uzywana w grze.
    };
} // namespace Engine2D
