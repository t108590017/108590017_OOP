#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "Ammo.h"

namespace game_framework {

	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////
	CAmmo::CAmmo()
	{
		is_alive = true;
		x = y = dx = dy = index = 0;
		delay_counter = 0;
	}

	bool CAmmo::HitEraser(CEraser* eraser)
	{
		// �˴����l�Һc�����x�άO�_�I��y
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}

	bool CAmmo::HitRectangle(int tx1, int ty1, int tx2, int ty2) {
		int x1 = x + dx;				// �y�����W��x�y��
		int y1 = y + dy;				// �y�����W��y�y��
		int x2 = x1 + bmp.Width();	// �y���k�U��x�y��
		int y2 = y1 + bmp.Height();	// �y���k�U��y�y��

									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool CAmmo::IsAlive()
	{
		return is_alive;
	}

	void CAmmo::LoadBitmap()
	{
		bmp.AddBitmap(IDB_Bullet , RGB(181, 230, 29));			// ���J�y���ϧ�

	}


	void CAmmo::OnMove()
	{

		if (!is_alive)
			return;
		delay_counter--;
		if (delay_counter < 0) {
			delay_counter = delay;
			//
			// �p��y�V����ߪ��첾�qdx, dy
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

	void CAmmo::SetDelay(double d)
	{
		delay = d;
	}

	void CAmmo::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void CAmmo::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}
	void CAmmo::OnShow(GameMap* m)
	{
		if (is_alive) {
			bmp.SetTopLeft(m->ScreenX(x + dx), m->ScreenY(y + dy));
			bmp.OnShow();

		}
	}
}