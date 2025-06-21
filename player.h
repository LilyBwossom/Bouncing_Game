#pragma once
#include "game.h"
#include "template.h"
#include "surface.h"
#include <string>
#include <iostream>

namespace Tmpl8 
{
    class Surface;

    class Player {
        public:
            Player(bool grounded = true) : x(x), y(y)
            {
                Respawn(grounded);
            }

            void Respawn(bool spawnsGrounded = true);

            void Draw(Surface* gameScreen);
            void Collisions(Surface* screen);
            void Physics(float deltaTime);

            void MoveLeft(float deltaTime);
            void MoveRight(float deltaTime);
            void SpeedUp(float deltaTime);
            void Jump(float deltaTime);
            void JumpForceUp(float deltaTime);

            void UpdateAnim();

            float x, y;
            float velocityX = 0, velocityY = 0;
            float frictionMod = 0;
            float speed = 0.25;
            float speedMod = 0;
            float speedUpTime = 0;
            bool facingRight = true;
            float gravity = 0.015;
            #ifndef VERSION2
            float jumpForce = 0.7;
            #else
            float jumpForce = 5;
            #endif
            float jumpForceMod = 0;
            float jumpForceUpTime = 0;
            bool grounded = false;

            #ifdef VERSION2
            bool touchedFlag = false;
            #endif

        private:
            void CollideTop(int sideY);
            void CollideBottom(int sideY);
            void CollideLeft(int sideX);
            void CollideRight(int sideX);
    };
}