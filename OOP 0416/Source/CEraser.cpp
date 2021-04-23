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
		const int X_POS = 0;
		const int Y_POS = 0;
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

	void CEraser::OnMove(GameMap* m)
	{
		const int STEP_SIZE = 10;
		animation.OnMove();
		if (isMovingLeft) {
			if (m->IsEmpty(x - STEP_SIZE, y))
				x -= STEP_SIZE;
		}
		if (isMovingRight) {
			if (m->IsEmpty(x + STEP_SIZE+50, y))
				x += STEP_SIZE;
		}
		if (m->IsEmpty(x , y+ STEP_SIZE+58))
			y +=  30;
		if (isJumping) {
			int a = 0;
			if (m->IsEmpty(x, y - STEP_SIZE-58)) {
				a -= STEP_SIZE;
				y -= 40;
			}
			if (a == -30)
				isJumping = false;
		}


		if (m->ScreenX(x) > 300 && isMovingRight) {  //角色走過畫面x超過480 
			m->SetMovingRight(true);				 //畫面開始向右
		}
		else {
			m->SetMovingRight(false);
		}

		if (m->ScreenX(x) < 100 && isMovingLeft) {   //角色走過畫面x小於100  
			m->SetMovingLeft(true);					 //畫面開始向左
		}
		else {
			m->SetMovingLeft(false);
		}

		if (m->ScreenY(y) > 300 && isMovingDown) {   //角色走過畫面y超過300
			m->SetMovingDown(true);					 //畫面開始向下
		}
		else {
			m->SetMovingDown(false);
		}

		if (m->ScreenY(y) < 100 && isMovingUp) {		 //角色走過畫面y小於100
			m->SetMovingUp(true);					 //畫面開始向上
		}
		else {
			m->SetMovingUp(false);
		}
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
	bool CEraser::isJump(bool jump) {
		isJumping = jump;
		return jump;
	}

	void CEraser::OnShow(GameMap *m){

		if (isStick) {
			if (isMovingRight|| isFacingRight) {
				if (isAttack) {
					Attack.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
					Attack.deleteBMP();
					Attack.AddBitmap(IDB_Cartman_stick2, RGB(181, 230, 29));
					Attack.OnShow();
				}
				else {
					gotRight.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
					gotRight.deleteBMP();
					gotRight.AddBitmap(IDB_Cartman_stick1, RGB(181, 230, 29));
					gotRight.OnShow();
				}

			}
			else if (isMovingLeft || isFacingLeft) {
				if (isAttack) {
					Attack.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
					Attack.deleteBMP();
					Attack.AddBitmap(IDB_Cartman_stick2_L, RGB(181, 230, 29));
					Attack.OnShow();
				}
				else {
					gotLeft.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
					gotLeft.OnShow();
				}

			}

		}
		else if (isRifle) {
			if (isMovingRight || isFacingRight) {
				if (isAttack) {
					Attack.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
					Attack.deleteBMP();
					Attack.AddBitmap(IDB_cartman_rifle, RGB(181, 230, 29));
					Attack.OnShow();
				}
				else {
					gotRight.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
					gotRight.deleteBMP();
					gotRight.AddBitmap(IDB_cartman_rifle, RGB(181, 230, 29));
					gotRight.OnShow();
				}
				animation.deleteBMP();
				animation.AddBitmap(IDB_cartman_rifle, RGB(181, 230, 29));
			}
			else if (isMovingLeft || isFacingLeft) {
				if (isAttack) {
					Attack.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
					Attack.deleteBMP();
					Attack.AddBitmap(IDB_cartman_rifle_L, RGB(181, 230, 29));
					Attack.OnShow();
				}
				else {
					gotRight.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
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
					Attack.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
					Attack.deleteBMP();
					Attack.AddBitmap(IDB_Cartman_fire, RGB(181, 230, 29));
					Attack.OnShow();
				}
				else {
					gotRight.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
					gotRight.deleteBMP();
					gotRight.AddBitmap(IDB_Cartman_fire, RGB(181, 230, 29));
					gotRight.OnShow();
				}
				animation.deleteBMP();
				animation.AddBitmap(IDB_Cartman_fire, RGB(181, 230, 29));
			}
			else if (isMovingLeft || isFacingLeft) {
				if (isAttack) {
					Attack.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
					Attack.deleteBMP();
					Attack.AddBitmap(IDB_Cartman_fire_L, RGB(181, 230, 29));
					Attack.OnShow();
				}
				else {
					gotRight.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
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
					Attack.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
					Attack.deleteBMP();
					Attack.AddBitmap(IDB_cartman_rocket, RGB(181, 230, 29));
					Attack.OnShow();
				}
				else {
					gotRight.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
					gotRight.deleteBMP();
					gotRight.AddBitmap(IDB_cartman_rocket, RGB(181, 230, 29));
					gotRight.OnShow();
				}
				animation.deleteBMP();
				animation.AddBitmap(IDB_cartman_rocket, RGB(181, 230, 29));
			}
			else if (isMovingLeft || isFacingLeft) {
				if (isAttack) {
					Attack.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
					Attack.deleteBMP();
					Attack.AddBitmap(IDB_cartman_rocket_L, RGB(181, 230, 29));
					Attack.OnShow();
				}
				else {
					gotRight.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
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