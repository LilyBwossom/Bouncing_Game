#pragma once

namespace Tmpl8
{
	class Tile {
		public:
			// virtual destructor
			virtual ~Tile() = default;

			enum Direction {
				TOP,
				BOTTOM,
				LEFT,
				RIGHT
			};

			enum CollisionType {
				FULL,
				HALF
			};

			virtual void OnCollide(Direction dir, int txSet, int tySet) {};
			virtual void updateAnim() {};

			void ChangeSprite(int x, int y);

			int mapX, mapY;

			CollisionType collisionType = FULL;

			bool hasCollision = true;
	};
}