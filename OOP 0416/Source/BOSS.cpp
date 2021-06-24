#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "BOSS.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	CBOSS::CBOSS()
	{
		is_alive = true;
		x = y = dx = dy = 0;
		index = 0;
		delay_counter = 0;
	}

	bool CBOSS::HitEraser(CEraser *eraser)
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

	bool CBOSS::HurtEraser(CEraser* eraser)
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


	bool CBOSS::HitRectangle(int tx1, int ty1, int tx2, int ty2){
		int x1 = x + dx;				// �y�����W��x�y��
		int y1 = y + dy;				// �y�����W��y�y��
		int x2 = x1 + boss.Width();	// �y���k�U��x�y��
		int y2 = y1 + boss.Height();	// �y���k�U��y�y��
		
									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool CBOSS::IsAlive()
	{
		return is_alive;
	}

	void CBOSS::LoadBitmap()
	{
		boss.AddBitmap(IDB_BOSS, RGB(181, 230, 29));			// ���J�y���ϧ�
		

		//bmp_center.LoadBitmap(IDB_CENTER, RGB(0, 0, 0));	// ���J�y��ߪ��ϧ�

	}

	void CBOSS::OnMove()
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
			const int STEPS = 288;
			static const int DIFFX[] = { 0, 0, 0, 0,  0,  0,  0,  0,  0,   0,   0,  0,  0,  0,  0,  0, 0, 0, 0,  0,  0,  0,  0,  0, 0, 0, 0, 0,  0,  0,  0,  0,  0,   0,   0,  0,  0,  0,  0,  0, 0, 0, 0,  0,  0,  0,  0,  0 , 0, 0, 0, 0,  0,  0,  0,  0,  0,   0,   0,  0,  0,  0,  0,  0, 0, 0, 0,  0,  0,  0,  0,  0,8 * -1,8*-2,8 * -3,8 * -4,8 * -5,8 * -6,8 * -7,8 * -8,8 * -9,8 * -10,8 * -11,8 * -12,8*-13, 8 * -14, 8 * -15, 8 * -16, 8 * -17, 8 * -18, 8 * -19, 8 * -20, 8 * -21, 8 * -22, 8 * -23, 8 * -24, 8 * -25, 8 * -26, 8 * -27, 8 * -28, 8 * -29, 8 * -30, 8 * -31, 8 * -32,8 * -33,8 * -34,8 * -35,8 * -36,8 * -37,8 * -38,8 * -39,8 * -40,8 * -41,8 * -42,8 * -43,8 * -44,8 * -45, 8 * -46, 8 * -47, 8 * -48, 8 * -49, 8 * -50, 8 * -51, 8 * -52, 8 * -53, 8 * -54, 8 * -55, 8 * -56, 8 * -57, 8 * -58, 8 * -59, 8 * -60, 8 * -61, 8 * -62, 8 * -63, 8 * -64, 8* -64, 8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8 * -64,  8* -64,8 * -63,8 * -62,8 * -61,8 * -59,8 * -58,8 * -57,8 * -56,8 * -55,8 * -54,8 * -53,8 * -52,8 * -51,8 * -50,8 * -49,8 * -48,8 * -47,8 * -46,8 * -45,8 * -44,8 * -43,8 * -42,8 * -41,8 * -40,8 * -39,8 * -38,8 * -37,8 * -36,8 * -35,8 * -34,8 * -33,8 * -32,8 * -32,   8 * -31,  8 * -30,  8 * -29, 8 * -28, 8 * -27, 8 * -26, 8 * -25,  8 * -24,  8 * -23,  8 * -22,  8 * -21,  8 * -20,  8 * -19,  8 * -18,  8 * -17, 8 * -16,  8 * -15,  8 * -14,  8 * -13,  8 * -12,  8 * -11,  8 * -10,  8 * -9,  8 * -8,  8 * -7,  8 * -6,  8 * -5,  8 * -4,  8 * -3,  8 * -2,  8 * -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
			static const int DIFFY[] = { 0, 0,-20,-30,-40,-60,-80,-100,-120,-140,-160,-180,-200,-180,-160,-140,-120,-100, -80, -60, -40, -20, 0, 0,0, 0,-20,-30,-40,-60,-80,-100,-120,-140,-160,-180,-200,-180,-160,-140,-120,-100, -80, -60, -40, -20, 0, 0, 0, 0,-20,-30,-40,-60,-80,-100,-120,-140,-160,-180,-200,-180,-160,-140,-120,-100, -80, -60, -40, -20, 0, 0, 0, 0,-20,-30,-40,-60,-80,-100,-120,-140,-160,-180,-200,-180,-160,-140,-120,-100, -80, -60, -40, -20, 0, 0,  0, 0,-20,-30,-40,-60,-80,-100,-120,-140,-160,-180,-200,-180,-160,-140,-120,-100, -80, -60, -40, -20, 0, 0,  0, 0,-20,-30,-40,-60,-80,-100,-120,-140,-160,-180,-200,-180,-160,-140,-120,-100, -80, -60, -40, -20, 0, 0, 0, 0,-20,-30,-40,-60,-80,-100,-120,-140,-160,-180,-200,-180,-160,-140,-120,-100, -80, -60, -40, -20, 0, 0,0, 0,-20,-30,-40,-60,-80,-100,-120,-140,-160,-180,-200,-180,-160,-140,-120,-100, -80, -60, -40, -20, 0, 0,  0, 0,-20,-30,-40,-60,-80,-100,-120,-140,-160,-180,-200,-180,-160,-140,-120,-100, -80, -60, -40, -20, 0, 0, 0, 0,-20,-30,-40,-60,-80,-100,-120,-140,-160,-180,-200,-180,-160,-140,-120,-100, -80, -60, -40, -20, 0, 0,  0, 0,-20,-30,-40,-60,-80,-100,-120,-140,-160,-180,-200,-180,-160,-140,-120,-100, -80, -60, -40, -20, 0, 0,  0, 0,-20,-30,-40,-60,-80,-100,-120,-140,-160,-180,-200,-180,-160,-140,-120,-100, -80, -60, -40, -20, 0, 0, };
			index++;
			if (index >= STEPS)
				index = 0;
			dx = DIFFX[index];
			dy = DIFFY[index];
		}
	}

	int CBOSS::GetX1()
	{
		return  x;
	}

	int CBOSS::GetY1()
	{
		return  y;
	}

	int CBOSS::GetX2()
	{
		return x + boss.Width();;
	}

	int CBOSS::GetY2()
	{
		return y + boss.Height();
	}
	void CBOSS::SetDelay(double d)
	{
		delay = d;
	}

	void CBOSS::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void CBOSS::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CBOSS::OnShow(GameMap* m)
	{
		if (is_alive) {
			boss.SetTopLeft(m->ScreenX(x + dx), m->ScreenY(y + dy));
			boss.OnShow();
			//bmp_center.SetTopLeft(x, y);
			//bmp_center.ShowBitmap();
		}
	}
}