#pragma once
#include "tile.h"
#include "game.h"

namespace Tmpl8
{
	class Spike : public Tile {
	public:
		Spike() {
			hasCollision = false;
			collisionType = CollisionType::HALF;
		}

		void OnCollide(Direction dir, int txSet, int tySet) override;
	};

	class IronSpike : public Spike {
	public:
		IronSpike() {
			mapX = 0;
			mapY = 0;
		}
	};

	class WoodSpike1 : public Spike {
	public:
		WoodSpike1() {
			mapX = 13;
			mapY = 3;
		}
	};

	class WoodSpike2 : public Spike {
	public:
		WoodSpike2() {
			mapX = 14;
			mapY = 3;
		}
	};
}