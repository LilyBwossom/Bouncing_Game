#pragma once
#include "tile.h"
#include "game.h"

namespace Tmpl8
{
	class Apple : public Tile {
	public:
		Apple() {
			mapX = 14;
			mapY = 5;
			hasCollision = false;
		}

		void OnCollide(Direction dir, int txSet, int tySet) override;
	};

	class Banana : public Tile {
	public:
		Banana() {
			mapX = 14;
			mapY = 6;
			hasCollision = false;
		}

		void OnCollide(Direction dir, int txSet, int tySet) override;
	};
}