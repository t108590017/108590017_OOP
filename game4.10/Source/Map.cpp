#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"


namespace game_framework {
GameMap::GameMap()
:MW(32),MH(32),sx(0),sy(0){
	isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	KeepDraw = true;

	int map_init[row][col] = {
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0}};

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			map[i][j] = map_init[i][j];
		}
	}
}

int GameMap::ScreenX(int x) {//x為地圖的點座標
	return (x - sx);			//回傳螢幕的點座標
}

int GameMap::ScreenY(int y) {//y為地圖的點座標
	return (y - sy);			//回傳螢幕的點座標
}

bool GameMap::IsEmpty(int x, int y) {
	int gx = x / MW;		//地圖格座標
	int gy = y / MH;       
	return ((map[gy][gx] == 1) && x<=800 && x>=0  && y<=480 && y>=0);  // 設定1跟0為空  以及不能超過地圖尺寸(800*480)
}

void GameMap::LoadBitmap() {
	green.LoadBitmap(IDB_GREEN);
	yellow.LoadBitmap(IDB_YELLOW);
	blue.LoadBitmap(IDB_BLUE);
	BackGround_0.LoadBitmap(IDB_BACKGROUND);
}

void GameMap::OnMove() {
	const int STEP_SIZE = 4;
	if (isMovingLeft)
		sx -= STEP_SIZE;
	if (isMovingRight)
		sx += STEP_SIZE;
	if (isMovingUp)
		sy -= STEP_SIZE;
	if (isMovingDown)
		sy += STEP_SIZE;
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


void GameMap::OnShow() {
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			int x = i * MW - sx;
			int y = j * MH - sy;
			switch (map[j][i]) {
			case 0:
				blue.SetTopLeft(x,y);
				blue.ShowBitmap();
				break;
			case 1:
				yellow.SetTopLeft(x,y);
				yellow.ShowBitmap();
				break;
			case 2:
				green.SetTopLeft(x,y);
				green.ShowBitmap();
				break;
			default:
				ASSERT(0);
			
			}
			
		}
	}
	
}
	
}