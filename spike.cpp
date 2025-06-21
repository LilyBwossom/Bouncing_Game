#include "spike.h"

namespace Tmpl8
{
	void Spike::OnCollide(Tile::Direction, int txSet, int tySet)
	{
		Game::player.Respawn();
	}
}

