#include "coin.h"

namespace Tmpl8
{
	void Coin::updateAnim()
	{
		int newMapX = mapX + 1;
		if (newMapX >= 8) {
			newMapX = 0;
		}

		ChangeSprite(newMapX, mapY);
	}

	void Coin::OnCollide(Tile::Direction, int txSet, int tySet)
	{
		//remove the coin from the game on collide
		Game::SetTile("00", txSet, tySet);
	}
}

