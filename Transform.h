#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <set>
#include "GameObject.h"

using namespace std;
using namespace sf;

namespace Engine2D
{
    /**
     * @brief Klasa reprezentuj¹ca obiekt gry poddaj¹cy siê transformacjom.
     *
     * Klasa TransformableObject dziedziczy po klasie GameObject
     * i dodaje w³aœciwoœci oraz funkcje zwi¹zane z transformacjami.
     */
    class TransformableObject : public virtual GameObject
    {
    private:
        TransformableObject* parent;

    public:
        static set<TransformableObject*> All; ///< Zbiór wszystkich obiektów poddaj¹cych siê transformacjom.
        vector<TransformableObject*> children; ///< Wektor dzieci obiektu poddaj¹cego siê transformacjom.
        Vector2f position; ///< Lokalna pozycja obiektu.
        Vector2f lastPosition; ///< Ostatnia lokalna pozycja obiektu.

        /**
         * @brief Pobiera pozycjê obiektu w œwiecie.
         *
         * @return Pozycja obiektu w œwiecie.
         */
        Vector2f worldPosition();

        /**
         * @brief Pobiera ostatni¹ pozycjê obiektu w œwiecie.
         *
         * @return Ostatnia pozycja obiektu w œwiecie.
         */
        Vector2f lastWorldPosition();

        Vector2f scale; ///< Lokalna skala obiektu.

        /**
         * @brief Pobiera skalê obiektu w œwiecie.
         *
         * @return Skala obiektu w œwiecie.
         */
        Vector2f worldScale();

        Vector2f bounds; ///< Lokalne granice obiektu.

        /**
         * @brief Pobiera granice obiektu w œwiecie.
         *
         * @return Granice obiektu w œwiecie.
         */
        Vector2f worldBounds();
        string tag; ///< Etykieta obiektu.
        float rotation; ///< Lokalna rotacja obiektu.

        /**
         * @brief Pobiera globalna rotacje obiektu w swiecie.
         *
         * @return Globalna rotacja obiektu w swiecie.
         */
        float worldRotation();

        /**
         * @brief Przesuwa obiekt o podane wartosci X i Y.
         *
         * @param X Wartosc przesuniecia wzdluz osi X.
         * @param Y Wartosc przesuniecia wzdluz osi Y.
         */
        void Translate(float X, float Y);

        /**
         * @brief Przesuwa obiekt o podany wektor XY.
         *
         * @param XY Wektor przesuniecia.
         */
        void Translate(Vector2f XY);

        /**
         * @brief Ustawia pozycje obiektu na podanej wartosci XY.
         *
         * @param XY Nowa pozycja obiektu.
         */
        void setPosition(Vector2f XY);

        /**
         * @brief Skaluje obiekt o podana wartosc XY.
         *
         * @param XY Wartosc skalowania w obie strony.
         */
        void Scale(float XY);

        /**
         * @brief Skaluje obiekt o podane wartosci X i Y.
         *
         * @param X Wartosc skalowania wzdluz osi X.
         * @param Y Wartosc skalowania wzdluz osi Y.
         */
        void Scale(float X, float Y);

        /**
         * @brief Ustawia skale obiektu na podane wartosci X i Y.
         *
         * @param X Wartosc skalowania wzdluz osi X.
         * @param Y Wartosc skalowania wzdluz osi Y.
         */
        void setScale(float X, float Y);

        /**
         * @brief Skaluje obiekt o podany wektor XY.
         *
         * @param XY Wektor skalowania.
         */
        void Scale(Vector2f XY);

        /**
         * @brief Obraca obiekt o podany kat.
         *
         * @param rotation Kat rotacji.
         */
        void Rotate(float rotation);
        /**
         * @brief Przypisuje nowego rodzica obiektowi.
         *
         * @param newParent Nowy rodzic.
         */
        void SetParent(TransformableObject* newParent);

        /**
         * @brief Ustawia obiekt jako dziecko nowego rodzica.
         *
         * @param newParent Nowy rodzic obiektu.
         */
         /**
          * @brief Konstruktor domyslny klasy TransformableObject.
          */
        TransformableObject();

        /**
         * @brief Konstruktor klasy TransformableObject z podana pozycja.
         *
         * @param position Pozycja poczatkowa obiektu.
         */
        TransformableObject(Vector2f position);

        /**
         * @brief Konstruktor klasy TransformableObject z podana pozycja i rotacja.
         *
         * @param position Pozycja poczatkowa obiektu.
         * @param rotation Poczatkowa rotacja obiektu.
         */
        TransformableObject(Vector2f position, float rotation);

        /**
         * @brief Konstruktor klasy TransformableObject z podana pozycja, skala i rotacja.
         *
         * @param position Pozycja poczatkowa obiektu.
         * @param scale Skala poczatkowa obiektu.
         * @param rotation Poczatkowa rotacja obiektu.
         */
        TransformableObject(Vector2f position, Vector2f scale, float rotation);

        /**
         * @brief Konstruktor klasy TransformableObject z podana pozycja, skala, rotacja i rodzicem.
         *
         * @param position Pozycja poczatkowa obiektu.
         * @param scale Skala poczatkowa obiektu.
         * @param rotation Poczatkowa rotacja obiektu.
         * @param parent Rodzic obiektu.
         */
        TransformableObject(Vector2f position, Vector2f scale, float rotation, TransformableObject* parent);

        /**
         * @brief Konstruktor klasy TransformableObject z podanym rodzicem.
         *
         * @param parent Rodzic obiektu.
         */
        TransformableObject(TransformableObject* parent);

        /**
         * @brief Pobiera rodzica obiektu.
         *
         * @return Wskaznik do rodzica obiektu.
         */
        TransformableObject* GetParent();

        /**
         * @brief Destruktor klasy TransformableObject.
         */
        ~TransformableObject();
        /**
         * @brief Wirtualna funkcja informujaca o zmianie wlasciwosci obiektu.
         */
        virtual void PropertiesChanged();

        /**
         * @brief Aktualizuje wlasciwosci dzieci przy zmianie wlasciwosci tego obiektu.
         */
        void ChildrenPropertiesChange();

        /**
         * @brief Konstruktor klasy TransformableObject z podana nazwa i pozycja.
         *
         * @param name Nazwa obiektu.
         * @param position Pozycja poczatkowa obiektu.
         */
        TransformableObject(std::string name, Vector2f position);

        /**
         * @brief Wirtualna funkcja usuwajaca obiekt.
         *
         * Nadpisuje funkcje z klasy bazowej GameObject.
         */
        virtual void deleteMe() override;
		//virtual void checkPropertyChanged();
	};
}