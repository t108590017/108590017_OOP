#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CEraser::CEraser()
	{
		Initialize();
	}

	int CEraser::GetX1()
	{
		return x;
	}

	int CEraser::GetY1()
	{
		return y;
	}

	int CEraser::GetX2()
	{
		return x + animation.Width();
	}

	int CEraser::GetY2()
	{
		return y + animation.Height();
	}

	void CEraser::Initialize()
	{
		const int X_POS = 280;
		const int Y_POS = 400;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void CEraser::LoadBitmap()
	{
		animation.AddBitmap(IDB_Cartman_stick1, RGB(181, 230, 29));
		gotRight.AddBitmap(IDB_Cartman_stick1, RGB(181, 230, 29));
		Attack.AddBitmap(IDB_Cartman_stick2, RGB(181, 230, 29));
		gotLeft.AddBitmap(IDB_Cartman_stick1_L, RGB(181, 230, 29));

	}

	void CEraser::OnMove()
	{
		const int STEP_SIZE = 5;
		animation.OnMove();
		if (isMovingLeft)
			x -= STEP_SIZE;
		if (isMovingRight)
			x += STEP_SIZE;
		if (isMovingUp)
			y -= STEP_SIZE;
		if (isMovingDown)
			y += STEP_SIZE;
	}

	void CEraser::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CEraser::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CEraser::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CEraser::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void CEraser::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}
	void CEraser::SetAttack(bool flag)
	{
		isAttack = flag;
	}
	void CEraser::SetFaceLeft(bool flag)
	{
		isFacingLeft = flag;
	}
	void CEraser::SetFaceRight(bool flag)
	{
		isFacingRight = flag;
	}
	void CEraser::SetWeapon(bool flag)
	{
		isSwichingWeapon = flag;
		
	}

	void CEraser::OnShow()
	{
		


		if (isMovingRight) {

			if (isAttack) {
				Attack.SetTopLeft(x, y);
				Attack.deleteBMP();
				Attack.AddBitmap(IDB_Cartman_stick2, RGB(181, 230, 29));
				Attack.OnShow();
			}
			else {
				gotRight.SetTopLeft(x, y);
				gotRight.AddBitmap(IDB_Cartman_stick1, RGB(181, 230, 29));
				gotRight.OnShow();
			}
			animation.deleteBMP();
			animation.AddBitmap(IDB_Cartman_stick1, RGB(181, 230, 29));
		}
		else if (isMovingLeft) {
			if (isAttack) {
				Attack.SetTopLeft(x, y);
				Attack.deleteBMP();
				Attack.AddBitmap(IDB_Cartman_stick2_L, RGB(181, 230, 29));
				Attack.OnShow();
			}
			else {
				gotLeft.SetTopLeft(x, y);
				gotLeft.OnShow();
			}

			animation.deleteBMP();
			animation.AddBitmap(IDB_Cartman_stick1_L, RGB(181, 230, 29));
		}
		else {
			if (isAttack && isFacingLeft) {
				Attack.SetTopLeft(x, y);
				Attack.deleteBMP();
				Attack.AddBitmap(IDB_Cartman_stick2_L, RGB(181, 230, 29));
				Attack.OnShow();
			}
			else if (isAttack && isFacingRight) {
				Attack.SetTopLeft(x, y);
				Attack.deleteBMP();
				Attack.AddBitmap(IDB_Cartman_stick2, RGB(181, 230, 29));
				Attack.OnShow();
			}
			else {
				animation.SetTopLeft(x, y);
				animation.OnShow();
			}

		}

	}

}