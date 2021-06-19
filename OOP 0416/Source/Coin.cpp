#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "Coin.h"

namespace game_framework {
	int coin_left = 0;

	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////
	CCoin::CCoin()
	{
		is_alive = true;
		x = y = dx = dy = index = 0;
		delay_counter = 0;
	}

	bool CCoin::HitEraser(CEraser* eraser)
	{
		// 檢測擦子所構成的矩形是否碰到球
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}

	bool CCoin::HitRectangle(int tx1, int ty1, int tx2, int ty2) {
		int x1 = x + dx;				// 球的左上角x座標
		int y1 = y + dy;				// 球的左上角y座標
		int x2 = x1 + bmp.Width();	// 球的右下角x座標
		int y2 = y1 + bmp.Height();	// 球的右下角y座標

									//
									// 檢測球的矩形與參數矩形是否有交集
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool CCoin::IsAlive()
	{
		return is_alive;
	}
	
	void CCoin::LoadBitmap()
	{
		bmp.AddBitmap(IDB_Coin, RGB(181, 230, 29));			// 載入球的圖形


		bmp_center.AddBitmap(IDB_00, RGB(0, 0, 0));	// 載入球圓心的圖形
		bmp_center2.AddBitmap(IDB_00, RGB(0, 0, 0));	// 載入球圓心的圖形



	}


	void CCoin::OnMove()
	{

		if (!is_alive)
			return;
		delay_counter--;
		if (delay_counter < 0) {
			delay_counter = delay;
			//
			// 計算球向對於圓心的位移量dx, dy
			//
			int i = 0;
			const int STEPS = 100;
			static const int DIFFX[] = { 0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, };
			static const int DIFFY[] = { 0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, };
			index++;
			if (index >= STEPS)
				index = 0;
			dx = DIFFX[index];
			dy = DIFFY[index];

			if ((index >= 20 && index <= 30) || index >= 70 && index <= 80) {
				bmp.deleteBMP();
				bmp.AddBitmap(IDB_enemy1_S, RGB(181, 230, 29));
			}
			else if (index > 30 && index < 70) {
				bmp.deleteBMP();
				bmp.AddBitmap(IDB_enemy1_L, RGB(181, 230, 29));
			}
			else {
				bmp.deleteBMP();
				bmp.AddBitmap(IDB_enemy1, RGB(181, 230, 29));
			}
		}
		
		
	}

	void CCoin::SetDelay(double d)
	{
		delay = d;
	}

	void CCoin::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void CCoin::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}
	int CCoin::getLeft()
	{
		return coin_left;
	}

	void CCoin::setLeft(int n) {

		coin_left += n;
		if (coin_left / 10 == 1) {
			bmp_center2.deleteBMP();
			bmp_center2.AddBitmap(IDB_1, RGB(0, 0, 0));
		}
		else if (coin_left / 10 == 2) {
			bmp_center2.deleteBMP();
			bmp_center2.AddBitmap(IDB_2, RGB(0, 0, 0));
		}
		else if (coin_left / 10 == 3) {
			bmp_center2.deleteBMP();
			bmp_center2.AddBitmap(IDB_3, RGB(0, 0, 0));
		}
		else if (coin_left / 10 == 4) {
			bmp_center2.deleteBMP();
			bmp_center2.AddBitmap(IDB_4, RGB(0, 0, 0));
		}
		else if (coin_left / 10 == 5) {
			bmp_center2.deleteBMP();
			bmp_center2.AddBitmap(IDB_5, RGB(0, 0, 0));
		}
		else if (coin_left / 10 == 6) {
			bmp_center2.deleteBMP();
			bmp_center2.AddBitmap(IDB_6, RGB(0, 0, 0));
		}
		else if (coin_left / 10 == 7) {
			bmp_center2.deleteBMP();
			bmp_center2.AddBitmap(IDB_7, RGB(0, 0, 0));
		}
		else if (coin_left / 10 == 8) {
			bmp_center2.deleteBMP();
			bmp_center2.AddBitmap(IDB_8, RGB(0, 0, 0));
		}
		else if (coin_left / 10 == 9) {
			bmp_center2.deleteBMP();
			bmp_center2.AddBitmap(IDB_9, RGB(0, 0, 0));
		}
		else if (coin_left / 10 == 0) {
			bmp_center2.deleteBMP();
			bmp_center2.AddBitmap(IDB_0, RGB(0, 0, 0));
		}


		if (coin_left % 10 == 1) {
			bmp_center.deleteBMP();
			bmp_center.AddBitmap(IDB_1, RGB(0, 0, 0));
		}
		else if (coin_left % 10 == 2) {
			bmp_center.deleteBMP();
			bmp_center.AddBitmap(IDB_2, RGB(0, 0, 0));
		}
		else if (coin_left % 10 == 3) {
			bmp_center.deleteBMP();
			bmp_center.AddBitmap(IDB_3, RGB(0, 0, 0));
		}
		else if (coin_left % 10 == 4) {
			bmp_center.deleteBMP();
			bmp_center.AddBitmap(IDB_4, RGB(0, 0, 0));
		}
		else if (coin_left % 10 == 5) {
			bmp_center.deleteBMP();
			bmp_center.AddBitmap(IDB_5, RGB(0, 0, 0));
		}
		else if (coin_left % 10 == 6) {
			bmp_center.deleteBMP();
			bmp_center.AddBitmap(IDB_6, RGB(0, 0, 0));
		}
		else if (coin_left % 10 == 7) {
			bmp_center.deleteBMP();
			bmp_center.AddBitmap(IDB_7, RGB(0, 0, 0));
		}
		else if (coin_left % 10 == 8) {
			bmp_center.deleteBMP();
			bmp_center.AddBitmap(IDB_8, RGB(0, 0, 0));
		}
		else if (coin_left % 10 == 9) {
			bmp_center.deleteBMP();
			bmp_center.AddBitmap(IDB_9, RGB(0, 0, 0));
		}
		else if (coin_left % 10 == 0) {
			bmp_center.deleteBMP();
			bmp_center.AddBitmap(IDB_0, RGB(0, 0, 0));
		}

	}
	void CCoin::OnShow(GameMap* m)
	{
		bmp_center.SetTopLeft(613, 35);
		bmp_center.OnShow();
		bmp_center2.SetTopLeft(603,35);
		bmp_center2.OnShow();
		if (is_alive) {
			bmp.SetTopLeft(m->ScreenX(x + dx), m->ScreenY(y + dy));
			bmp.OnShow();

		}

	}
}