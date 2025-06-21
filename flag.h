#pragma once
#include "tile.h"
#include "game.h"

namespace Tmpl8
{
	class Flag : public Tile {
	public:
		Flag() {
			hasCollision = false;
		}
		void OnCollide(Direction dir, int txSet, int tySet) override;
		void updateAnim() override;

		int frameX = 0;
	};

	class FlagTL : public Flag {
	public:
		FlagTL() {
			mapX = 0;
			mapY = 8;

			frameX = 0;
		}
	};

	class FlagTR : public Flag {
	public:
		FlagTR() {
			mapX = 1;
			mapY = 8;

			frameX = 1;
		}
	};

	class FlagBL : public Flag {
	public:
		FlagBL() {
			mapX = 0;
			mapY = 9;

			frameX = 0;
		}
	};

	class FlagBR : public Flag {
	public:
		FlagBR() {
			mapX = 1;
			mapY = 9;

			frameX = 1;
		}
	};
}