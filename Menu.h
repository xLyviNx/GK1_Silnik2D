#pragma once

#include "UpdatableObject.h"
#include "ShapeObject.h"
#include "Engine.h"
#include "Transform.h"
#include "DrawableObject.h"

#define MAX_NUMBER_OF_OPTIONS 2

using namespace Engine2D;
namespace FlappyBird {
    /**
     * @brief Klasa reprezentujaca menu w grze.
     *
     * Klasa Menu dziedziczy po roznych klasach, aby dostarczyc funkcjonalnosci zwiazanej
     * z aktualizacja, ksztaltem, obsluga interakcji wejsciowych oraz rysowaniem.
     */
    class Menu : public virtual UpdatableObject, public virtual TransformableObject, public virtual InputReader, public virtual DrawableObject
    {
    private:
        int selectedOptionIndex; ///< Indeks aktualnie wybranej opcji w menu.
        sf::Font font; ///< Czcionka uzywana do wyswietlania tekstu w menu.
        sf::Text menu[MAX_NUMBER_OF_OPTIONS]; ///< Tekst dla poszczegolnych opcji w menu.
        bool returnToMenu; ///< Flaga okreslajaca, czy nalezy wrocic do menu.
        bool endGame; ///< Flaga okreslajaca, czy gra powinna zakonczyc sie.

    public:
        bool menuActive; ///< Flaga okreslajaca, czy menu jest aktywne.

        /**
         * @brief Konstruktor menu.
         *
         * @param width Szerokosc menu.
         * @param height Wysokosc menu.
         */
        Menu(float width, float height);

        /**
         * @brief Przesuwa w gore aktualnie zaznaczona opcje w menu.
         */
        void MoveUp();

        /**
         * @brief Przesuwa w dol aktualnie zaznaczona opcje w menu.
         */
        void MoveDown();

        /**
         * @brief Zwraca indeks nacisnietej opcji.
         *
         * @return Indeks nacisnietej opcji w menu.
         */
        int getPressedOption();

        /**
         * @brief Usuwa obiekt menu.
         */
        virtual void deleteMe() override;

        /**
         * @brief Rysuje menu.
         */
        virtual void Draw() override;

        /**
         * @brief Obsluguje nacisniecie klawisza.
         *
         * @param keyPressed Nacisniety klawisz.
         */
        virtual void KeyPressed(sf::Keyboard::Key keyPressed) override;

        /**
         * @brief Obsluguje zwolnienie klawisza.
         *
         * @param keyPressed Zwolniony klawisz.
         */
        virtual void KeyReleased(sf::Keyboard::Key keyPressed) override;

        /**
         * @brief Obsluguje nacisniecie przycisku myszy.
         *
         * @param mouseEvent Informacje o nacisnieciu przycisku myszy.
         */
        virtual void MousePressed(sf::Event::MouseButtonEvent mouseEvent) override;

        /**
         * @brief Obsluguje zwolnienie przycisku myszy.
         *
         * @param mouseEvent Informacje o zwolnieniu przycisku myszy.
         */
        virtual void MouseReleased(sf::Event::MouseButtonEvent mouseEvent) override;
    };

}