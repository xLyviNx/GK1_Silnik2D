#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameObject.h"

namespace Engine2D
{
    /**
     * @brief Klasa bazowa dla obiektow rysowalnych.
     *
     * Klasa DrawableObject umozliwia rysowanie obiektow, dziedziczy po klasie GameObject, z usuwaniem/czyszczeniem obiektow.
     */
    class DrawableObject : public virtual GameObject
    {
    public:
        bool visible; ///< Flaga okreslajaca widocznosc obiektu.
        static std::vector<DrawableObject*> All; ///< Wektor zawierajacy wszystkie obiekty rysowalne.
        sf::RenderWindow* window; ///< Wskaznik do okna renderowania.

        /**
         * @brief Wirtualna funkcja rysujaca obiekt.
         */
        virtual void Draw();

        /**
         * @brief Konstruktor domyslny klasy DrawableObject.
         */
        DrawableObject();

        /**
         * @brief Funkcja rysujaca obiekt z podana tekstura.
         *
         * @param texture Tekstura do narysowania.
         */
        virtual void Draw(sf::Texture texture);

        /**
         * @brief Wirtualny destruktor klasy DrawableObject.
         */
        ~DrawableObject();

        bool isUi; ///< Flaga okreslajaca, czy obiekt jest elementem interfejsu uzytkownika.

        /**
         * @brief Wirtualna funkcja usuwajaca obiekt.
         *
         * Nadpisuje funkcje z klasy bazowej GameObject.
         */
        virtual void deleteMe() override;
    };
} // namespace Engine2D
