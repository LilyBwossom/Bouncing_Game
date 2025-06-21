#pragma once
#include "levelmanager.h"
#include "tile.h"
#include "ending.h"
#include "powerups.h"
#include "ice.h"
#include "blower.h"
#include "decorations.h"
#include "surface.h"
#include "template.h"
#include "windows.h"
#include "flag.h"
#include "spike.h"
#include "coin.h"
#include "ground.h"
#include "player.h"
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <map>

namespace Tmpl8 
{
	class Surface;
	class Player;
	
	class Game
	{
		public:
			void SetTarget( Surface* surface ) { screen = surface; }
			void Init();
			void Shutdown();
			void Tick( float deltaTime );
			void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
			void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
			void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
			void KeyUp( int key ) { /* implement if you want to handle keys */ }
			void KeyDown( int key ) { /* implement if you want to handle keys */ }

			static void SetTile(char tileType[3], int txSet, int tySet);
			static Tile* GetTile(int txSet, int tySet);

			static Player player;

			constexpr static int TileSize = 64;
			static Tmpl8::map map;
			static void Game::ChangeLevel(Tmpl8::map level);

			static int CameraX, CameraY;

		private:
			Surface* screen;
			void DrawTile(Surface* screen, int tx, int ty, int screenX, int screenY, int x, int y);
			void DrawTileSet(Surface* screen);

			void Animate(float deltaTime);
	};
};