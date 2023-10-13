#include "Engine.h"
#include <stdio.h>
#include <iostream>
int main()
{
    Engine* currentEngine = Engine::GetSingleton(true);
    printf("Engine: %p\n", currentEngine);
    delete(currentEngine);
    Engine* newEngine = new Engine();
    printf("Engine: %p\n", Engine::GetSingleton(false));
    return 0;
}