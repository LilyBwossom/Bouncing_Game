#include "flag.h"

namespace Tmpl8
{
	void Flag::updateAnim()
	{
		int newMapX = mapX + 2;
		if (newMapX >= 18) {
			newMapX = frameX;
		}

		ChangeSprite(newMapX, mapY);
	}

	void Flag::OnCollide(Tile::Direction, int txSet, int tySet)
	{
		#ifdef VERSION2
		if (Game::player.touchedFlag) {
			return;
		}
		#endif

		currentLevel++;
		if (currentLevel < levelAmount) {
			//remove the flag from the game on collide
			//this so the flag doesn't accidentally change the level twice
			Game::SetTile("00", txSet, tySet);

			#ifndef VERSION2
			Game::ChangeLevel(*levels[currentLevel]);

			#else
			Game::player.touchedFlag = true;
			#endif
 			Game::player.Respawn();
		}
	}
}

