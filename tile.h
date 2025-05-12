#pragma once

namespace Tmpl8
{
	enum Direction {
		TOP,
		BOTTOM,
		LEFT,
		RIGHT
	};

	class Tile {
		public:
			// virtual destructor
			virtual ~Tile() = default;

			virtual void OnCollide(Direction dir) {};

			void ChangeSprite(int x, int y);

			int mapX, mapY;
			int id;

			bool hasCollision = true;
		private:
	};
}