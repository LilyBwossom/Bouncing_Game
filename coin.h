#pragma once
#include "tile.h"
#include "game.h"

namespace Tmpl8
{
	class Coin : public Tile {
	public:
		Coin() {
			mapX = 0;
			mapY = 6;
			hasCollision = false;

			collisionType = CollisionType::HALF;
		}
		
		void OnCollide(Direction dir, int txSet, int tySet) override;
		void updateAnim() override;
	};
}