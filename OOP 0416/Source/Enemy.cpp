#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"
#include "Enemy.h"
#include "CEraser.h"
#include <math.h>


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C������
	/////////////////////////////////////////////////////////////////////////////
	Enemy::Enemy()
	{
		Initialize();
	}
	void Enemy::Initialize() {
		const int X_POS = 300;
		const int Y_POS = 240;
		x = X_POS;
		y = Y_POS;

	}

	void Enemy::LoadBitmap() {
		//�]�w���
		bmp.AddBitmap(IDB_enemy1);
	}
	bool Enemy::HitEraser(CEraser* eraser)
	{
		// �˴����l�Һc�����x�άO�_�I��y
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}
	bool Enemy::HitRectangle(int tx1, int ty1, int tx2, int ty2) {
		int x1 = x + dx;				// �y�����W��x�y��
		int y1 = y + dy;				// �y�����W��y�y��
		int x2 = x1 + bmp.Width();	// �y���k�U��x�y��
		int y2 = y1 + bmp.Height();	// �y���k�U��y�y��

									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
	bool Enemy::IsAlive()
	{
		return is_alive;
	}

	void Enemy::OnMove(GameMap* m,Player* role) {

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
			static const int DIFFX[] = { 0,3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,48,51,54,57,60,60,60,60,60,60,60,60,60,60,60,57,54,51,48,45,42,39,36,33,30,27,24,21,18,15,12,9,6,3,0,-3,-6,-9,-12,-15,-18,-21,-24,-27,-30,-33,-36,-39,-42,-45,-48,-51,-54,-57,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-57,-54,-51,-48,-45,-42,-39,-36,-33,-30,-27,-24,-21,-18,-15,-12,-9,-6,-3 };
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

	void Enemy::OnShow(GameMap* m) {
	
	}
}
