#include "ice.h"

namespace Tmpl8
{
	void Ice::OnCollide(Direction dir, int txSet, int tySet)
	{
		if (dir == Direction::BOTTOM) {
			Game::player.frictionMod = -0.2;
		}
	}
}

