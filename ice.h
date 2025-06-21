#pragma once
#include "tile.h"
#include "game.h"

namespace Tmpl8
{
	class Ice : public Tile {
		void OnCollide(Direction dir, int txSet, int tySet) override;
	};

	class Ice1 : public Ice {
	public:
		Ice1() {
			mapX = 6;
			mapY = 5;
		}
	};

	class Ice2 : public Ice {
	public:
		Ice2() {
			mapX = 7;
			mapY = 5;
		}
	};

	class Ice3 : public Ice {
	public:
		Ice3() {
			mapX = 8;
			mapY = 5;
		}
	};

	class Ice4 : public Ice {
	public:
		Ice4() {
			mapX = 9;
			mapY = 5;
		}
	};
}