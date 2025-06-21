#include "ground.h"

namespace Tmpl8
{
	int GroundMM::getMapX() {
		//generate a random number between 0 and 5
		return mapX + rand() & 6;
	}
}