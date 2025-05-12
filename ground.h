#pragma once
#include "tile.h"

namespace Tmpl8
{
	class GroundTL : public Tile {
	public:
		GroundTL() {
			mapX = 0;
			mapY = 0;
			id = 1;
		}
	};

	class GroundTM : public Tile {
	public:
		GroundTM() {
			mapX = 1;
			mapY = 0;
			id = 2;
		}
	};

	class GroundTR : public Tile {
	public:
		GroundTR() {
			mapX = 2;
			mapY = 0;
			id = 3;
		}
	};

	class GroundML : public Tile {
	public:
		GroundML() {
			mapX = 0;
			mapY = 1;
			id = 4;
		}
	};

	class GroundMM : public Tile {
	public:
		GroundMM() {
			mapX = 1;
			mapY = 1;
			id = 5;
		}
	};

	class GroundMR : public Tile {
	public:
		GroundMR() {
			mapX = 2;
			mapY = 1;
			id = 6;
		}
	};

	class GroundBL : public Tile {
	public:
		GroundBL() {
			mapX = 0;
			mapY = 2;
			id = 7;
		}
	};

	class GroundBM : public Tile {
	public:
		GroundBM() {
			mapX = 1;
			mapY = 2;
			id = 8;
		}
	};

	class GroundBR : public Tile {
	public:
		GroundBR() {
			mapX = 2;
			mapY = 2;
			id = 9;
		}
	};
}