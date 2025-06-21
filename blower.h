#pragma once
#pragma once
#include "tile.h"
#include "game.h"

namespace Tmpl8
{
	class Blower : public Tile {
	public:
		Blower() {
			mapX = 10;
			mapY = 10;
			hasCollision = false;
		}

		void OnCollide(Direction dir, int txSet, int tySet) override;
		void updateAnim() override;
	};
}