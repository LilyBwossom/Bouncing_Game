#include "game.h"
#include "player.h"
#include "template.h"
#include "surface.h"
#include <string>

namespace Tmpl8
{
    Sprite PlayerSprite(new Surface("assets/player.tga"), 2);
    const int PlayerSize = 64;

    void Player::MoveLeft(float deltaTime) {
        facingRight = false;
        velocityX += -speed * deltaTime;
    }

    void Player::MoveRight(float deltaTime) {
        facingRight = true;
        velocityX += speed * deltaTime;
    }

    void Player::Jump(float deltaTime) {
        if (grounded) {
            grounded = false;
            velocityY = -jumpForce; // * deltaTime; (removed because it made the jump height inconsistent)
        }
    }

    void Player::Draw(Surface* gameScreen) {
        PlayerSprite.SetFrame(facingRight);

        //-(PlayerSize / 2) so it's centered
        PlayerSprite.Draw(gameScreen, (ScreenWidth / 2) - (PlayerSize / 2), (int)y - (PlayerSize / 2));
    }

    void Player::Physics(float deltaTime) {
        x += velocityX;
        y += velocityY;

        velocityX *= 0.5;
        velocityY += gravity * deltaTime;

        if (y > ScreenHeight)
        {
            x = 200;
            y = ScreenHeight / 1.5;
        }

        Game::CameraX = x;
        //CameraY = y;
    }

    void Player::CollideTop() {
        if (velocityY < 0) {
            velocityY = 0;
        }
    }

    void Player::CollideBottom() {
        grounded = true;

        if (velocityY > 0) {
            velocityY = 0;
        }
    }

    void Player::CollideLeft() {
        if (velocityX < 0) {
            velocityX = 0;
        }
    }

    void Player::CollideRight() {
        if (velocityX > 0) {
            velocityX = 0;
        }
    }

    //handles the player collisions
    void Player::Collisions(Surface* screen) {
        int pxCenter = Game::CameraX;
        int pyCenter = y;

        int px = pxCenter - (PlayerSize / 2);
        int py = pyCenter - (PlayerSize / 2);

        //this loops through the tiles near the player
        for (int y = -1; y <= 1; y++) {
            for (int x = -1; x <= 1; x++) {
                //collision sides
                bool top = false;
                bool bottom = false;
                bool left = false;
                bool right = false;

                int txSet = floor((pxCenter + x * Game::TileSize) / Game::TileSize);
                int tySet = floor((pyCenter + y * Game::TileSize) / Game::TileSize);

                // int tx = floor((pxCenterScreen + x * Game::TileSize) / Game::TileSize);
                // int ty = floor((pyCenterScreen + y * Game::TileSize) / Game::TileSize);

                //this stops the program from trying to find a tile when there is none at that index in the tilemap
                if (txSet < 0 || txSet >= Game::WorldTilesX || tySet < 0 && tySet >= Game::WorldTilesY) {
                    continue;
                }

                int tx = txSet * Game::TileSize;
                int ty = tySet * Game::TileSize;


                int tileType = Game::map[tySet][txSet * 4 + 2] - 'a';

                //this does the box collision
                if (tileType == 0) {
                    bool horz = tx <= px + PlayerSize && px <= tx + Game::TileSize;
                    bool vert = ty <= py + PlayerSize && py <= ty + Game::TileSize;

                    top = horz && (ty + Game::TileSize >= py && ty + Game::TileSize <= py + PlayerSize);
                    bottom = horz && (ty >= py && ty <= py + PlayerSize);
                    left = vert && (tx + Game::TileSize >= px && tx + Game::TileSize <= px + PlayerSize);
                    right = vert && (tx >= px && tx <= px + PlayerSize);

                    //std::string string = "Collisions: " + std::to_string(top) + ", " + std::to_string(bottom) + ", " + std::to_string(left) + ", " + std::to_string(right) + "\nhorz and vert: " + std::to_string(horz) + ", " + std::to_string(vert);
                    //char* char1 = (char*)(string).c_str();
                    //screen->Print(char1, 2, 80, 0xffffff);
                }

                if (top) {
                    CollideTop();
                }

                if (bottom) {
                    CollideBottom();
                }

                if (left) {
                    CollideLeft();
                }

                if (right) {
                    CollideRight();
                }
            }
        }
    }
}