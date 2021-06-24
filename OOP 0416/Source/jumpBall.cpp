#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "jumpBall.h"


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CJBALL: Ball class
	/////////////////////////////////////////////////////////////////////////////

	CJBALL::CJBALL()
	{
		is_alive = true;
		x = y = dx = dy = 0;
		index = rand()%24;
		delay_counter = 0;
	}
	int CJBALL::GetX1()
	{
		return  x;
	}

	int CJBALL::GetY1()
	{
		return  y;
	}

	int CJBALL::GetX2()
	{
		return x + JumpBall.Width();;
	}

	int CJBALL::GetY2()
	{
		return y + JumpBall.Height();
	}
	bool CJBALL::HitEraser(CEraser *eraser)
	{
		// �˴����l�Һc�����x�άO�_�I��y
		if (eraser->isFacing() == 0) {
			return HitRectangle(eraser->GetX2()-24, eraser->GetY1(),
				eraser->GetX2()+8, eraser->GetY2());
		}
		else {
			return HitRectangle(eraser->GetX1()-8, eraser->GetY1(),
				eraser->GetX1()+24, eraser->GetY2());
		}
	}

	bool CJBALL::HurtEraser(CEraser* eraser)
	{
		// �˴����l�Һc�����x�άO�_�I��y
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


	bool CJBALL::HitRectangle(int tx1, int ty1, int tx2, int ty2){
		int x1 = x + dx;				// �y�����W��x�y��
		int y1 = y + dy;				// �y�����W��y�y��
		int x2 = x1 + JumpBall.Width();	// �y���k�U��x�y��
		int y2 = y1 + JumpBall.Height();	// �y���k�U��y�y��
		
									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool CJBALL::IsAlive()
	{
		return is_alive;
	}

	void CJBALL::LoadBitmap()
	{
		JumpBall.AddBitmap(IDB_JBall, RGB(181, 230, 29));			// ���J�y���ϧ�
		
	}

	void CJBALL::OnMove()
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
			const int STEPS = 24;
			static const int DIFFX[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
			static const int DIFFY[] = { 0, 0,-20,-30,-40,-60,-80,-100,-120,-140,-160,-180,-200,-180,-160,-140,-120,-100, -80, -60, -40, -20, 0, 0 };
			index++;
			if (index >= STEPS)
				index = 0;
			dx = DIFFX[index];
			dy = DIFFY[index];

		}
	}

	void CJBALL::SetDelay(double d)
	{
		delay = d;
	}

	void CJBALL::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void CJBALL::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CJBALL::OnShow(GameMap* m)
	{
		if (is_alive) {
			JumpBall.SetTopLeft(m->ScreenX(x + dx), m->ScreenY(y + dy));
			JumpBall.OnShow();
			//JumpBall_center.SetTopLeft(x, y);
			//JumpBall_center.ShowBitmap();
		}
	}
}