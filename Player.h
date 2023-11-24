#pragma once
#include "InputReader.h"
#include "Transform.h"
#include "ShapeObject.h"
#include "Collisions.h"
#include "BitmapObject.h"

namespace Engine2D
{
    /**
     * @brief Klasa reprezentujaca gracza.
     *
     * Klasa Player dziedziczy po roznych klasach, aby dostarczyc funkcjonalnosci zwiazanych z obsluga wejscia,
     * transformacja, rysowaniem ksztaltu, obsluga kolizji, obsluga obiektow bitowych oraz aktualizacja.
     */
    class Player : public virtual Shapes::RectangleShape, public virtual InputReader, public virtual UpdatableObject, public virtual Collisions, public virtual BitmapObject
    {
    private:
        bool jumped; ///< Flaga okreslajaca, czy gracz wykonal skok.

    protected:
        bool isTopView; ///< Flaga okreslajaca, czy widok gracza jest z gory.
        float movementSpeed; ///< Predkosc poruszania sie gracza.
        float gravityForce; ///< Sila grawitacyjna dzialajaca na gracza.
        bool isGrounded; ///< Flaga okreslajaca, czy gracz jest na ziemi.
        Vector2f movement; ///< Wektor kierunku poruszania sie gracza.

    public:
        float jumpForce; ///< Sila skoku gracza.
        bool enableGravity; ///< Flaga okreslajaca, czy dziala grawitacja na gracza.

        /**
         * @brief Wirtualna funkcja usuwajaca obiekt gracza.
         *
         * Nadpisuje funkcje z klasy bazowej TransformableObject.
         */
        virtual void deleteMe() override;

        /**
         * @brief Konstruktor klasy Player.
         *
         * @param name Nazwa obiektu.
         * @param position Pozycja poczatkowa gracza.
         */
        Player(std::string name, Vector2f position);

        /**
         * @brief Funkcja inicjujaca dzialanie gracza.
         *
         * Nadpisuje funkcje z klasy bazowej TransformableObject.
         */
        virtual void Start() override;

        /**
         * @brief Funkcja obslugujaca poruszanie sie gracza.
         *
         * @param engine Wskaznik do obiektu klasy Engine.
         * @param deltaTime Czas od ostatniej aktualizacji.
         */
        virtual void Movement(Engine* engine, float deltaTime);

        /**
         * @brief Funkcja aktualizujaca stan gracza.
         *
         * @param deltaTime Czas od ostatniej aktualizacji.
         */
        virtual void Update(float deltaTime) override;

        /**
         * @brief Funkcja obslugujaca zwolnienie klawisza na klawiaturze.
         *
         * Nadpisuje funkcje z klasy bazowej InputReader.
         *
         * @param keyReleased Zwolniony klawisz.
         */
        virtual void KeyReleased(sf::Keyboard::Key keyReleased) override;

        /**
         * @brief Funkcja obslugujaca nacisniecie klawisza na klawiaturze.
         *
         * Nadpisuje funkcje z klasy bazowej InputReader.
         *
         * @param keyPressed Nacisniety klawisz.
         */
        virtual void KeyPressed(sf::Keyboard::Key keyPressed) override;

        /**
         * @brief Funkcja obslugujaca zderzenie z innym obiektem.
         *
         * Nadpisuje funkcje z klasy bazowej Collisions.
         *
         * @param col Obiekt, z ktorym doszlo do zderzenia.
         */
        virtual void OnCollisionEnter(Collisions* col) override;

        /**
         * @brief Funkcja obslugujaca pozostawanie w kolizji z innym obiektem.
         *
         * Nadpisuje funkcje z klasy bazowej Collisions.
         *
         * @param col Obiekt, z ktorym zachodzi kolizja.
         */
        virtual void OnCollisionStay(Collisions* col) override;

        /**
         * @brief Funkcja obslugujaca opuszczenie kolizji z innym obiektem.
         *
         * Nadpisuje funkcje z klasy bazowej Collisions.
         *
         * @param col Obiekt, z ktorym opuszczono kolizje.
         */
        virtual void OnCollisionExit(Collisions* col) override;

        bool canJumpMidAir; ///< Flaga okreslajaca, czy gracz moze skakac w powietrzu.

        /**
         * @brief Funkcja przemieszczajaca gracza.
         *
         * @param position Pozycja poczatkowa gracza.
         * @param dir Kierunek przemieszczenia.
         * @param collided Wskaznik na zmienna okreslajaca, czy doszlo do zderzenia.
         */
        void Move(Vector2f position, Vector2f dir, bool* collided);

        /**
         * @brief Funkcja przemieszczajaca gracza.
         *
         * @param position Pozycja poczatkowa gracza.
         * @param dir Kierunek przemieszczenia.
         * @param collided Wskaznik na zmienna okreslajaca, czy doszlo do zderzenia.
         * @param collisionsMoveOut Flaga okreslajaca, czy unikac kolizji.
         */
        void Move(Vector2f position, Vector2f dir, bool* collided, bool collisionsMoveOut);

        /**
         * @brief Funkcja rysujaca gracza.
         */
        virtual void Draw() override;
    };
} // namespace Engine2D
