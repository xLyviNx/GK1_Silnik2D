#include "Engine.h"
#include "DataTypes.h"
#include <stdio.h>
#include <iostream>
using namespace GRUPA3::Engine2D;
using namespace GRUPA3::DataTypes;
using namespace std;
namespace GRUPA3
{
    int main()
    {
        Engine* currentEngine = Engine::GetSingleton(true);
        delete(currentEngine);
        return 0;
    }
}