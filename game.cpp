using namespace std;

#include "ground.h"
#include "player.h"
#include "game.h"
#include "surface.h"
#include "template.h"
#include "windows.h"
#include <string>
#include <list>

namespace Tmpl8
{
    Surface Tileset("assets/tileset.tga");
    Surface Specialset("assets/specialset.tga");

    const int TilemapWidth = Game::TileSize * 20;
    const int TilemapHeight = Game::TileSize * 16;

    int Game::CameraX;
    int Game::CameraY = 100;

    constexpr static int tileAmount = 9;
    Tile* tiles[tileAmount] = { new GroundTL(),
                                new GroundTM(),
                                new GroundTR(),
                                new GroundML(),
                                new GroundMM(),
                                new GroundMR(),
                                new GroundBL(),
                                new GroundBM(),
                                new GroundBR()
    };

    char Game::map[Game::WorldTilesY][Game::WorldTilesX * 2] = {
        "1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 3",
        "4 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 6",
        "4 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 6",
        "4 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 6",
        "4 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 6",
        "4 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 6",
        "4 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 6",
        "4 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 6",
        "4 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 6",
        "4 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 6",
        "4 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 6",
        "4 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 6",
        "4 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 6",
        "4 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 6",
        "4 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 6",
        "4 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 6",
        "4 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 6",
        "7 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 9"
    };

    //void Game::GetTile(int x, int y) {
    //    floor((pxCenterScreen + x * Game::TileSize) / Game::TileSize);
    //}

    void Game::Init() {}

    void Game::Shutdown() {
        // free each tile object
        for (int i = 0; i < tileAmount; ++i) {
            delete tiles[i];
            tiles[i] = nullptr;
        }
    }

    void Game::DrawTile(Surface* screen, int tx, int ty, int x, int y) {
        Pixel* src = Tileset.GetBuffer() + tx * TileSize + ty * TileSize * TilemapWidth;
        Pixel* dst = screen->GetBuffer() + x + y * ScreenWidth;

        //this loops through all the pixels on the tile and draws them on the screen
        //and also populates the special map
        for (int i = 0; i < TileSize; i++, src += TilemapWidth, dst += screen->GetWidth()) {
            for (int j = 0; j < TileSize; j++) {
                int pixelX = (x + j);
                int pixelY = (y + i);

                //this checks if the pixel coordinates are on the screen
                if (pixelX > 0 && pixelX < ScreenWidth && pixelY > 0 && pixelY < ScreenHeight) {
                    dst[j] = src[j];
                }
            }
        }
    }

    void Game::DrawTileSet(Surface* screen) {
        //this gets the top left most pixel coordinate on the screen
        int FirstTileX = CameraX - (ScreenWidth / 2);
        int FirstTileY = CameraY - (ScreenWidth / 2);

        //this gets the bottom right most pixel coordinate on the screen
        int LastTileX = CameraX + (ScreenWidth / 2);
        int LastTileY = CameraY + (ScreenWidth / 2);

        //this loops through the places where tiles should be placed on the screen
        for (int y = floor(FirstTileY / TileSize); y < ceil((float)LastTileY / TileSize); y++) {
            for (int x = floor(FirstTileX / TileSize); x < ceil((float)LastTileX / TileSize); x++) {
                //this stops the program from trying to draw a tile when there is none at that index in the tilemap
                if (x >= 0 && x < WorldTilesX && y >= 0 && y < WorldTilesY) {
                    //this draws the tile and gets the tilemap coordinates
                    int tx = tiles[map[y][x * 2] - '1']->mapX, ty = tiles[map[y][x * 2] - '1']->mapY;
                    DrawTile(screen, tx, ty, (x * TileSize) - FirstTileX, (y * TileSize) - FirstTileY);
                }
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

    void printDebugText(Surface* screen, int* textY, string strArray[], int length) {
        for (int i = 0; i < length; i++) {
            screen->Print((char*)strArray[i].c_str(), 2, *textY, 0xffffff);
            *textY += 10;
        }
    }

    //initialize the player
    Tmpl8::Player player(-100, (ScreenHeight / 1.5));

    void Game::Tick(float deltaTime) {
        screen->Clear(0);

        if (GetAsyncKeyState('A')) { player.MoveLeft(deltaTime); }
        if (GetAsyncKeyState('D')) { player.MoveRight(deltaTime); }
        if (GetAsyncKeyState(VK_SPACE)) { player.Jump(deltaTime); }

        player.grounded = false;

        DrawTileSet(screen);
        
        DrawSky(screen);

        player.Collisions(screen);

        player.Physics(deltaTime);

        player.Draw(screen);

        int debugTextY = 25;

        //"Drawing tile " + std::to_string((int)floor(FirstTileX / 32)) + " - " + std::to_string((int)ceil((float)LastTileX / 32)) + " and tile " + std::to_string((int)floor(FirstTileY / 32)) + " - " + std::to_string((int)ceil((float)LastTileY / 32))
        string strArray[] = { "Camera position: " + to_string(CameraX) + ", " + std::to_string(CameraY),
                              "Player pos: " + to_string(player.x),
                              "Player vel: " + to_string(player.velocityX) + ", " + std::to_string(player.velocityY),
                              "Player grounded: " + to_string(player.grounded),
                              "x and y of left top most: " + to_string(CameraX - (ScreenWidth / 2)) + ", " + to_string(CameraY - (ScreenWidth / 2))
                            };
    
        printDebugText(screen, &debugTextY, strArray, 5);
    }
};