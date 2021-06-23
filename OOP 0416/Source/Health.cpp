#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "Health.h"

namespace game_framework {

	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////
	CHealth::CHealth()
	{
		is_alive = true;
		x = y = dx = dy = index = 0;
		delay_counter = 0;
	}

	bool CHealth::HitEraser(CEraser* eraser)
	{
		// �˴����l�Һc�����x�άO�_�I��y
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}

	bool CHealth::HitRectangle(int tx1, int ty1, int tx2, int ty2) {
		int x1 = x + dx;				// �y�����W��x�y��
		int y1 = y + dy;				// �y�����W��y�y��
		int x2 = x1 + bmp.Width();	// �y���k�U��x�y��
		int y2 = y1 + bmp.Height();	// �y���k�U��y�y��

									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool CHealth::IsAlive()
	{
		return is_alive;
	}
	
	void CHealth::LoadBitmap()
	{
		bmp.AddBitmap(IDB_HEALTH, RGB(181, 230, 29));			// ���J�y���ϧ�
	}


	void CHealth::OnMove()
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
			
		}
		
		
	}

	void CHealth::SetDelay(double d)
	{
		delay = d;
	}

	void CHealth::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void CHealth::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	
	void CHealth::OnShow(GameMap* m)
	{

		if (is_alive) {
			bmp.SetTopLeft(m->ScreenX(x + dx), m->ScreenY(y + dy));
			bmp.OnShow();

		}

	}
}