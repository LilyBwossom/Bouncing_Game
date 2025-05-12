#include <vector>
#include "tile.h"
#pragma once

namespace Tmpl8 
{
	class Surface;
	
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

			constexpr static int TileSize = 64;
			constexpr static int WorldTilesX = 26;
			constexpr static int WorldTilesY = 18;

			static int CameraX, CameraY;
			static char map[WorldTilesY][WorldTilesX * 2];

			struct TileData
			{
				int ScreenX;
				int ScreenY;
				Tile tile;
			};

			TileData getTileScreen(int x, int y);
		private:
			Surface* screen;
			void DrawTile(Surface* screen, int tx, int ty, int x, int y);
			void DrawTileSet(Surface* screen);
	};
};