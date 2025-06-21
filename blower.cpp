#include "blower.h"

namespace Tmpl8
{
	void Blower::OnCollide(Tile::Direction, int txSet, int tySet)
	{
		#ifndef VERSION2
		Game::player.velocityY -= Game::player.jumpForce * 0.5f;
		#else
		Game::player.velocityY -= Game::player.jumpForce * 0.06f;
		#endif
	}

	void Blower::updateAnim()
	{
		int newMapX = mapX + 1;
		if (newMapX >= 14) {
			newMapX = 10;
		}

		ChangeSprite(newMapX, mapY);
	}
}

