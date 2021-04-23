#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"


namespace game_framework {
	GameMap::GameMap() :X(0), Y(0), MH(32), MW(32) {
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		int map_init[15][20] = {   {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
								   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
								   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
								   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
								   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
								   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
								   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
								   {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
								   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
								   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
								   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
								   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
								   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
								   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
								   {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}
		};
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 20; j++)
				map[i][j] = map_init[i][j];


	}
	void GameMap::LoadBitmap() {
		blue.LoadBitmap(IDB_BLUE, RGB(181, 230, 29));
		green.LoadBitmap(IDB_GREEN, RGB(181, 230, 29));
		block.LoadBitmap(IDB_BLOCK, RGB(181, 230, 29));
		block2.LoadBitmap(IDB_BLOCK2, RGB(181, 230, 29));


	}
	bool GameMap::IsEmpty(int x, int y) {
		int gx = x / MH;
		int gy = y / MW;
		return ((map[gy][gx] == 0) && x <= 640 && x >= 0 && y <= 480 && y >= 0);
	}


	void GameMap::OnShow() {
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				int sx = i * MW - X;
				int sy = j * MH - Y;

				switch (map[j][i])
				{
				case 0:
					break;
				case 1:
					block.SetTopLeft(sx,sy);
					block.ShowBitmap();
					break;
				case 2:
					block2.SetTopLeft(sx, sy);
					block2.ShowBitmap();
					break;
				default:
					ASSERT(0);
				}
			}

		}
	}
	int GameMap::ScreenX(int x) {
		return x - X;
	}
	int GameMap::ScreenY(int y) {
		return y - Y;
	}
	void GameMap::OnMove() {
		if (isMovingLeft)
			X -= 10;
		if (isMovingRight)
			X += 10;
		if (isMovingUp)
			Y -= 10;
		if (isMovingDown)
			Y += 10;
	}
	void GameMap::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void GameMap::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void GameMap::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void GameMap::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}
}