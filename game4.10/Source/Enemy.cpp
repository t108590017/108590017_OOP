#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Enemy.h"
#include "CEraser.h"
#include "Map.h"

#include <math.h>


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲角色
	/////////////////////////////////////////////////////////////////////////////
	Enemy::Enemy()
	{
		Initialize(300, 240);
	}
	Enemy::Enemy(int InputX, int InputY)
	{
		Initialize(InputX, InputY);
	}

	void Enemy::Initialize(int InputX, int InputY) {
		const int X_POS = InputX;
		const int Y_POS = InputY;
		x = X_POS;
		y = Y_POS;
		DirectionX, DirectionY = false;
		AnimationReset_State = true;
		isCollision = false;
		isHit = false;
		isMoving = true;	//正在移動
		BarIsShow = false;
		OffsetX = 0;
		OffsetY = 0;
		Blood = 100;
		BloodX = 550;
		BloodTime = 0;
		Time = 0;

	}

	void Enemy::LoadBitmap() {
		//設定初值
		AnimationCurrent.AddBitmap(IDB_enemy1, RGB(181, 230, 29));
		AnimationCurrent.AddBitmap(IDB_enemy1_S, RGB(181, 230, 29));
		AnimationCurrent.AddBitmap(IDB_enemy1_L, RGB(181, 230, 29));

		AnimationCurrent.SetDelayCount(3);

	}
	bool Enemy::collision(int mX, int mY) {
		const double Distance = 50;
		double X = pow((x - mX), 2);
		double Y = pow((y - mY), 2);
		if (sqrt(X + Y) <= Distance) {
			return true;
		}
		else {
			return false;
		}

	}
	bool Enemy::IsHit(int mX, int mY, bool Direction, bool isSpecialAction) {

		if (Direction && isSpecialAction) {
			if ((mY <= y + 30) && (mY >= y - 40) && (mX >= x - 70) && (mX <= x - 20)) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (Direction == false && isSpecialAction) {
			if ((mY <= y + 40) && (mY >= y - 30) && (mX >= x + 20) && (mX <= x + 70)) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}

	}
	int Enemy::SetOffset(int x, int Offset) {
		return (x + Offset);
	}
	int Enemy::GetBlood() {
		return Blood;
	}
	void Enemy::ShowProgress(int percent, int X) {
		if (!SHOW_LOAD_PROGRESS)
			return;
		const int bar_width = 73;
		const int bar_height = 18;
		const int x1 = X;
		const int x2 = x1 + bar_width;
		const int y1 = 102;
		const int y2 = y1 + bar_height;
		const int pen_width = bar_height / 8;
		const int progress_x1 = x1 + pen_width;
		const int progress_x2 = progress_x1 + percent * (bar_width - 2 * pen_width) / 100;
		const int progress_x2_end = x2 - pen_width;
		const int progress_y1 = y1 + pen_width;
		const int progress_y2 = y2 - pen_width;
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CPen* pp, p(PS_NULL, 0, RGB(0, 0, 0));		// 清除pen
		pp = pDC->SelectObject(&p);
		CBrush b2(RGB(255, 255, 0));					// 畫黃色 progrss進度
		pDC->SelectObject(&b2);
		pDC->Rectangle(progress_x1, progress_y1, progress_x2, progress_y2);
		pDC->SelectObject(pp);						// 釋放 pen
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
	void Enemy::OnMove(GameMap* m, CEraser* role) {
		Time += 1;
		const int STEP_SIZE = 4;
		int PlayerX = role->GetX1();
		int PlayerY = role->GetY1();
		bool PlayerDirection = role->GetDirection();
		bool PlayerSpecialAction = true;
		;
		isCollision = collision(PlayerX, PlayerY);		//是否跟腳色碰撞
		isHit = IsHit(PlayerX, PlayerY, PlayerDirection, PlayerSpecialAction);		//當腳色被主角打到
		isMoving = !isHit;		//被打到時不移動
		AnimationCurrent.OnMove();
		//HealthBar.OnMove();

		/// <summary>
		/// 腳色移動
		/// </summary>
		if (isMoving && Blood >= 0) {
			if (DirectionX) {
				x += STEP_SIZE;
			}
			else {
				x -= STEP_SIZE;
			}
			if (DirectionY) {
				y -= STEP_SIZE;
			}
			else {
				y += STEP_SIZE;
			}
		}

		if (PlayerDirection && isHit) {
			OffsetX = -12;
			OffsetY = -25;
		}
		else if (PlayerDirection == false && isHit) {
			OffsetX = -12;
			OffsetY = -19;
		}
		else {
			OffsetX = 0;
			OffsetY = 0;
		}
		if (isHit && AnimationCurrent.IsFinalBitmap() && Blood > 0) {
			/*if (Blood == 0) {
				Blood = 100;
			}*/
			Blood -= 10;
			AnimationCurrent.Reset();
			BloodTime = Time;
			BarIsShow = true;

		}
		/// <summary>
		/// 以下是角色移動的限制
		/// </summary>
		/// 
		if (x + STEP_SIZE >= 800 - 2 * AnimationCurrent.Width()) {
			DirectionX = false;
		}
		else if (x <= STEP_SIZE) {
			DirectionX = true;
		}
		if (y >= 480 - STEP_SIZE - AnimationCurrent.Height()) {
			DirectionY = true;
		}
		else if (y <= STEP_SIZE) {
			DirectionY = false;
		}
		/// <summary>
		/// 以下是角色血條持續狀態
		/// </summary>
		/// 
		if ((Time - BloodTime) >= 60) {			//血條持續時間為60格(2秒)
			BarIsShow = false;
		}
	}

	void Enemy::OnShow(GameMap* m) {
		int offset_x = SetOffset(x, OffsetX);
		int offset_y = SetOffset(y, OffsetY);

		AnimationCurrent.SetTopLeft(m->ScreenX(offset_x), m->ScreenY(offset_y)); //轉換為螢幕座標
		if (Blood > 0) {
			AnimationCurrent.OnShow();
		}

	}
}