#include "powerups.h"

namespace Tmpl8
{
	void Apple::OnCollide(Tile::Direction, int txSet, int tySet)
	{
		Game::player.jumpForceUpTime = 5000;

		//remove the apple from the game on collide
		Game::SetTile("00", txSet, tySet);
	}

	void Banana::OnCollide(Tile::Direction, int txSet, int tySet)
	{
		Game::player.speedUpTime = 5000;

		//remove the banana from the game on collide
		Game::SetTile("00", txSet, tySet);
	}
}

