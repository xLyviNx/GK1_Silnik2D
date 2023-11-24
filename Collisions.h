#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include "Transform.h"
#include <vector>
namespace Engine2D
{
	class Collisions;

	/**
	 * @brief Struktura przechowujaca informacje o trafieniu promienia w detekcji kolizji.
	 *
	 * Struktura ta zawiera informacje o tym, czy promien trafil w obiekt Collisions, ktory
	 * koliduje, oraz dodatkowe dane, takie jak punkt trafienia, punkt przed trafieniem, celowy
	 * koniec promienia i obiekt kolidujacy.
	 */
	struct RaycastHit
	{
		bool hit; ///< Czy promien trafil w obiekt kolidujacy.
		Collisions* collidedObject; ///< Wskaznik na obiekt Collisions, z ktorym zachodzi kolizja.
		sf::Vector2f point; ///< Punkt trafienia promienia.
		sf::Vector2f pointBefore; ///< Punkt przed trafieniem.
		sf::Vector2f targetEnd; ///< Celowy koniec promienia.

		/**
		 * @brief Konstruktor struktury RaycastHit.
		 *
		 * @param hits Czy promien trafil.
		 * @param collided Wskaznik na obiekt Collisions, z ktorym zachodzi kolizja.
		 * @param hpoint Punkt trafienia promienia.
		 * @param end Celowy koniec promienia.
		 * @param pointBef Punkt przed trafieniem.
		 */
		RaycastHit(bool hits, Collisions* collided, sf::Vector2f hpoint, sf::Vector2f end, sf::Vector2f pointBef)
			: hit(hits), collidedObject(collided), point(hpoint), targetEnd(end), pointBefore(pointBef)
		{
		}
	};
	/**
	 * @brief Klasa reprezentujaca obiekt odpowiedzialny za obsluge kolizji.
	 *
	 * Klasa Collisions zawiera funkcje do obslugi detekcji kolizji oraz reakcji na nie.
	 * Jest dziedziczona po klasie GameObject, co oznacza, ze moze byc uzywana jako
	 * podstawowy element w strukturze gry.
	 */
	class Collisions : public virtual GameObject
	{
	private:
		float oldAngle; ///< Przechowuje poprzedni kat obiektu.
		float oldSin; ///< Przechowuje sinus poprzedniego kata obiektu.
		float oldCos; ///< Przechowuje cosinus poprzedniego kata obiektu.

	protected:
		sf::FloatRect globalBounds; ///< Ograniczenia globalne obiektu w postaci prostokata.

	public:
		bool enabled; ///< Flaga wskazujaca, czy obiekt jest wlaczony.

		/**
		 * @brief Konstruktor klasy Collisions.
		 *
		 * Konstruktor inicjalizuje obiekt klasy Collisions ustawiajac poczatkowe wartosci
		 * dla zmiennych skladowych.
		 */
		Collisions();
		/**
		 * @brief Konstruktor klasy Collisions z podanym obiektem TransformableObject.
		 *
		 * Inicjalizuje obiekt klasy Collisions z podanym obiektem transformacji.
		 *
		 * @param transform Wskaznik na obiekt TransformableObject.
		 */
		Collisions(TransformableObject* transform);

		/**
		 * @brief Destruktor klasy Collisions.
		 *
		 * Zwalnia zasoby zwiazane z obiektem klasy Collisions.
		 */
		~Collisions();

		/**
		 * @brief Lista wszystkich obiektow Collisions.
		 */
		static std::vector<Collisions*> All;

		/**
		 * @brief Funkcja usuwajaca obiekt Collisions.
		 *
		 * Usuwa obiekt Collisions (zamiast bezposredniego delete).
		 */
		virtual void deleteMe() override;

		/**
		 * @brief Zwraca prostokat ograniczajacy obiekt.
		 *
		 * @return Prostokat ograniczajacy obiekt.
		 */
		sf::FloatRect getGlobalBounds();

		/**
		 * @brief Sprawdza, czy obiekt koliduje z prostokatem o podanych wymiarach.
		 *
		 * @param otherRect Prostokat do sprawdzenia kolizji.
		 * @return True, jesli zachodzi kolizja, w przeciwnym razie False.
		 */
		bool Collides(sf::FloatRect otherRect);

		/**
		 * @brief Sprawdza, czy obiekt koliduje z ktorymkolwiek innym obiektem Collisions.
		 *
		 * @return Wskaznik na obiekt, z ktorym zachodzi kolizja; nullptr, jesli nie zachodzi kolizja.
		 */
		Collisions* CollidesWithAny();

		/**
		 * @brief Funkcja statyczna do sprawdzania kolizji z okreslonym punktem.
		 *
		 * Sprawdza kolizje z danym punktem, z mozliwoscia ignorowania jednego obiektu.
		 *
		 * @param point Punkt do sprawdzenia kolizji.
		 * @param ignoreOne Wskaznik na obiekt Collisions, ktory ma byc zignorowany.
		 * @return Wskaznik na obiekt Collisions, z ktorym zachodzi kolizja; nullptr, jesli nie zachodzi kolizja.
		 */
		static Collisions* PointCollide(sf::Vector2f point, Collisions* ignoreOne);

		/**
		 * @brief Wskaznik na obiekt transformacji zwiazanego z obiektem.
		 */
		TransformableObject* myTransform;

		/**
		 * @brief Funkcja statyczna do wykrywania kolizji promienia z obiektami Collisions.
		 *
		 * Sprawdza kolizje promienia pomiedzy punktem startowym a punktem koncowym z obiektami Collisions,
		 * z mozliwoscia ignorowania okreslonych obiektow.
		 *
		 * @param start Punkt poczatkowy promienia.
		 * @param end Punkt koncowy promienia.
		 * @param ignore Zbior obiektow do zignorowania podczas sprawdzania kolizji.
		 * @return Struktura RaycastHit zawierajaca informacje o trafieniu promienia.
		 */
		static RaycastHit Raycast(sf::Vector2f start, sf::Vector2f end, std::set<Collisions*> ignore);

		/**
		 * @brief Funkcja statyczna do wykrywania kolizji promienia z obiektami Collisions (jako caly obiekt).
		 *
		 * Sprawdza kolizje promienia z okreslonym obiektem Collisions, przy uwzglednieniu pozycji i
		 * punktu koncowego promienia.
		 *
		 * @param self Obiekt Collisions sprawdzajacy kolizje.
		 * @param selfPosition Aktualna pozycja obiektu.
		 * @param end Punkt koncowy promienia.
		 * @param ignore Zbior obiektow do zignorowania podczas sprawdzania kolizji.
		 * @return Struktura RaycastHit zawierajaca informacje o trafieniu promienia.
		 */
		static RaycastHit RaycastBox(Collisions* self, sf::Vector2f selfPosition, sf::Vector2f end, std::set<Collisions*> ignore);

		/**
		 * @brief Funkcja wywolywana, gdy zachodzi kolizja z innym obiektem.
		 *
		 * @param other Wskaznik na obiekt Collisions, z ktorym zachodzi kolizja.
		 */
		virtual void OnCollisionEnter(Collisions* other);

		/**
		 * @brief Funkcja wywolywana, gdy kolizja z innym obiektem trwa.
		 *
		 * @param other Wskaznik na obiekt Collisions, z ktorym zachodzi kolizja.
		 */
		virtual void OnCollisionStay(Collisions* other);

		/**
		 * @brief Funkcja wywolywana, gdy kolizja z innym obiektem konczy sie.
		 *
		 * @param other Wskaznik na obiekt Collisions, z ktorym konczy sie kolizja.
		 */
		virtual void OnCollisionExit(Collisions* other);
		/**
		 * @brief Wektor przechowujacy aktualne kolizje z innymi obiektami Collisions.
		 */
		std::vector<Collisions*> currentCollisions;

		/**
		 * @brief Funkcja statyczna do przesuwania obiektu na zewnatrz kolizji.
		 *
		 * Przesuwa obiekt na zewnatrz kolizji, uwzgledniajac tylko kolizje z okreslonym obiektem.
		 *
		 * @param coll Wskaznik na obiekt Collisions.
		 * @param position Aktualna pozycja obiektu.
		 * @return Nowa pozycja obiektu po przesunieciu na zewnatrz kolizji.
		 */
		static sf::Vector2f moveOutOfCollision(Collisions* coll, sf::Vector2f position);

		/**
		 * @brief Sprawdza kolizje z innym obiektem Collisions.
		 *
		 * @param other Wskaznik na obiekt Collisions.
		 * @return True, jesli zachodzi kolizja, w przeciwnym razie False.
		 */
		bool Collides(Collisions* other);

		/**
		 * @brief Sprawdza kolizje z danym punktem.
		 *
		 * @param point Punkt do sprawdzenia kolizji.
		 * @return True, jesli zachodzi kolizja, w przeciwnym razie False.
		 */
		bool Collides(sf::Vector2f point);

		/**
		 * @brief Funkcja do przesuwania obiektu na zewnatrz kolizji z uwzglednieniem predkosci.
		 *
		 * Przesuwa obiekt na zewnatrz kolizji, uwzgledniajac predkosc obiektu.
		 *
		 * @param coll Wskaznik na obiekt Collisions.
		 * @param position Aktualna pozycja obiektu.
		 * @param velocity Wektor predkosci obiektu.
		 * @return Nowa pozycja obiektu po przesunieciu na zewnatrz kolizji z uwzglednieniem predkosci.
		 */
		sf::Vector2f moveOutOfCollision(Collisions* coll, sf::Vector2f position, sf::Vector2f velocity);

		/**
		 * @brief Sprawdza kolizje z danym zbiorem punktow (wierzcholkow).
		 *
		 * @param corners Wektor zawierajacy punkty do sprawdzenia kolizji.
		 * @return True, jesli zachodzi kolizja, w przeciwnym razie False.
		 */
		bool Collides(std::vector<sf::Vector2f> corners);

		/**
		 * @brief Oblicza pozycje wierzcholkow obiektu na podstawie szerokosci, wysokosci, kata i pozycji.
		 *
		 * @param width Szerokosc obiektu.
		 * @param height Wysokosc obiektu.
		 * @param angle Kat obrotu obiektu.
		 * @param position Pozycja obiektu.
		 */
		void CalculateCorners(float width, float height, float angle, const sf::Vector2f position);

		/**
		 * @brief Wypisuje wspolrzedne wierzcholkow obiektu.
		 *
		 * @param corners Wektor zawierajacy wspolrzedne wierzcholkow.
		 */
		static void printCorners(const std::vector<sf::Vector2f>& corners);

		/**
		 * @brief Rysuje wspolrzedne wierzcholkow obiektu.
		 *
		 * @param corners Wektor zawierajacy wspolrzedne wierzcholkow.
		 */
		static void drawCorners(const std::vector<sf::Vector2f>& corners);

		/**
		 * @brief Wektor przechowujacy wspolrzedne wierzcholkow obiektu.
		 */
		std::vector<Vector2f> myCorners;

		/*Vector2f left;
		Vector2f right;
		Vector2f bottom;
		Vector2f top;*/
	};

}