#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "Shoot.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	CShoot::CShoot()
	{
		is_alive = true;
		x = y = dx = dy = index = delay_counter = 0;
	}

	bool CShoot::HitEraser(CEraser *eraser)
	{
		// �˴����l�Һc�����x�άO�_�I��y
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}

	bool CShoot::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + dx;				// �y�����W��x�y��
		int y1 = y + dy;				// �y�����W��y�y��
		int x2 = x1 + bmp.Width();	// �y���k�U��x�y��
		int y2 = y1 + bmp.Height();	// �y���k�U��y�y��
									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool CShoot::IsAlive()
	{
		return is_alive;
	}

	void CShoot::LoadBitmap()
	{
		bmp.LoadBitmap(IDB_Shoot, RGB(181, 230, 29));			// ���J�y���ϧ�
	}

	void CShoot::OnMove()
	{
		if (!is_alive)
			return;
		delay_counter--;
		if (delay_counter < 0) {
			delay_counter = delay;
			//
			// �p��y�V����ߪ��첾�qdx, dy
			//
			const int STEPS = 31;
			static const int DIFFX[] = { 0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300 };
			static const int DIFFY[] = { 0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

			index++;
			if (index >= STEPS) {
				SetIsAlive(false);
				index = 0;

			}
			if (eraser.isFacing() == 0) {
			dx = DIFFX[index];
			dy = DIFFY[index];
			}
			else if (eraser.isFacing() == 1) {
				dx = DIFFX[index]*(-1);
				dy = DIFFY[index] * (-1);
			}
		}
	}

	void CShoot::SetDelay(int d)
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
			bmp.SetTopLeft(x + dx, y + dy);
			bmp.ShowBitmap();
			if (eraser.isFacing() == 0) {
				bmp_center.SetTopLeft((eraser.GetX2()), (eraser.GetY1() + eraser.GetY2()) / 2);
			}
			else
				bmp_center.SetTopLeft((eraser.GetX1()), (eraser.GetY1() + eraser.GetY2()) / 2);
			bmp_center.ShowBitmap();
		}
	}
}