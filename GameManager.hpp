#pragma once
#include "fb_Obstacle.hpp"
#include "UpdatableObject.h"
#include "Calculations.h"
#include "Menu.h"
#include "flappyScore.hpp"

namespace FlappyBird
{

    class flappyObstacle; // Deklaracja wstepna klasy flappyObstacle
    /**
     * @brief Klasa reprezentujaca menadzera gry w Flappy Bird.
     *
     * Klasa GameManager dziedziczy po klasie UpdatableObject, co umozliwia
     * jej aktualizacje w glownej petli gry.
     */
    class GameManager : public virtual Engine2D::UpdatableObject
    {
    public:
        static int minY; ///< Minimalna wartosc Y dla pozycji przeszkod.
        static int maxY; ///< Maksymalna wartosc Y dla pozycji przeszkod.
        static int gap; ///< Rozmiar luki miedzy przeszkodami.

        /**
         * @brief Konstruktor klasy GameManager.
         */
        GameManager();

        /**
         * @brief Destruktor klasy GameManager.
         */
        ~GameManager();

        Menu* GameMenu; ///< Wskaznik do obiektu menu gry.
        bool inGame; ///< Flaga informujaca, czy gra jest w trakcie.
        static GameManager* singleton; ///< Jedyny obiekt klasy GameManager.
        std::vector<flappyObstacle*> obstacles; ///< Wektor przeszkod w grze.

        /**
         * @brief Funkcja generujaca przeszkody w grze.
         */
        void SpawnObstacles();

        /**
         * @brief Aktualizuje stan gry w zaleznosci od uplywu czasu.
         *
         * @param deltaTime Czas od ostatniej aktualizacji.
         */
        void Update(float deltaTime) override;

        /**
         * @brief Funkcja wywolywana w przypadku zakonczenia gry.
         */
        void GameOver();

        /**
         * @brief Rozpoczyna nowa gre.
         */
        void StartGame();

        /**
         * @brief Funkcja usuwajaca obiekt klasy GameManager.
         */
        virtual void deleteMe() override;

        Player* GamePlayer; ///< Wskaznik do obiektu gracza.
        int points; ///< Aktualna liczba punktow w grze.
    };
} // namespace FlappyBird
