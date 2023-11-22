#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "spriteObject.h"

class BitmapHandler {
protected:
   
    int width;
    int height;
    sf::Image bitmap;
public:
    
    BitmapHandler(int width, int height);
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);
    sf::Image getbitmap();
    
    void copyTo(BitmapHandler& other);
    sf::Image getImage();
};

