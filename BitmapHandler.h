#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "spriteObject.h"
/**
 * @brief klasa sluzaca do obslugi bitmap z technicznego punktu widzenia tj. zaladowanie z pliku, zaladowanie do pliku, kopiowanie.
 */
class BitmapHandler {
protected:
   
    int width;///<szerokosc obiektu
    int height;///<wysokosc obiektu
public:
    sf::Image bitmap;
   
    BitmapHandler(int width, int height);
    /**
     * @brief funkcja ladujaca bitmape do obiektu
     * 
     * @param filename nazwa pliku z ktorego bitmapa ma byc zaladowana.
     */
    void loadFromFile(const std::string& filename);
    /**
    * @brief funkcja ladujaca bitmape z obiektu do pliku
    *
    * @param filename nazwa pliku z ktorego bitmapa ma byc zaladowana.
    */
    void saveToFile(const std::string& filename);
    sf::Image getbitmap();
    /**
     * @brief funkcja kopiujaca bitmape do innego obiektu typu BitmapHandler
     * 
     * @param other obiekt do ktorego ma byc przekopiowana bitmapa
     */
    void copyTo(BitmapHandler& other);
    sf::Image getImage();
};

