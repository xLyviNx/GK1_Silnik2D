#pragma once
#include "DrawableObject.h"
#include "Transform.h"
#include "PrimitiveRenderer.h"
#include "Engine.h"
#include "Collisions.h"

namespace Engine2D
{
    /**
     * @brief Klasa bazowa dla obiektow ksztaltow.
     *
     * Klasa ShapeObject dziedziczy po klasach TransformableObject, DrawableObject, Collisions,
     * dostarczajac funkcjonalnosci zwiazane z transformacja, rysowaniem i obsluga kolizji dla obiektow ksztaltow.
     */
    class ShapeObject : public virtual TransformableObject, public virtual DrawableObject, public virtual Collisions
    {
    protected:
        /**
         * @brief Wskaznik na okno.
         */
        sf::RenderWindow* renderWindow;

    public:
        /**
         * @brief Konstruktor domyslny klasy ShapeObject.
         */
        ShapeObject();

        /**
         * @brief Konstruktor klasy ShapeObject z podana pozycja.
         *
         * @param position Pozycja poczatkowa obiektu.
         */
        ShapeObject(Vector2f position);

        /**
         * @brief Konstruktor klasy ShapeObject z podana nazwa i pozycja.
         *
         * @param name Nazwa obiektu.
         * @param position Pozycja poczatkowa obiektu.
         */
        ShapeObject(std::string name, Vector2f position);

        /**
         * @brief Wirtualna funkcja usuwajaca obiekt.
         *
         * Nadpisuje funkcje z klasy bazowej GameObject.
         */
        virtual void deleteMe() override;

        /**
         * @brief Wirtualna funkcja rysujaca obiekt.
         *
         * Nadpisuje funkcje z klasy bazowej DrawableObject.
         */
        virtual void Draw() override;
    };

    namespace Shapes
    {
        /**
         * @brief Klasa reprezentujaca prostokatny ksztalt.
         *
         * Klasa RectangleShape dziedziczy po klasie ShapeObject, dostarczajac funkcjonalnosci zwiazanej z rysowaniem
         * prostokatnego ksztaltu oraz obsluga zmiany jego rozmiaru.
         */
        class RectangleShape : public virtual ShapeObject
        {
        protected:
            float localA; ///< Lokalna dlugosc boku A prostokata.
            float localB; ///< Lokalna dlugosc boku B prostokata.
            float worldA; ///< Globalna dlugosc boku A prostokata.
            float worldB; ///< Globalna dlugosc boku B prostokata.
            float outlinewidth; ///< Grubosc obwodki prostokata.

        public:
            sf::RectangleShape rectShape; ///< Prostokatny ksztalt.
            Color fillColor; ///< Kolor wypelnienia prostokata.
            Color color; ///< Kolor obwodki prostokata.

            /**
             * @brief Wirtualna funkcja wywolywana po zmianie wlasciwosci prostokata.
             *
             * Nadpisuje funkcje z klasy bazowej TransformableObject.
             */
            virtual void PropertiesChanged() override;

            /**
             * @brief Konstruktor prostokatnego ksztaltu.
             *
             * @param position Pozycja poczatkowa prostokata.
             * @param A Dlugosc boku A prostokata.
             * @param B Dlugosc boku B prostokata.
             * @param color Kolor obwodki prostokata.
             * @param width Grubosc obwodki prostokata.
             */
            RectangleShape(Vector2f position, float A, float B, Color color, float width);

            /**
             * @brief Konstruktor prostokatnego ksztaltu z pelnymi parametrami.
             *
             * @param position Pozycja poczatkowa prostokata.
             * @param A Dlugosc boku A prostokata.
             * @param B Dlugosc boku B prostokata.
             * @param color Kolor obwodki prostokata.
             * @param fillColor Kolor wypelnienia prostokata.
             * @param width Grubosc obwodki prostokata.
             */
            RectangleShape(Vector2f position, float A, float B, Color color, Color fillColor, float width);

            /**
             * @brief Konstruktor prostokatnego ksztaltu z pelnymi parametrami i nazwa.
             *
             * @param name Nazwa prostokata.
             * @param position Pozycja poczatkowa prostokata.
             * @param A Dlugosc boku A prostokata.
             * @param B Dlugosc boku B prostokata.
             * @param color Kolor obwodki prostokata.
             * @param width Grubosc obwodki prostokata.
             */
            RectangleShape(std::string name, Vector2f position, float A, float B, Color color, float width);

            /**
             * @brief Konstruktor prostokatnego ksztaltu z pelnymi parametrami, nazwa i kolorem wypelnienia.
             *
             * @param name Nazwa prostokata.
             * @param position Pozycja poczatkowa prostokata.
             * @param A Dlugosc boku A prostokata.
             * @param B Dlugosc boku B prostokata.
             * @param color Kolor obwodki prostokata.
             * @param fillColor Kolor wypelnienia prostokata.
             * @param width Grubosc obwodki prostokata.
             */
            RectangleShape(std::string name, Vector2f position, float A, float B, Color color, Color fillColor, float width);

            /**
             * @brief Wirtualna funkcja usuwajaca obiekt prostokata.
             *
             * Nadpisuje funkcje z klasy bazowej ShapeObject.
             */
            void deleteMe() override;

            /**
             * @brief Wirtualna funkcja rysujaca prostokat.
             *
             * Nadpisuje funkcje z klasy bazowej ShapeObject.
             */
            void Draw() override;

            /**
             * @brief Zmienia rozmiar prostokata.
             *
             * @param A Nowa dlugosc boku A.
             * @param B Nowa dlugosc boku B.
             */
            void ChangeSize(float A, float B);
        };

        /**
         * @brief Klasa reprezentujaca okragly ksztalt.
         *
         * Klasa CircleShape dziedziczy po klasie ShapeObject, dostarczajac funkcjonalnosci zwiazanej z rysowaniem
         * okraglego ksztaltu oraz obsluga zmiany jego rozmiaru.
         */
        class CircleShape : public virtual ShapeObject
        {
        private:
            float localRadius; ///< Lokalny promien okregu.
            float worldRadius; ///< Globalny promien okregu.
            float width; ///< Grubosc obwodki okregu.
            sf::CircleShape circleShape; ///< Okragly ksztalt.

        public:
            Color color; ///< Kolor obwodki okregu.
            Color fillColor; ///< Kolor wypelnienia okregu.

            /**
             * @brief Wirtualna funkcja wywolywana po zmianie wlasciwosci okregu.
             *
             * Nadpisuje funkcje z klasy bazowej TransformableObject.
             */
            virtual void PropertiesChanged() override;

            /**
             * @brief Konstruktor okraglego ksztaltu.
             *
             * @param position Pozycja poczatkowa okregu.
             * @param Rad Promien okregu.
             * @param width Grubosc obwodki okregu.
             * @param color Kolor obwodki okregu.
             * @param fillColor Kolor wypelnienia okregu.
             */
            CircleShape(Vector2f position, float Rad, float width, Color color, Color fillColor);

            /**
             * @brief Konstruktor okraglego ksztaltu z pelnymi parametrami.
             *
             * @param name Nazwa okregu.
             * @param position Pozycja poczatkowa okregu.
             * @param R Promien okregu.
             * @param color Kolor obwodki okregu.
             */
            CircleShape(std::string name, Vector2f position, float R, Color color);

            /**
             * @brief Wirtualna funkcja usuwajaca obiekt okregu.
             *
             * Nadpisuje funkcje z klasy bazowej ShapeObject.
             */
            void deleteMe() override;

            /**
             * @brief Wirtualna funkcja rysujaca okrag.
             *
             * Nadpisuje funkcje z klasy bazowej ShapeObject.
             */
            void Draw() override;
        };
    } // namespace Shapes
} // namespace Engine2D
