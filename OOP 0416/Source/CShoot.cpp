#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "CShoot.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	CShoot::CShoot()
	{
		is_alive = true;
		x = y = dx = dy = 0;
		index = rand()%100;
		delay_counter = 0;
	}

	bool CShoot::HitEraser(CEraser *eraser)
	{
		// 檢測擦子所構成的矩形是否碰到球
		if (eraser->isFacing() == 0) {
			return HitRectangle(eraser->GetX2()-24, eraser->GetY1(),
				eraser->GetX2()+8, eraser->GetY2());
		}
		else {
			return HitRectangle(eraser->GetX1()-8, eraser->GetY1(),
				eraser->GetX1()+24, eraser->GetY2());
		}
	}

	bool CShoot::HurtEraser(CEraser* eraser)
	{
		// 檢測擦子所構成的矩形是否碰到球
		if (eraser->isFacing() == 0 && eraser->isAttacking()) {
			return HitRectangle(eraser->GetX1(), eraser->GetY1(),
				eraser->GetX2() - 80, eraser->GetY2());
		}
		else if (eraser->isFacing() == 0 && !eraser->isAttacking()) {
			return HitRectangle(eraser->GetX1(), eraser->GetY1(),
				eraser->GetX2() - 40, eraser->GetY2());
		}
		else if (eraser->isFacing() == 1 && !eraser->isAttacking()) {
			return HitRectangle(eraser->GetX1() + 30, eraser->GetY1(),
				eraser->GetX1() + 50, eraser->GetY2());
		}
		else if (eraser->isFacing() == 1) {
			return HitRectangle(eraser->GetX1() + 30, eraser->GetY1(),
				eraser->GetX1() + 50, eraser->GetY2());
		}
		else
			return false;
	}


	bool CShoot::HitRectangle(int tx1, int ty1, int tx2, int ty2){
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
		bmp.AddBitmap(IDB_enemy1, RGB(181, 230, 29));			// 載入球的圖形
		
	}

	void CShoot::OnMove()
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
			static const int DIFFX[] = { 0,3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,48,51,54,57,60,60,60,60,60,60,60,60,60,60,60,57,54,51,48,45,42,39,36,33,30,27,24,21,18,15,12,9,6,3,0,-3,-6,-9,-12,-15,-18,-21,-24,-27,-30,-33,-36,-39,-42,-45,-48,-51,-54,-57,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-57,-54,-51,-48,-45,-42,-39,-36,-33,-30,-27,-24,-21,-18,-15,-12,-9,-6,-3 };
			static const int DIFFY[] = { 0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, };
			index++;
			if (index >= STEPS)
				index = 0;
			dx = DIFFX[index];
			dy = DIFFY[index];

			if ((index >= 20 &&index<=30)|| index >= 70 && index <= 80) {
				bmp.deleteBMP();
				bmp.AddBitmap(IDB_enemy1_S, RGB(181, 230, 29));
			}
			else if  (index > 30 && index < 70) {
				bmp.deleteBMP();
				bmp.AddBitmap(IDB_enemy1_L, RGB(181, 230, 29));
			}
			else {
				bmp.deleteBMP();
				bmp.AddBitmap(IDB_enemy1, RGB(181, 230, 29));
			}
		}
	}

	void CShoot::SetDelay(double d)
	{
		delay = d;
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
		if (is_alive) {
			bmp.SetTopLeft(m->ScreenX(x + dx), m->ScreenY(y + dy));
			bmp.OnShow();
			//bmp_center.SetTopLeft(x, y);
			//bmp_center.ShowBitmap();
		}
	}
}