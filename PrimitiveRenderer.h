#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "Calculations.h"
using namespace std;
namespace Engine2D {
	/**
	 * @brief klasa sluzaca do obslugi rysowania prymitywow
	 */
	class PrimitiveRenderer
	{
	protected:
	public:
		sf::Color Color;///<kolor obiektu
		float Width;
		/**
		 * @brief metoda sluzaca do rysowania pojedynczej linii wedlug algorytmu napisanego recznej
		 *
		 * @param renderWindow okno w ktorym ma byc wyrenderowana linia
		 * @param A obiekt typu sf::Vector2f majacy wskazac pierwsza wspolrzedna do narysowania
		 * @param B obiekt typu sf::Vector2f majacy wskazac druga wspolrzedna do narysowania
		 * @param Width szerokosc linii
		 * @param Color kolor linii
		 */
		static void DrawSingleLine(sf::RenderWindow* renderWindow, sf::Vector2f A, sf::Vector2f B, float Width, sf::Color Color);
		/**
		 * @brief funkcja rysujaca linie za pomoca metod biblioteki SFML
		 *
		 * @param posA	sf::Vector wskazujacy poczatek linii
		 * @param posB sf::Vector wskazujacy koniec linii
		 * @param angle kat lini
		 * @param Color kolor linii
		 */
		static void DrawSingleLineSFML(sf::Vector2f posA, sf::Vector2f posB, float angle, sf::Color Color);
		/**
		 * @brief metoda rysujaca kolko
		 *
		 * @param center sf::Vector wskazujacy na srodek kola
		 * @param radius promien kola
		 * @param color kolor
		 */
		static void DrawCircle(sf::Vector2f center, float radius, sf::Color color);

		static void DrawCircle(sf::RenderWindow* renderWindow, sf::Vector2f center, std::vector<sf::Vector2f> points, sf::Color color);
		/**
		 * @brief funkcja rysujaca linie po Vectorze punktow
		 *
		 * @param renderWindow okno w ktorym ma sie wyrenderowac linia
		 * @param points Vector z punktami
		 * @param Width szerokosc linii
		 * @param Color kolor linii
		 */
		static void PointLine(sf::RenderWindow* renderWindow, std::vector<sf::Vector2f>* points, float Width, sf::Color Color);
		static void PointLine(sf::RenderWindow* renderWindow, sf::Vector2f points[], int pointsCount, float Width, sf::Color Color);
		static void DrawEllipse(sf::Vector2f center, float RX, float RY, sf::Color color);
		PrimitiveRenderer() : Color(sf::Color::White), Width(1.0f) {};
		PrimitiveRenderer(sf::Color color, float width);
	};

	/**
	 * @brief klasa reprezentujaca obiekt Point2D sluzacy do wskazywania wspolrzednych.
	 */
	class Point2D : public PrimitiveRenderer
	{
	public:
		sf::Vector2f Position;
		sf::Vector2f getPosition();
		/**
		 * @brief metoda ustawiajaca pozycje punktu
		 *
		 * @param newPos sf::Vector wskazujacy nowa pozycje
		 */
		void setPosition(sf::Vector2f newPos);
		void DrawPointSFML();

		Point2D(sf::Color color, float width, sf::Vector2f position);
	};
}