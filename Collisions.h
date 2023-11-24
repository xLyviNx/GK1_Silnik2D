#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include "Transform.h"
#include <vector>
namespace Engine2D
{
	/**
	 * @brief Klasa reprezentuj�ca obiekt odpowiedzialny za obs�ug� kolizji.
	 *
	 * Klasa Collisions zawiera funkcje do obs�ugi detekcji kolizji oraz reakcji na nie.
	 * Jest dziedziczona po klasie GameObject, co oznacza, �e mo�e by� u�ywana jako
	 * podstawowy element w strukturze gry.
	 */
	class Collisions;

	/**
	 * @brief Struktura przechowuj�ca informacje o trafieniu promienia w detekcji kolizji.
	 *
	 * Struktura ta zawiera informacje o tym, czy promie� trafi� w obiekt Collisions, kt�ry
	 * koliduje, oraz dodatkowe dane, takie jak punkt trafienia, punkt przed trafieniem, celowy
	 * koniec promienia i obiekt koliduj�cy.
	 */
	struct RaycastHit
	{
		bool hit; ///< Czy promie� trafi� w obiekt koliduj�cy.
		Collisions* collidedObject; ///< Wska�nik na obiekt Collisions, z kt�rym zachodzi kolizja.
		sf::Vector2f point; ///< Punkt trafienia promienia.
		sf::Vector2f pointBefore; ///< Punkt przed trafieniem.
		sf::Vector2f targetEnd; ///< Celowy koniec promienia.

		/**
		 * @brief Konstruktor struktury RaycastHit.
		 *
		 * @param hits Czy promie� trafi�.
		 * @param collided Wska�nik na obiekt Collisions, z kt�rym zachodzi kolizja.
		 * @param hpoint Punkt trafienia promienia.
		 * @param end Celowy koniec promienia.
		 * @param pointBef Punkt przed trafieniem.
		 */
		RaycastHit(bool hits, Collisions* collided, sf::Vector2f hpoint, sf::Vector2f end, sf::Vector2f pointBef)
			: hit(hits), collidedObject(collided), point(hpoint), targetEnd(end), pointBefore(pointBef)
		{
		}
	};

	class Collisions : public virtual GameObject
	{
	private:
		float oldAngle; ///< Przechowuje poprzedni k�t obiektu.
		float oldSin; ///< Przechowuje sinus poprzedniego k�ta obiektu.
		float oldCos; ///< Przechowuje cosinus poprzedniego k�ta obiektu.

	protected:
		sf::FloatRect globalBounds; ///< Ograniczenia globalne obiektu w postaci prostok�ta.

	public:
		bool enabled; ///< Flaga wskazuj�ca, czy obiekt jest w��czony.

		/**
		 * @brief Konstruktor klasy Collisions.
		 *
		 * Konstruktor inicjalizuje obiekt klasy Collisions ustawiaj�c pocz�tkowe warto�ci
		 * dla zmiennych sk�adowych.
		 */
		Collisions();
		/**
		 * @brief Konstruktor klasy Collisions z podanym obiektem TransformableObject.
		 *
		 * Inicjalizuje obiekt klasy Collisions z podanym obiektem transformacji.
		 *
		 * @param transform Wska�nik na obiekt TransformableObject.
		 */
		Collisions(TransformableObject* transform);

		/**
		 * @brief Destruktor klasy Collisions.
		 *
		 * Zwalnia zasoby zwi�zane z obiektem klasy Collisions.
		 */
		~Collisions();

		/**
		 * @brief Lista wszystkich obiekt�w Collisions.
		 */
		static std::vector<Collisions*> All;

		/**
		 * @brief Funkcja usuwaj�ca obiekt Collisions.
		 *
		 * Usuwa obiekt Collisions (zamiast bezpo�redniego delete).
		 */
		virtual void deleteMe() override;

		/**
		 * @brief Zwraca prostok�t ograniczaj�cy obiekt.
		 *
		 * @return Prostok�t ograniczaj�cy obiekt.
		 */
		sf::FloatRect getGlobalBounds();

		/**
		 * @brief Sprawdza, czy obiekt koliduje z prostok�tem o podanych wymiarach.
		 *
		 * @param otherRect Prostok�t do sprawdzenia kolizji.
		 * @return True, je�li zachodzi kolizja, w przeciwnym razie False.
		 */
		bool Collides(sf::FloatRect otherRect);

		/**
		 * @brief Sprawdza, czy obiekt koliduje z kt�rymkolwiek innym obiektem Collisions.
		 *
		 * @return Wska�nik na obiekt, z kt�rym zachodzi kolizja; nullptr, je�li nie zachodzi kolizja.
		 */
		Collisions* CollidesWithAny();

		/**
		 * @brief Funkcja statyczna do sprawdzania kolizji z okre�lonym punktem.
		 *
		 * Sprawdza kolizj� z danym punktem, z mo�liwo�ci� ignorowania jednego obiektu.
		 *
		 * @param point Punkt do sprawdzenia kolizji.
		 * @param ignoreOne Wska�nik na obiekt Collisions, kt�ry ma by� zignorowany.
		 * @return Wska�nik na obiekt Collisions, z kt�rym zachodzi kolizja; nullptr, je�li nie zachodzi kolizja.
		 */
		static Collisions* PointCollide(sf::Vector2f point, Collisions* ignoreOne);

		/**
		 * @brief Wska�nik na obiekt transformacji zwi�zanego z obiektem.
		 */
		TransformableObject* myTransform;

		/**
		 * @brief Funkcja statyczna do wykrywania kolizji promienia z obiektami Collisions.
		 *
		 * Sprawdza kolizj� promienia pomi�dzy punktem startowym a punktem ko�cowym z obiektami Collisions,
		 * z mo�liwo�ci� ignorowania okre�lonych obiekt�w.
		 *
		 * @param start Punkt pocz�tkowy promienia.
		 * @param end Punkt ko�cowy promienia.
		 * @param ignore Zbi�r obiekt�w do zignorowania podczas sprawdzania kolizji.
		 * @return Struktura RaycastHit zawieraj�ca informacje o trafieniu promienia.
		 */
		static RaycastHit Raycast(sf::Vector2f start, sf::Vector2f end, std::set<Collisions*> ignore);

		/**
		 * @brief Funkcja statyczna do wykrywania kolizji promienia z obiektami Collisions (jako ca�y obiekt).
		 *
		 * Sprawdza kolizj� promienia z okre�lonym obiektem Collisions, przy uwzgl�dnieniu pozycji i
		 * punktu ko�cowego promienia.
		 *
		 * @param self Obiekt Collisions sprawdzaj�cy kolizj�.
		 * @param selfPosition Aktualna pozycja obiektu.
		 * @param end Punkt ko�cowy promienia.
		 * @param ignore Zbi�r obiekt�w do zignorowania podczas sprawdzania kolizji.
		 * @return Struktura RaycastHit zawieraj�ca informacje o trafieniu promienia.
		 */
		static RaycastHit RaycastBox(Collisions* self, sf::Vector2f selfPosition, sf::Vector2f end, std::set<Collisions*> ignore);

		/**
		 * @brief Funkcja wywo�ywana, gdy zachodzi kolizja z innym obiektem.
		 *
		 * @param other Wska�nik na obiekt Collisions, z kt�rym zachodzi kolizja.
		 */
		virtual void OnCollisionEnter(Collisions* other);

		/**
		 * @brief Funkcja wywo�ywana, gdy kolizja z innym obiektem trwa.
		 *
		 * @param other Wska�nik na obiekt Collisions, z kt�rym zachodzi kolizja.
		 */
		virtual void OnCollisionStay(Collisions* other);

		/**
		 * @brief Funkcja wywo�ywana, gdy kolizja z innym obiektem ko�czy si�.
		 *
		 * @param other Wska�nik na obiekt Collisions, z kt�rym ko�czy si� kolizja.
		 */
		virtual void OnCollisionExit(Collisions* other);
		/**
		 * @brief Wektor przechowuj�cy aktualne kolizje z innymi obiektami Collisions.
		 */
		std::vector<Collisions*> currentCollisions;

		/**
		 * @brief Funkcja statyczna do przesuwania obiektu na zewn�trz kolizji.
		 *
		 * Przesuwa obiekt na zewn�trz kolizji, uwzgl�dniaj�c tylko kolizje z okre�lonym obiektem.
		 *
		 * @param coll Wska�nik na obiekt Collisions.
		 * @param position Aktualna pozycja obiektu.
		 * @return Nowa pozycja obiektu po przesuni�ciu na zewn�trz kolizji.
		 */
		static sf::Vector2f moveOutOfCollision(Collisions* coll, sf::Vector2f position);

		/**
		 * @brief Sprawdza kolizj� z innym obiektem Collisions.
		 *
		 * @param other Wska�nik na obiekt Collisions.
		 * @return True, je�li zachodzi kolizja, w przeciwnym razie False.
		 */
		bool Collides(Collisions* other);

		/**
		 * @brief Sprawdza kolizj� z danym punktem.
		 *
		 * @param point Punkt do sprawdzenia kolizji.
		 * @return True, je�li zachodzi kolizja, w przeciwnym razie False.
		 */
		bool Collides(sf::Vector2f point);

		/**
		 * @brief Funkcja do przesuwania obiektu na zewn�trz kolizji z uwzgl�dnieniem pr�dko�ci.
		 *
		 * Przesuwa obiekt na zewn�trz kolizji, uwzgl�dniaj�c pr�dko�� obiektu.
		 *
		 * @param coll Wska�nik na obiekt Collisions.
		 * @param position Aktualna pozycja obiektu.
		 * @param velocity Wektor pr�dko�ci obiektu.
		 * @return Nowa pozycja obiektu po przesuni�ciu na zewn�trz kolizji z uwzgl�dnieniem pr�dko�ci.
		 */
		sf::Vector2f moveOutOfCollision(Collisions* coll, sf::Vector2f position, sf::Vector2f velocity);

		/**
		 * @brief Sprawdza kolizj� z danym zbiorem punkt�w (wierzcho�k�w).
		 *
		 * @param corners Wektor zawieraj�cy punkty do sprawdzenia kolizji.
		 * @return True, je�li zachodzi kolizja, w przeciwnym razie False.
		 */
		bool Collides(std::vector<sf::Vector2f> corners);

		/**
		 * @brief Oblicza pozycje wierzcho�k�w obiektu na podstawie szeroko�ci, wysoko�ci, k�ta i pozycji.
		 *
		 * @param width Szeroko�� obiektu.
		 * @param height Wysoko�� obiektu.
		 * @param angle K�t obrotu obiektu.
		 * @param position Pozycja obiektu.
		 */
		void CalculateCorners(float width, float height, float angle, const sf::Vector2f position);

		/**
		 * @brief Wypisuje wsp�rz�dne wierzcho�k�w obiektu.
		 *
		 * @param corners Wektor zawieraj�cy wsp�rz�dne wierzcho�k�w.
		 */
		static void printCorners(const std::vector<sf::Vector2f>& corners);

		/**
		 * @brief Rysuje wsp�rz�dne wierzcho�k�w obiektu.
		 *
		 * @param corners Wektor zawieraj�cy wsp�rz�dne wierzcho�k�w.
		 */
		static void drawCorners(const std::vector<sf::Vector2f>& corners);

		/**
		 * @brief Wektor przechowuj�cy wsp�rz�dne wierzcho�k�w obiektu.
		 */
		std::vector<Vector2f> myCorners;

		/*Vector2f left;
		Vector2f right;
		Vector2f bottom;
		Vector2f top;*/
	};

}