#pragma once
#include "SFML/Graphics.hpp"
#define M_PI 3.14159265358979323846

namespace Engine2D
{
    /**
     * @brief Klasa zawieraj¹ca ró¿ne matematyczne operacje.
     */
    class Calculations {
    public:
        /**
         * @brief Normalizuje wektor sf::Vector2f.
         * @param Vector Wektor do znormalizowania.
         * @return Znormalizowany wektor sf::Vector2f.
         */
        static sf::Vector2f Vector2f_Normalize(sf::Vector2f Vector);

        /**
         * @brief Oblicza d³ugoœæ wektora sf::Vector2f.
         * @param Vector Wektor, którego d³ugoœæ ma byæ obliczona.
         * @return D³ugoœæ wektora.
         */
        static float Vector2f_Magnitude(sf::Vector2f Vector);

        /**
         * @brief Oblicza iloczyn skalarny dwóch wektorów sf::Vector2f.
         * @param a Pierwszy wektor.
         * @param b Drugi wektor.
         * @return Iloczyn skalarny.
         */
        static float dotProduct(const sf::Vector2f& a, const sf::Vector2f& b);

        /**
         * @brief Generuje losow¹ liczbê ca³kowit¹ w okreœlonym zakresie.
         * @param min Dolna granica zakresu.
         * @param max Górna granica zakresu.
         * @return Wygenerowana liczba losowa.
         */
        static int Random(int min, int max);
    };
}
