#pragma once
#include "GameManager.hpp"
#include "Collisions.h"
using namespace Engine2D;

namespace FlappyBird {
    /**
     * @brief Klasa reprezentujaca element punktacji w grze Flappy Bird.
     *
     * Klasa flappyScore dziedziczy po klasach RectangleShape i Collisions, aby dostarczyc
     * funkcjonalnosci zwiazanej z rysowaniem, kolizjami i obsluga punktacji.
     */
    class flappyScore : public virtual Shapes::RectangleShape, public virtual Collisions
    {
    public:
        /**
         * @brief Rysuje element punktacji.
         */
        void Draw() override;

        /**
         * @brief Usuwa obiekt punktacji.
         */
        void deleteMe();

        /**
         * @brief Funkcja wywolywana w momencie kolizji z innym obiektem.
         *
         * @param other Wskaznik do obiektu, z ktorym wystapila kolizja.
         */
        void OnCollisionEnter(Collisions* other) override;

        /**
         * @brief Konstruktor obiektu punktacji Flappy Bird.
         *
         * @param pos Pozycja poczatkowa obiektu.
         */
        flappyScore(Vector2f pos);
    };
} // namespace FlappyBird
