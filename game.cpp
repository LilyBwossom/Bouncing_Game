using namespace std;

#include "game.h"

namespace Tmpl8
{
    Surface Tileset("assets/tileset.tga");

    int Game::CameraX;
    int Game::CameraY = 548;

    std::map<char*, Tile*> tiles = {
        {"G1", new GroundTL()}, {"G2", new GroundTM()}, {"G3", new GroundTR()},
        {"G4", new GroundML()}, {"M1", new GroundMM()}, {"G6", new GroundMR()},
        {"G7", new GroundBL()}, {"G8", new GroundBM()}, {"G9", new GroundBR()},
        {"K1", new GroundUL()}, {"K2", new GroundUR()},
        {"M2", new GroundMMR1()}, {"M3", new GroundMMR2()}, {"M4", new GroundMMR3()}, {"M5", new GroundMMR4()}, {"M6", new GroundMMR5()},
        {"C1", new Coin()},
        {"S1", new IronSpike()}, {"S2", new WoodSpike1()}, {"S3", new WoodSpike2()},
        {"F1", new FlagTL()}, {"F2", new FlagTR()},
        {"F3", new FlagBL()}, {"F4", new FlagBR()},
        {"D1", new Plant1()}, {"D2", new Plant2()}, {"D3", new BushL()}, {"D4", new BushR()},
        {"D5", new Rock1()}, {"D6", new Rock2()}, {"D7", new BigRock()},
        {"D8", new Stump()}, {"D9", new Arrow()},
        {"L1", new Cloud1()}, {"L2", new Cloud2()}, {"L3", new Cloud3()},
        {"L4", new Cloud4()}, {"L5", new Cloud5()}, {"L6", new Cloud6()},
        {"L7", new Cloud7()}, {"L8", new Cloud8()}, {"L9", new Cloud9()},
        {"B1", new Blower()},
        {"I1", new Ice1()}, {"I2", new Ice2()}, {"I3", new Ice3()}, {"I4", new Ice4()},
        {"P1", new Apple}, {"P2", new Banana()},
        {"E1", new End1()}, {"E2", new End2()}, {"E3", new End3()}, {"E4", new End4()}, {"E5", new End5()}, {"E6", new End6()},
        {"T1", new Thanks1()}, {"T2", new Thanks2()}, {"T3", new Thanks3()}, {"T4", new Thanks4()}, {"T5", new Thanks5()}, {"T6", new Thanks6()}, {"T7", new Thanks7()}, 
        {"T8", new Thanks8()}, {"T9", new Thanks9()}, {"H1", new Thanks10()}, {"H2", new Thanks11()}, {"H3", new Thanks12()}, {"H4", new Thanks13()}, 
        {"H5", new Thanks14()}, {"H6", new Thanks15()}
    };

    Tmpl8::map Game::map;

    void Game::ChangeLevel(Tmpl8::map level) {
        std::copy(&level[0][0], &level[WorldTilesY - 1][WorldTilesX * 3 - 1], &Game::map[0][0]);
    }

    //sets a tile on the tile map
    void Game::SetTile(char tileType[3], int txSet, int tySet) {
        //return null if the tile is not in the tileset
        if (txSet < 0 || txSet >= WorldTilesX ||
            tySet < 0 || tySet >= WorldTilesY) {
            return;
        }

        map[tySet][txSet * 3] = tileType[0];
        map[tySet][txSet * 3 + 1] = tileType[1];
    }

    //gets a tile on the tile map
    Tile* Game::GetTile(int txSet, int tySet) {
        //return null if the tile is not in the tileset
        if (txSet < 0 || txSet >= WorldTilesX || 
            tySet < 0 || tySet >= WorldTilesY) {
            return nullptr;
        }

        char* id = &map[tySet][txSet * 3];

        if (strncmp(id, "00", 2) == 0) {
            return nullptr;
        }

        #ifndef VERSION2 //unnecessary code left in accidentally
        auto pair = tiles.find(id);
        if (pair != tiles.end()) {
            return pair->second;
        }
        #endif

        for (const auto& pair : tiles) {
            if (strncmp(pair.first, id, 2) == 0) {
                return pair.second;
            }
        }

        return nullptr;
    }

    //initialize the player
    Player Game::player = new Player();

    void Game::Init() {
        ChangeLevel(level1);    
    }

    void Game::Shutdown() {
        //frees all tiles
        for (const auto& pair : tiles) {
            delete pair.second;
        }
    }

    void Game::DrawTile(Surface* screen, int tx, int ty, int screenX, int screenY, int x, int y) {
        Pixel* src = Tileset.GetBuffer() + tx * TileSize + ty * TileSize * Tileset.GetWidth();
        Pixel* dst = screen->GetBuffer() + screenX + screenY * ScreenWidth;

        //this loops through all the pixels on the tile and draws them on the screen
        //and also populates the special map
        for (int i = 0; i < TileSize; i++, src += Tileset.GetWidth(), dst += screen->GetWidth()) {
            for (int j = 0; j < TileSize; j++) {
                int pixelX = (screenX + j);
                int pixelY = (screenY + i);

                //this checks if the pixel coordinates are on the screen
                if (pixelX > 0 && pixelX < ScreenWidth && pixelY > 0 && pixelY < ScreenHeight) {
                    /* adjacent tile visualization debug code
                    if (abs(x - player.x) < 80 && (abs(y - player.y)) < 80) {
                        dst[j] = (255) + (0 << 8) + (0 << 16);
                        continue;
                    }
                    */

                    dst[j] = src[j];
                }
            }
        }
    }

    void Game::DrawTileSet(Surface* screen) {
        //this gets the top left most pixel coordinate on the screen
        int FirstTileX = CameraX - (ScreenWidth / 2);
        int FirstTileY = CameraY - (ScreenHeight / 2);

        //this gets the bottom right most pixel coordinate on the screen
        int LastTileX = CameraX + (ScreenWidth / 2);
        int LastTileY = CameraY + (ScreenHeight / 2);

        //this loops through the places where tiles should be placed on the screen
        for (int y = (int)floor(FirstTileY / TileSize); y < (int)ceil((float)LastTileY / TileSize); y++) {
            for (int x = (int)floor(FirstTileX / TileSize); x < (int)ceil((float)LastTileX / TileSize); x++) {
                //this draws the tile and gets the tilemap coordinates
                Tile* tile = GetTile(x, y);

                //there is no tile at that index in the tilemap
                if (tile == nullptr) {
                    continue;
                }

                int tx = tile->mapX, ty = tile->mapY;
                DrawTile(screen, tx, ty, (x * TileSize) - FirstTileX, (y * TileSize) - FirstTileY, x * TileSize, y * TileSize);
            }
        }
    }

    void DrawSky(Surface* screen) {
        //fills the rest of the screen with the sky color
        Pixel* screenPixels = screen->GetBuffer();
        for (int i = 0; i < (screen->GetHeight() * screen->GetWidth()); i++) {
            //same as ((147 * 256 * 256) + (199 * 256) + 255), creates color 147 199 255
            //(147 << 16) + (199 << 8) + 255

            //checks for empty pixels
            if (screenPixels[i] == 0) {
                screenPixels[i] = (255) + (199 << 8) + (147 << 16);
            }
        }
    }

    void printDebugText(Surface* screen, string strArray[], int length) {
        int textY = 25;
        for (int i = 0; i < length; i++) {
            screen->Print((char*)strArray[i].c_str(), 2, textY, 0xffffff);
            textY += 10;
        }
    }

    //handles animations at a 50 and 25 milisecond framerate
    float timeSinceLastAnim;
    int fiftyPassed;
    void Game::Animate(float deltaTime) {
        timeSinceLastAnim += deltaTime;

        if (timeSinceLastAnim >= 50) {
            timeSinceLastAnim = 0;
            fiftyPassed += 1;

            for (const auto& pair : tiles) {
                pair.second->updateAnim();
            }

        }

        if (fiftyPassed >= 3) {
            fiftyPassed = 0;

            player.UpdateAnim();
        }
    }

    void Game::Tick(float deltaTime) {
        screen->Clear(0);

        //handles speed and jump boosts applied by powerups
        player.SpeedUp(deltaTime);
        player.JumpForceUp(deltaTime);

        if (GetAsyncKeyState('A')) { player.MoveLeft(deltaTime); }
        if (GetAsyncKeyState('D')) { player.MoveRight(deltaTime); }
        if (GetAsyncKeyState(VK_SPACE)) { player.Jump(deltaTime); }

        player.grounded = false;

        DrawTileSet(screen);
        
        DrawSky(screen);

        player.Collisions(screen);

        player.Physics(deltaTime);

        player.Draw(screen);

        Animate(deltaTime);

        #ifndef VERSION2
        string strArray[] = { "Camera position: " + to_string(CameraX) + ", " + std::to_string(CameraY),
                              "Player pos: " + to_string(player.x),
                              "Player vel: " + to_string(player.velocityX) + ", " + std::to_string(player.velocityY),
                              "Player grounded: " + to_string(player.grounded),
                              "x and y of left top most: " + to_string(CameraX - (ScreenWidth / 2)) + ", " + to_string(CameraY - (ScreenWidth / 2))
                            };
    
        printDebugText(screen, strArray, 5);
        #endif

    }
};