#pragma once

namespace Tmpl8 
{
    class Surface;

    class Player {
        public:
            Player(float x, float y, float velocityX = 0, float velocityY = 0, bool grounded = false)
            {
                x = x;
                y = y;
                velocityX = velocityX;
                velocityY = velocityY;
                grounded = grounded;
            }
    
            void MoveLeft(float deltaTime);
    
            void MoveRight(float deltaTime);
    
            void Jump(float deltaTime);
    
            void Draw(Surface* gameScreen);
    
            void Collisions(Surface* screen);
    
            void Physics(float deltaTime);
    
            void CollideTop();
    
            void CollideBottom();
    
            void CollideLeft();
    
            void CollideRight();
    
            float x, y;
            float velocityX, velocityY;
            float speed = 0.25;
            bool facingRight = true;
            float gravity = 0.005;
            float jumpForce = 3.5;
            bool grounded;
    };
}