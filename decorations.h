#pragma once
#include "tile.h"

namespace Tmpl8
{
	class Decoration : public Tile {
	public:
		Decoration() {
			hasCollision = false;
		}
	};

	class Plant1 : public Decoration {
	public:
		Plant1() {
			mapX = 1;
			mapY = 1;
		}
	};

	class Plant2 : public Decoration {
	public:
		Plant2() {
			mapX = 4;
			mapY = 1;
		}
	};

	class BushL : public Decoration {
	public:
		BushL() {
			mapX = 10;
			mapY = 1;
		}
	};

	class BushR : public Decoration {
	public:
		BushR() {
			mapX = 11;
			mapY = 1;
		}
	};

	class Rock1 : public Decoration {
	public:
		Rock1() {
			mapX = 2;
			mapY = 1;
		}
	};

	class Rock2 : public Decoration {
	public:
		Rock2() {
			mapX = 5;
			mapY = 2;
		}
	};

	class BigRock : public Decoration {
	public:
		BigRock() {
			mapX = 12;
			mapY = 1;
		}
	};

	class Stump : public Decoration {
	public:
		Stump() {
			mapX = 13;
			mapY = 4;
		}
	};

	class Arrow : public Decoration {
	public:
		Arrow() {
			mapX = 6;
			mapY = 1;
		}
	};

	class Cloud1 : public Decoration {
	public:
		Cloud1() {
			mapX = 7;
			mapY = 1;
		}
	};

	class Cloud2 : public Decoration {
	public:
		Cloud2() {
			mapX = 8;
			mapY = 1;
		}
	};

	class Cloud3 : public Decoration {
	public:
		Cloud3() {
			mapX = 9;
			mapY = 1;
		}
	};

	class Cloud4 : public Decoration {
	public:
		Cloud4() {
			mapX = 7;
			mapY = 2;
		}
	};

	class Cloud5 : public Decoration {
	public:
		Cloud5() {
			mapX = 8;
			mapY = 2;
		}
	};

	class Cloud6 : public Decoration {
	public:
		Cloud6() {
			mapX = 9;
			mapY = 2;
		}
	};

	class Cloud7 : public Decoration {
	public:
		Cloud7() {
			mapX = 7;
			mapY = 3;
		}
	};

	class Cloud8 : public Decoration {
	public:
		Cloud8() {
			mapX = 8;
			mapY = 3;
		}
	};

	class Cloud9 : public Decoration {
	public:
		Cloud9() {
			mapX = 9;
			mapY = 3;
		}
	};
}