#pragma once
#include "UpdatableObject.h"
#include "Collisions.h"
#include "ShapeObject.h"
#include "Engine.h"
#include "Player.h"
#include "GameManager.hpp"
#include "Transform.h"
#include "BitmapHandler.h"

using namespace Engine2D;
namespace FlappyBird
{

    class GameManager; // Deklaracja wstepna klasy GameManager
    /**
     * @brief Klasa reprezentujaca przeszkode w grze Flappy Bird.
     *
     * Klasa flappyObstacle dziedziczy po roznych klasach, aby dostarczyc funkcjonalnosci zwiazanej
     * z transformacja, kolizjami, ksztaltem, obsluga obiektow bitowych oraz aktualizacja.
     */
    class flappyObstacle : public virtual TransformableObject, public virtual Collisions, public virtual Shapes::RectangleShape, public virtual BitmapObject, public virtual UpdatableObject
    {
    private:
        static float obstacleSpeed; ///< Predkosc przeszkody.
        static int minY; ///< Minimalna wartosc Y dla pozycji przeszkody.
        static int maxY; ///< Maksymalna wartosc Y dla pozycji przeszkody.

    public:
        bool isTopOne; ///< Flaga okreslajaca, czy przeszkoda jest gorna.

        /**
         * @brief Aktualizuje stan przeszkody.
         *
         * @param deltaTime Czas od ostatniej aktualizacji.
         */
        virtual void Update(float deltaTime);

        /**
         * @brief Rozpoczyna dzialanie przeszkody.
         */
        virtual void Start();

        /**
         * @brief Usuwa obiekt przeszkody.
         */
        virtual void deleteMe() override;

        /**
         * @brief Rysuje przeszkode.
         */
        void Draw() override;

        /**
         * @brief Ustawia wlasciwosci przeszkody.
         */
        void SetProperties();

        /**
         * @brief Konstruktor przeszkody Flappy Bird.
         *
         * @param obstacleman Wskaznik do obiektu klasy GameManager.
         */
        flappyObstacle(GameManager* obstacleman);

        /**
         * @brief Destruktor przeszkody Flappy Bird.
         */
        ~flappyObstacle();
    };
} // namespace FlappyBird
