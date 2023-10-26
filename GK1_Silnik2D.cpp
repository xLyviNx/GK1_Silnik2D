#include "Engine.h"
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace Engine2D;
using namespace std;
int main()
{
    Engine* currentEngine = Engine::GetSingleton(true);
    delete(currentEngine);
    return 0;
}
