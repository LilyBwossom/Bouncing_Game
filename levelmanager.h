#pragma once

namespace Tmpl8
{
    constexpr static int WorldTilesX = 60;
    constexpr static int WorldTilesY = 17;
    typedef char map[WorldTilesY][WorldTilesX * 3];
    
    #ifndef VERSION2
    static int currentLevel = 0;
    #else
    extern int currentLevel;
    #endif
    
    extern map level1;
    extern map level2;
    extern map level3;
    extern map endLevel;

    constexpr static int levelAmount = 4;
    constexpr map* levels[levelAmount] = { &level1, &level2, &level3, &endLevel };
}