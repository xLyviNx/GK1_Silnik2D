﻿#include "Engine.h"
#include <stdio.h>
#include <iostream>
using namespace GRUPA3::Engine2D;
using namespace std;
int main()
{
    Engine* currentEngine = Engine::GetSingleton(true);
    delete(currentEngine);
    return 0;
}
