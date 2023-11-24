#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <set>

using namespace std;
using namespace sf;

namespace Engine2D
{
    /**
     * @brief Klasa reprezentujaca obiekt gry.
     *
     * Klasa GameObject zawiera podstawowe funkcje i wlasciwosci
     * dla wszystkich obiektow w grze.
     */
    class GameObject
    {
        /**
         * @brief Inicjalizuje obiekt gry.
         */
        void Initialize();

    public:
        static vector<GameObject*> All; ///< Wektor wszystkich obiektow gry.
        string name; ///< Nazwa obiektu.

        /**
         * @brief Usuwa obiekt gry.
         */
        virtual void deleteMe();

        /**
         * @brief Konstruktor domyslny klasy GameObject.
         */
        GameObject();

        /**
         * @brief Konstruktor klasy GameObject.
         *
         * @param name Nazwa obiektu.
         */
        GameObject(std::string name);

        /**
         * @brief Destruktor klasy GameObject.
         */
        ~GameObject();

        bool isRemoving; ///< Flaga informujaca, czy obiekt jest usuwany.
    };
} // namespace Engine2D
