#include "BitmapHandler.h"
using namespace Engine2D;
BitmapHandler::BitmapHandler(int width, int height) {
    this->width = width;
    this->height = height;
    bitmap.create(width, height);
}
    
 void BitmapHandler::loadFromFile(const std::string & filename)
    {
        if (bitmap.loadFromFile(filename)) {
            width = bitmap.getSize().x;
            height = bitmap.getSize().y;
        }
        else {
            std::cerr << "blad zaladowania pliku: " << filename << std::endl;
        }
    }
 void BitmapHandler::saveToFile(const std::string& filename)
 {
     if (bitmap.saveToFile(filename)) {
     }
     else {
         std::cerr << "blad zapisu pliku: " << filename << std::endl;
     }
 }

 sf::Image BitmapHandler::getbitmap()
 {
     return bitmap;
 }

 void BitmapHandler::copyTo(BitmapHandler& other) {
     other.bitmap = bitmap;
     other.width = width;
     other.height = height;
 }

 sf::Image BitmapHandler::getImage()
 {
     return this->bitmap;
 }
