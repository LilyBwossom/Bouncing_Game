#include "player.h"

namespace Tmpl8
{
    Sprite PlayerSprite(new Surface("assets/player.tga"), 4);
    const int PlayerSize = 64;
    int currentFrame = 0;

    void Player::Respawn(bool spawnsGrounded) {
        #ifdef VERSION2
        Game::ChangeLevel(*levels[currentLevel]);
        #endif

        velocityX = 0;
        velocityY = 0;
        grounded = spawnsGrounded;

        x = Game::TileSize * 2;
        y = Game::TileSize * (WorldTilesY - 4);

        speedUpTime = 0;
        jumpForceUpTime = 0;
    }

    void Player::MoveLeft(float deltaTime) {
        facingRight = false;
        velocityX += -(speed + speedMod) * deltaTime;
    }

    void Player::MoveRight(float deltaTime) {
        facingRight = true;
        velocityX += (speed + speedMod) * deltaTime;
    }

    void Player::SpeedUp(float deltaTime) {
        if (speedUpTime > 0) {
            speedUpTime -= deltaTime;
            speedMod = 0.15;
        }
        else {
            speedUpTime = 0;
            speedMod = 0;
        }
    }

    void Player::Jump(float deltaTime) {
        if (grounded) {
            grounded = false;
            #ifndef VERSION2
            velocityY = -(jumpForce + jumpForceMod) * deltaTime;
            #else     
            velocityY = -(jumpForce + jumpForceMod);
            #endif
        }
    }

    void Player::JumpForceUp(float deltaTime) {
        if (jumpForceUpTime > 0) {
            jumpForceUpTime -= deltaTime;
            #ifndef VERSION2
            jumpForceMod = 0.2;
            #else
            jumpForceMod = 2;
            #endif
        }
        else {
            jumpForceUpTime = 0;
            jumpForceMod = 0;
        }
    }

    void Player::Draw(Surface* gameScreen) {
        PlayerSprite.SetFrame(facingRight + currentFrame);

        int topLeftY = Game::CameraY - (ScreenHeight / 2);

        //-(PlayerSize / 2) so it's centered
        PlayerSprite.Draw(gameScreen, (ScreenWidth / 2) - (PlayerSize / 2), (int)y - (PlayerSize / 2) - topLeftY);
    }

    void Player::UpdateAnim()
    {
        int newFrame = currentFrame + 2;
        if (newFrame >= 4) {
            newFrame = 0;
        }

        currentFrame = newFrame;
    }

    void Player::Physics(float deltaTime) {
        x += velocityX;
        y += velocityY;

        //reset the friction after collisions apply it
        velocityX *= 0.5f - frictionMod;
        frictionMod = 0;

        velocityY += gravity * deltaTime;

        if (y > ScreenHeight + PlayerSize)
        {
            Respawn();
        }

        Game::CameraX = (int)x;
        //CameraY = y;
    }

    void Player::CollideTop(int sideY) {
        y = (float)(sideY + PlayerSize / 2);

        if (velocityY < 0) {
            velocityY = 0;
        }
    }

    void Player::CollideBottom(int sideY) {
        grounded = true;

        y = (float)(sideY - PlayerSize / 2);

        if (velocityY > 0) {
            velocityY = 0;
        }
    }

    void Player::CollideLeft(int sideX) {
        x = (float)(sideX + PlayerSize / 2);

        if (velocityX < 0) {
            velocityX = 0;
        }
    }

    void Player::CollideRight(int sideX) {
        x = (float)(sideX - PlayerSize / 2);

        if (velocityX > 0) {
            velocityX = 0;
        }
    }

    //handles the player collisions
    void Player::Collisions(Surface* screen) {
        int pxCenter = (int)x;
        int pyCenter = (int)y;

        int px = pxCenter - (PlayerSize / 2);
        int py = pyCenter - (PlayerSize / 2);

        //this loops through the tiles near the player
        for (int y = -1; y <= 1; y++) {
            for (int x = -1; x <= 1; x++) {
                int txSet = (int)floor(pxCenter / Game::TileSize + x); //tile tileset x coordinate
                int tySet = (int)floor(pyCenter / Game::TileSize + y); //tile tileset y coordinate

                int tx = txSet * Game::TileSize; //tile topleft x
                int ty = tySet * Game::TileSize; //tile topleft y

                Tile* tile = Game::GetTile(txSet, tySet);

                //there is no tile at that index in the tilemap
                if (tile == nullptr) {
                    continue;
                }

                //this does the box collision
                //---------------------------
                float m = 10; //margin
                int ts = Game::TileSize; //tile size
                int ps = PlayerSize; //playersize

                bool top = false;
                bool bottom = false;
                bool left = false;
                bool right = false;

                if (tile->collisionType == Tile::CollisionType::FULL) {
                    top = py <= ty + ts && py >= ty && px + ps - m >= tx && px + m <= tx + ts;
                    bottom = py + ps >= ty && py + ps <= ty + ts && px + ps - m >= tx && px + m <= tx + ts;
                    left = px <= tx + ts && px >= tx && py + ps - m >= ty && py + m <= ty + ts;
                    right = px + ps >= tx && px + ps <= tx + ts && py + ps - m >= ty && py + m <= ty + ts;
                }
                else if (tile->collisionType == Tile::CollisionType::HALF) {
                    int b = 1; //inner box margin

                    top = py >= ty + ts / 4 - b && py <= ty + ts - ts / 4 + b && px + ps - m >= tx + ts / 4 - b && px + m <= tx + ts - ts / 4 + b;
                    bottom = py + ps >= ty + ts / 4 - b && py + ps <= ty + ts - ts / 4 + b && px + ps - m >= tx + ts / 4 - b && px + m <= tx + ts - ts / 4 + b;
                    right = px + ps >= tx + ts / 4 - b && px + ps <= tx + ts - ts / 4 + b && py + ps - m >= ty + ts / 4 - b && py + m <= ty + ts - ts / 4 + b;
                    left = px >= tx + ts / 4 - b && px <= tx + ts - ts / 4 + b && py + ps - m >= ty + ts / 4 - b && py + m <= ty + ts - ts / 4 + b;
                }

                if (top) {
                    tile->OnCollide(Tile::Direction::TOP, txSet, tySet);
                    if (tile->hasCollision) {
                        CollideTop(ty + Game::TileSize);
                    }
                }

                if (bottom) {
                    tile->OnCollide(Tile::Direction::BOTTOM, txSet, tySet);
                    if (tile->hasCollision) {
                        CollideBottom(ty);
                    }
                }

                if (left) {
                    tile->OnCollide(Tile::Direction::LEFT, txSet, tySet);
                    if (tile->hasCollision) {
                        CollideLeft(tx + Game::TileSize);
                    }
                }

                if (right) {
                    tile->OnCollide(Tile::Direction::RIGHT, txSet, tySet);
                    if (tile->hasCollision) {
                        CollideRight(tx);
                    }
                }
                //---------------------------

                #ifdef VERSION2
                touchedFlag = false;
                #endif
            }
        }
    }
}