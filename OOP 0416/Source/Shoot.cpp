#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "CBall.h"
#include "Shoot.h"
#include "BOSS.h"
#include "jumpBall.h"


namespace game_framework {
	int Ammo = 0;
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	CShoot::CShoot()
	{
		is_alive = true;
		x = y = dx = dy = 0;
		delay_counter = 0;
	}
	bool CShoot::hitBall(CBall* ball) {
			int x1 = x;
			int x2 = x + bmp.Width();
			int y1 = y;
			int y2 = y + bmp.Height();
			int tx1 = ball->GetX1();
			int ty1 = ball->GetY1();
			int tx2 = ball->GetX2();
			int ty2 = ball->GetY2();
			return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
	bool CShoot::hitBOSS(CBOSS* BOSS) {
		int x1 = x;
		int x2 = x + bmp.Width();
		int y1 = y;
		int y2 = y + bmp.Height();
		int tx1 = BOSS->GetX1();
		int ty1 = BOSS->GetY1();
		int tx2 = BOSS->GetX2();
		int ty2 = BOSS->GetY2();
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
	bool CShoot::hitJBall(CJBALL* JBALL) {
		int x1 = x;
		int x2 = x + bmp.Width();
		int y1 = y;
		int y2 = y + bmp.Height();
		int tx1 = JBALL->GetX1();
		int ty1 = JBALL->GetY1();
		int tx2 = JBALL->GetX2();
		int ty2 = JBALL->GetY2();
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool CShoot::HitRectangle(int tx1, int ty1, int tx2, int ty2) {
		int x1 = x + dx;				// 球的左上角x座標
		int y1 = y + dy;				// 球的左上角y座標
		int x2 = x1 + bmp.Width();	// 球的右下角x座標
		int y2 = y1 + bmp.Height();	// 球的右下角y座標



									//
									// 檢測球的矩形與參數矩形是否有交集
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool CShoot::IsAlive()
	{
		return is_alive;
	}

	void CShoot::LoadBitmap()
	{
		bmp.AddBitmap(IDB_Shoot, RGB(181, 230, 29));			// 載入球的圖形
		bmp_center.AddBitmap(IDB_00, RGB(0, 0, 0));	// 載入球圓心的圖形
		bmp_center2.AddBitmap(IDB_00, RGB(0, 0, 0));	// 載入球圓心的圖形
		bmp_center3.AddBitmap(IDB_00, RGB(0, 0, 0));	// 載入球圓心的圖形


	}

	void CShoot::OnMove()
	{
		if (!is_alive)
			return;
		delay_counter--;
		if (delay_counter < 0) {
			delay_counter = delay;
			const int STEPS = 16;
			index++;
			if (index >= STEPS) {
				index = 0;
				SetIsAlive(false);
			}
			if (FacingLeft &&	is_alive) {
				x -= 30;
			}
			else if(FacingRight && is_alive) {
				x += 30;
			}
		}
	}
	void CShoot::setFacingLeft(bool F)
	{
		FacingLeft = F;

	}
	void CShoot::setFacingRight(bool F)
	{
		FacingRight = F;
	}
	void CShoot::SetDelay(double d)
	{
		delay = d;
	}
	int CShoot::getLeft()
	{
		return Ammo;
	}

	void CShoot::setLeft(int n) {
		Ammo += n;
		if (Ammo > 999) {
			Ammo = 999;
		}
		if (Ammo <= 0) {
			Ammo = 0;
		}

		if (Ammo  / 100 % 10== 1) {
			bmp_center3.deleteBMP();
			bmp_center3.AddBitmap(IDB_1, RGB(0, 0, 0));
		}
		else if (Ammo  / 100 %10  == 2) {
			bmp_center3.deleteBMP();
			bmp_center3.AddBitmap(IDB_2, RGB(0, 0, 0));
		}
		else if (Ammo  / 100 % 10  == 3) {
			bmp_center3.deleteBMP();
			bmp_center3.AddBitmap(IDB_3, RGB(0, 0, 0));
		}
		else if (Ammo  / 100 % 10  == 4) {
			bmp_center3.deleteBMP();
			bmp_center3.AddBitmap(IDB_4, RGB(0, 0, 0));
		}
		else if (Ammo  / 100 % 10  == 5) {
			bmp_center3.deleteBMP();
			bmp_center3.AddBitmap(IDB_5, RGB(0, 0, 0));
		}
		else if (Ammo  / 100 % 10  == 6) {
			bmp_center3.deleteBMP();
			bmp_center3.AddBitmap(IDB_6, RGB(0, 0, 0));
		}
		else if (Ammo  / 100 % 10  == 7) {
			bmp_center3.deleteBMP();
			bmp_center3.AddBitmap(IDB_7, RGB(0, 0, 0));
		}
		else if (Ammo  / 100 % 10  == 8) {
			bmp_center3.deleteBMP();
			bmp_center3.AddBitmap(IDB_8, RGB(0, 0, 0));
		}
		else if (Ammo  / 100 % 10  == 9) {
			bmp_center3.deleteBMP();
			bmp_center3.AddBitmap(IDB_9, RGB(0, 0, 0));
		}
		else if (Ammo  / 100 % 10  == 0) {
			bmp_center3.deleteBMP();
			bmp_center3.AddBitmap(IDB_0, RGB(0, 0, 0));
		}


		if (Ammo  / 10 %10 == 1) {
			bmp_center2.deleteBMP();
			bmp_center2.AddBitmap(IDB_1, RGB(0, 0, 0));
		}
		else if (Ammo  / 10 % 10 == 2) {
			bmp_center2.deleteBMP();
			bmp_center2.AddBitmap(IDB_2, RGB(0, 0, 0));
		}
		else if (Ammo  / 10 % 10 == 3) {
			bmp_center2.deleteBMP();
			bmp_center2.AddBitmap(IDB_3, RGB(0, 0, 0));
		}
		else if (Ammo  / 10 % 10 == 4) {
			bmp_center2.deleteBMP();
			bmp_center2.AddBitmap(IDB_4, RGB(0, 0, 0));
		}
		else if (Ammo  / 10 % 10 == 5) {
			bmp_center2.deleteBMP();
			bmp_center2.AddBitmap(IDB_5, RGB(0, 0, 0));
		}
		else if (Ammo / 10 % 10 == 6) {
			bmp_center2.deleteBMP();
			bmp_center2.AddBitmap(IDB_6, RGB(0, 0, 0));
		}
		else if (Ammo  / 10 % 10 == 7) {
			bmp_center2.deleteBMP();
			bmp_center2.AddBitmap(IDB_7, RGB(0, 0, 0));
		}
		else if (Ammo  / 10 % 10 == 8) {
			bmp_center2.deleteBMP();
			bmp_center2.AddBitmap(IDB_8, RGB(0, 0, 0));
		}
		else if (Ammo  / 10 % 10 == 9) {
			bmp_center2.deleteBMP();
			bmp_center2.AddBitmap(IDB_9, RGB(0, 0, 0));
		}
		else if (Ammo  / 10 % 10 == 0) {
			bmp_center2.deleteBMP();
			bmp_center2.AddBitmap(IDB_0, RGB(0, 0, 0));
		}


		if (Ammo   % 10== 1) {
			bmp_center.deleteBMP();
			bmp_center.AddBitmap(IDB_1, RGB(0, 0, 0));
		}
		else if (Ammo % 10== 2) {
			bmp_center.deleteBMP();
			bmp_center.AddBitmap(IDB_2, RGB(0, 0, 0));
		}
		else if (Ammo  % 10 == 3) {
			bmp_center.deleteBMP();
			bmp_center.AddBitmap(IDB_3, RGB(0, 0, 0));
		}
		else if (Ammo  % 10  == 4) {
			bmp_center.deleteBMP();
			bmp_center.AddBitmap(IDB_4, RGB(0, 0, 0));
		}
		else if (Ammo  % 10  == 5) {
			bmp_center.deleteBMP();
			bmp_center.AddBitmap(IDB_5, RGB(0, 0, 0));
		}
		else if (Ammo % 10  == 6) {
			bmp_center.deleteBMP();
			bmp_center.AddBitmap(IDB_6, RGB(0, 0, 0));
		}
		else if (Ammo  % 10  == 7) {
			bmp_center.deleteBMP();
			bmp_center.AddBitmap(IDB_7, RGB(0, 0, 0));
		}
		else if (Ammo  % 10  == 8) {
			bmp_center.deleteBMP();
			bmp_center.AddBitmap(IDB_8, RGB(0, 0, 0));
		}
		else if (Ammo  % 10  == 9) {
			bmp_center.deleteBMP();
			bmp_center.AddBitmap(IDB_9, RGB(0, 0, 0));
		}
		else if (Ammo  % 10 == 0) {
			bmp_center.deleteBMP();
			bmp_center.AddBitmap(IDB_0, RGB(0, 0, 0));
		}

	}




	void CShoot::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void CShoot::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CShoot::OnShow(GameMap* m)
	{
		bmp_center3.SetTopLeft(20,35);
		bmp_center3.OnShow();
		bmp_center2.SetTopLeft(30, 35);
		bmp_center2.OnShow();
		bmp_center.SetTopLeft(40, 35);
		bmp_center.OnShow();
		if (is_alive) {
			bmp.SetTopLeft(m->ScreenX(x + dx), m->ScreenY(y + dy));
			bmp.OnShow();

		}
	}
	int CShoot::GetX1()
	{
		return  x ;
	}

	int CShoot::GetY1()
	{
		return  y ; 
	}

	int CShoot::GetX2()
	{
		return x + bmp.Width();;
	}

	int CShoot::GetY2()
	{
		return y + bmp.Height();
	}
}