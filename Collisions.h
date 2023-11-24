#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include "Transform.h"
#include <vector>
namespace Engine2D
{
	/**
	 * @brief Klasa reprezentuj¹ca obiekt odpowiedzialny za obs³ugê kolizji.
	 *
	 * Klasa Collisions zawiera funkcje do obs³ugi detekcji kolizji oraz reakcji na nie.
	 * Jest dziedziczona po klasie GameObject, co oznacza, ¿e mo¿e byæ u¿ywana jako
	 * podstawowy element w strukturze gry.
	 */
	class Collisions;

	/**
	 * @brief Struktura przechowuj¹ca informacje o trafieniu promienia w detekcji kolizji.
	 *
	 * Struktura ta zawiera informacje o tym, czy promieñ trafi³ w obiekt Collisions, który
	 * koliduje, oraz dodatkowe dane, takie jak punkt trafienia, punkt przed trafieniem, celowy
	 * koniec promienia i obiekt koliduj¹cy.
	 */
	struct RaycastHit
	{
		bool hit; ///< Czy promieñ trafi³ w obiekt koliduj¹cy.
		Collisions* collidedObject; ///< WskaŸnik na obiekt Collisions, z którym zachodzi kolizja.
		sf::Vector2f point; ///< Punkt trafienia promienia.
		sf::Vector2f pointBefore; ///< Punkt przed trafieniem.
		sf::Vector2f targetEnd; ///< Celowy koniec promienia.

		/**
		 * @brief Konstruktor struktury RaycastHit.
		 *
		 * @param hits Czy promieñ trafi³.
		 * @param collided WskaŸnik na obiekt Collisions, z którym zachodzi kolizja.
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
		float oldAngle; ///< Przechowuje poprzedni k¹t obiektu.
		float oldSin; ///< Przechowuje sinus poprzedniego k¹ta obiektu.
		float oldCos; ///< Przechowuje cosinus poprzedniego k¹ta obiektu.

	protected:
		sf::FloatRect globalBounds; ///< Ograniczenia globalne obiektu w postaci prostok¹ta.

	public:
		bool enabled; ///< Flaga wskazuj¹ca, czy obiekt jest w³¹czony.

		/**
		 * @brief Konstruktor klasy Collisions.
		 *
		 * Konstruktor inicjalizuje obiekt klasy Collisions ustawiaj¹c pocz¹tkowe wartoœci
		 * dla zmiennych sk³adowych.
		 */
		Collisions();
		/**
		 * @brief Konstruktor klasy Collisions z podanym obiektem TransformableObject.
		 *
		 * Inicjalizuje obiekt klasy Collisions z podanym obiektem transformacji.
		 *
		 * @param transform WskaŸnik na obiekt TransformableObject.
		 */
		Collisions(TransformableObject* transform);

		/**
		 * @brief Destruktor klasy Collisions.
		 *
		 * Zwalnia zasoby zwi¹zane z obiektem klasy Collisions.
		 */
		~Collisions();

		/**
		 * @brief Lista wszystkich obiektów Collisions.
		 */
		static std::vector<Collisions*> All;

		/**
		 * @brief Funkcja usuwaj¹ca obiekt Collisions.
		 *
		 * Usuwa obiekt Collisions (zamiast bezpoœredniego delete).
		 */
		virtual void deleteMe() override;

		/**
		 * @brief Zwraca prostok¹t ograniczaj¹cy obiekt.
		 *
		 * @return Prostok¹t ograniczaj¹cy obiekt.
		 */
		sf::FloatRect getGlobalBounds();

		/**
		 * @brief Sprawdza, czy obiekt koliduje z prostok¹tem o podanych wymiarach.
		 *
		 * @param otherRect Prostok¹t do sprawdzenia kolizji.
		 * @return True, jeœli zachodzi kolizja, w przeciwnym razie False.
		 */
		bool Collides(sf::FloatRect otherRect);

		/**
		 * @brief Sprawdza, czy obiekt koliduje z którymkolwiek innym obiektem Collisions.
		 *
		 * @return WskaŸnik na obiekt, z którym zachodzi kolizja; nullptr, jeœli nie zachodzi kolizja.
		 */
		Collisions* CollidesWithAny();

		/**
		 * @brief Funkcja statyczna do sprawdzania kolizji z okreœlonym punktem.
		 *
		 * Sprawdza kolizjê z danym punktem, z mo¿liwoœci¹ ignorowania jednego obiektu.
		 *
		 * @param point Punkt do sprawdzenia kolizji.
		 * @param ignoreOne WskaŸnik na obiekt Collisions, który ma byæ zignorowany.
		 * @return WskaŸnik na obiekt Collisions, z którym zachodzi kolizja; nullptr, jeœli nie zachodzi kolizja.
		 */
		static Collisions* PointCollide(sf::Vector2f point, Collisions* ignoreOne);

		/**
		 * @brief WskaŸnik na obiekt transformacji zwi¹zanego z obiektem.
		 */
		TransformableObject* myTransform;

		/**
		 * @brief Funkcja statyczna do wykrywania kolizji promienia z obiektami Collisions.
		 *
		 * Sprawdza kolizjê promienia pomiêdzy punktem startowym a punktem koñcowym z obiektami Collisions,
		 * z mo¿liwoœci¹ ignorowania okreœlonych obiektów.
		 *
		 * @param start Punkt pocz¹tkowy promienia.
		 * @param end Punkt koñcowy promienia.
		 * @param ignore Zbiór obiektów do zignorowania podczas sprawdzania kolizji.
		 * @return Struktura RaycastHit zawieraj¹ca informacje o trafieniu promienia.
		 */
		static RaycastHit Raycast(sf::Vector2f start, sf::Vector2f end, std::set<Collisions*> ignore);

		/**
		 * @brief Funkcja statyczna do wykrywania kolizji promienia z obiektami Collisions (jako ca³y obiekt).
		 *
		 * Sprawdza kolizjê promienia z okreœlonym obiektem Collisions, przy uwzglêdnieniu pozycji i
		 * punktu koñcowego promienia.
		 *
		 * @param self Obiekt Collisions sprawdzaj¹cy kolizjê.
		 * @param selfPosition Aktualna pozycja obiektu.
		 * @param end Punkt koñcowy promienia.
		 * @param ignore Zbiór obiektów do zignorowania podczas sprawdzania kolizji.
		 * @return Struktura RaycastHit zawieraj¹ca informacje o trafieniu promienia.
		 */
		static RaycastHit RaycastBox(Collisions* self, sf::Vector2f selfPosition, sf::Vector2f end, std::set<Collisions*> ignore);

		/**
		 * @brief Funkcja wywo³ywana, gdy zachodzi kolizja z innym obiektem.
		 *
		 * @param other WskaŸnik na obiekt Collisions, z którym zachodzi kolizja.
		 */
		virtual void OnCollisionEnter(Collisions* other);

		/**
		 * @brief Funkcja wywo³ywana, gdy kolizja z innym obiektem trwa.
		 *
		 * @param other WskaŸnik na obiekt Collisions, z którym zachodzi kolizja.
		 */
		virtual void OnCollisionStay(Collisions* other);

		/**
		 * @brief Funkcja wywo³ywana, gdy kolizja z innym obiektem koñczy siê.
		 *
		 * @param other WskaŸnik na obiekt Collisions, z którym koñczy siê kolizja.
		 */
		virtual void OnCollisionExit(Collisions* other);
		/**
		 * @brief Wektor przechowuj¹cy aktualne kolizje z innymi obiektami Collisions.
		 */
		std::vector<Collisions*> currentCollisions;

		/**
		 * @brief Funkcja statyczna do przesuwania obiektu na zewn¹trz kolizji.
		 *
		 * Przesuwa obiekt na zewn¹trz kolizji, uwzglêdniaj¹c tylko kolizje z okreœlonym obiektem.
		 *
		 * @param coll WskaŸnik na obiekt Collisions.
		 * @param position Aktualna pozycja obiektu.
		 * @return Nowa pozycja obiektu po przesuniêciu na zewn¹trz kolizji.
		 */
		static sf::Vector2f moveOutOfCollision(Collisions* coll, sf::Vector2f position);

		/**
		 * @brief Sprawdza kolizjê z innym obiektem Collisions.
		 *
		 * @param other WskaŸnik na obiekt Collisions.
		 * @return True, jeœli zachodzi kolizja, w przeciwnym razie False.
		 */
		bool Collides(Collisions* other);

		/**
		 * @brief Sprawdza kolizjê z danym punktem.
		 *
		 * @param point Punkt do sprawdzenia kolizji.
		 * @return True, jeœli zachodzi kolizja, w przeciwnym razie False.
		 */
		bool Collides(sf::Vector2f point);

		/**
		 * @brief Funkcja do przesuwania obiektu na zewn¹trz kolizji z uwzglêdnieniem prêdkoœci.
		 *
		 * Przesuwa obiekt na zewn¹trz kolizji, uwzglêdniaj¹c prêdkoœæ obiektu.
		 *
		 * @param coll WskaŸnik na obiekt Collisions.
		 * @param position Aktualna pozycja obiektu.
		 * @param velocity Wektor prêdkoœci obiektu.
		 * @return Nowa pozycja obiektu po przesuniêciu na zewn¹trz kolizji z uwzglêdnieniem prêdkoœci.
		 */
		sf::Vector2f moveOutOfCollision(Collisions* coll, sf::Vector2f position, sf::Vector2f velocity);

		/**
		 * @brief Sprawdza kolizjê z danym zbiorem punktów (wierzcho³ków).
		 *
		 * @param corners Wektor zawieraj¹cy punkty do sprawdzenia kolizji.
		 * @return True, jeœli zachodzi kolizja, w przeciwnym razie False.
		 */
		bool Collides(std::vector<sf::Vector2f> corners);

		/**
		 * @brief Oblicza pozycje wierzcho³ków obiektu na podstawie szerokoœci, wysokoœci, k¹ta i pozycji.
		 *
		 * @param width Szerokoœæ obiektu.
		 * @param height Wysokoœæ obiektu.
		 * @param angle K¹t obrotu obiektu.
		 * @param position Pozycja obiektu.
		 */
		void CalculateCorners(float width, float height, float angle, const sf::Vector2f position);

		/**
		 * @brief Wypisuje wspó³rzêdne wierzcho³ków obiektu.
		 *
		 * @param corners Wektor zawieraj¹cy wspó³rzêdne wierzcho³ków.
		 */
		static void printCorners(const std::vector<sf::Vector2f>& corners);

		/**
		 * @brief Rysuje wspó³rzêdne wierzcho³ków obiektu.
		 *
		 * @param corners Wektor zawieraj¹cy wspó³rzêdne wierzcho³ków.
		 */
		static void drawCorners(const std::vector<sf::Vector2f>& corners);

		/**
		 * @brief Wektor przechowuj¹cy wspó³rzêdne wierzcho³ków obiektu.
		 */
		std::vector<Vector2f> myCorners;

		/*Vector2f left;
		Vector2f right;
		Vector2f bottom;
		Vector2f top;*/
	};

}