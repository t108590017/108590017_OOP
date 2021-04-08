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
		return x + Attack.Width();
	}

	int CEraser::GetY2()
	{
		return y + Attack.Height();
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
	void CEraser::SetWeaponA(bool flag){
		isStick = true;
		isRifle = false;				
		isFire = false;		
		isRocket = false;

	}

	void CEraser::SetWeaponS(bool flag)
	{
		isStick = false;
		isRifle = true;
		isFire = false;
		isRocket = false;
	}
	void CEraser::SetWeaponD(bool flag)
	{
		isStick = false;
		isRifle = false;
		isFire = true;
		isRocket = false;
	}	
	void CEraser::SetWeaponF(bool flag)
	{
		isStick = false;
		isRifle = false;
		isFire = false;
		isRocket = true;
	}	
	bool CEraser::isAttacking() {
		return isAttack;
	}

	void CEraser::OnShow(){
		if (isStick) {
			if (isMovingRight|| isFacingRight) {
				if (isAttack) {
					Attack.SetTopLeft(x, y);
					Attack.deleteBMP();
					Attack.AddBitmap(IDB_Cartman_stick2, RGB(181, 230, 29));
					Attack.OnShow();
				}
				else {
					gotRight.SetTopLeft(x, y);
					gotRight.deleteBMP();
					gotRight.AddBitmap(IDB_Cartman_stick1, RGB(181, 230, 29));
					gotRight.OnShow();
				}

			}
			else if (isMovingLeft || isFacingLeft) {
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

			}

		}
		else if (isRifle) {
			if (isMovingRight || isFacingRight) {
				if (isAttack) {
					Attack.SetTopLeft(x, y);
					Attack.deleteBMP();
					Attack.AddBitmap(IDB_cartman_rifle, RGB(181, 230, 29));
					Attack.OnShow();
				}
				else {
					gotRight.SetTopLeft(x, y);
					gotRight.deleteBMP();
					gotRight.AddBitmap(IDB_cartman_rifle, RGB(181, 230, 29));
					gotRight.OnShow();
				}
				animation.deleteBMP();
				animation.AddBitmap(IDB_cartman_rifle, RGB(181, 230, 29));
			}
			else if (isMovingLeft || isFacingLeft) {
				if (isAttack) {
					Attack.SetTopLeft(x, y);
					Attack.deleteBMP();
					Attack.AddBitmap(IDB_cartman_rifle_L, RGB(181, 230, 29));
					Attack.OnShow();
				}
				else {
					gotRight.SetTopLeft(x, y);
					gotRight.deleteBMP();
					gotRight.AddBitmap(IDB_cartman_rifle_L, RGB(181, 230, 29));
					gotRight.OnShow();
				}

				animation.deleteBMP();
				animation.AddBitmap(IDB_cartman_rifle_L, RGB(181, 230, 29));
			}
		}
		else if (isFire) {
			if (isMovingRight||isFacingRight) {
				if (isAttack) {
					Attack.SetTopLeft(x, y);
					Attack.deleteBMP();
					Attack.AddBitmap(IDB_Cartman_fire, RGB(181, 230, 29));
					Attack.OnShow();
				}
				else {
					gotRight.SetTopLeft(x, y);
					gotRight.deleteBMP();
					gotRight.AddBitmap(IDB_Cartman_fire, RGB(181, 230, 29));
					gotRight.OnShow();
				}
				animation.deleteBMP();
				animation.AddBitmap(IDB_Cartman_fire, RGB(181, 230, 29));
			}
			else if (isMovingLeft || isFacingLeft) {
				if (isAttack) {
					Attack.SetTopLeft(x, y);
					Attack.deleteBMP();
					Attack.AddBitmap(IDB_Cartman_fire_L, RGB(181, 230, 29));
					Attack.OnShow();
				}
				else {
					gotRight.SetTopLeft(x, y);
					gotRight.deleteBMP();
					gotRight.AddBitmap(IDB_Cartman_fire_L, RGB(181, 230, 29));
					gotRight.OnShow();
				}

				animation.deleteBMP();
				animation.AddBitmap(IDB_Cartman_fire_L, RGB(181, 230, 29));
			}
		}
		else if (isRocket) {
			if (isMovingRight || isFacingRight) {
				if (isAttack) {
					Attack.SetTopLeft(x, y);
					Attack.deleteBMP();
					Attack.AddBitmap(IDB_cartman_rocket, RGB(181, 230, 29));
					Attack.OnShow();
				}
				else {
					gotRight.SetTopLeft(x, y);
					gotRight.deleteBMP();
					gotRight.AddBitmap(IDB_cartman_rocket, RGB(181, 230, 29));
					gotRight.OnShow();
				}
				animation.deleteBMP();
				animation.AddBitmap(IDB_cartman_rocket, RGB(181, 230, 29));
			}
			else if (isMovingLeft || isFacingLeft) {
				if (isAttack) {
					Attack.SetTopLeft(x, y);
					Attack.deleteBMP();
					Attack.AddBitmap(IDB_cartman_rocket_L, RGB(181, 230, 29));
					Attack.OnShow();
				}
				else {
					gotRight.SetTopLeft(x, y);
					gotRight.deleteBMP();
					gotRight.AddBitmap(IDB_cartman_rocket_L, RGB(181, 230, 29));
					gotRight.OnShow();
				}

				animation.deleteBMP();
				animation.AddBitmap(IDB_cartman_rocket_L, RGB(181, 230, 29));
			}
		}
	}

}