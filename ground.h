#pragma once
#include "tile.h"
#include <stdlib.h>

namespace Tmpl8
{
	class GroundTL : public Tile {
	public:
		GroundTL() {
			mapX = 1;
			mapY = 2;
		}
	};

	class GroundTM : public Tile {
	public:
		GroundTM() {
			mapX = 2;
			mapY = 2;
		}
	};

	class GroundTR : public Tile {
	public:
		GroundTR() {
			mapX = 4;
			mapY = 2;
		}
	};

	class GroundML : public Tile {
	public:
		GroundML() {
			mapX = 0;
			mapY = 4;
		}
	};

	class GroundMM : public Tile {
	public:
		GroundMM() {
			mapX = 3;
			mapY = 4;
		}
	};

	class GroundMR : public Tile {
	public:
		GroundMR() {
			mapX = 5;
			mapY = 4;
		}
	};

	class GroundBL : public Tile {
	public:
		GroundBL() {
			mapX = 0;
			mapY = 5;
		}
	};

	class GroundBM : public Tile {
	public:
		GroundBM() {
			mapX = 1;
			mapY = 5;
		}
	};

	class GroundBR : public Tile {
	public:
		GroundBR() {
			mapX = 5;
			mapY = 5;
		}
	};

	class GroundUL : public Tile {
	public:
		GroundUL() {
			mapX = 1;
			mapY = 3;
		}
	};

	class GroundUR : public Tile {
	public:
		GroundUR() {
			mapX = 4;
			mapY = 3;
		}
	};

	class GroundMMR1 : public Tile {
	public:
		GroundMMR1() {
			mapX = 2;
			mapY = 3;
		}
	};

	class GroundMMR2 : public Tile {
	public:
		GroundMMR2() {
			mapX = 3;
			mapY = 3;
		}
	};

	class GroundMMR3: public Tile {
	public:
		GroundMMR3() {
			mapX = 1;
			mapY = 4;
		}
	};

	class GroundMMR4 : public Tile {
	public:
		GroundMMR4() {
			mapX = 2;
			mapY = 4;
		}
	};

	class GroundMMR5 : public Tile {
	public:
		GroundMMR5() {
			mapX = 4;
			mapY = 4;
		}
	};
}