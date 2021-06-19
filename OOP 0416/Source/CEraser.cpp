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
	int Life = 0;

	CEraser::CEraser()
	{
		Initialize(&gameMap);
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

	void CEraser::Initialize(GameMap* m)
	{
		const int X_POS = 64;
		const int Y_POS = 1920;
		if (m->getLevel() == 6) {
			y = 1920 - 18 * 64;
		}
		else {
			y = Y_POS;
		}
		x = X_POS;
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
		const int STEP_SIZE = 20;
		animation.OnMove();
		if (isMovingLeft) {
			if ((m->IsEmpty(x - STEP_SIZE, y))==1 || (m->IsEmpty(x - STEP_SIZE, y)) == 4 || (m->IsEmpty(x - STEP_SIZE, y)) == 5|| (m->IsEmpty(x - STEP_SIZE, y)) == 14|| (m->IsEmpty(x - STEP_SIZE, y)) == 30)
				x -= STEP_SIZE;
		}
		if (isMovingRight) {
			if ((m->IsEmpty(x + STEP_SIZE+50, y))==1 || (m->IsEmpty(x + STEP_SIZE + 50, y)) == 4 || (m->IsEmpty(x + STEP_SIZE + 50, y)) == 5 || (m->IsEmpty(x + STEP_SIZE + 50, y)) == 14 || (m->IsEmpty(x + STEP_SIZE + 50, y)) == 30)
				x += STEP_SIZE;
		}
		if (((m->IsEmpty(x, y + STEP_SIZE + 54)) == 1) || ((m->IsEmpty(x, y + STEP_SIZE + 54)) == 5) ) {
			y += 32;
			if (((m->IsEmpty(x, y + STEP_SIZE + 54)) == 13)|| ((m->IsEmpty(x, y + STEP_SIZE + 54)) == 14) || ((m->IsEmpty(x, y + STEP_SIZE + 54)) == 30)) {
				is_Alive = false;
			}
		}
		
		if (isJumping) {
			int a = 0;
			if (m->IsEmpty(x, y - STEP_SIZE ) == 1|| m->IsEmpty(x, y - STEP_SIZE) == 5 || m->IsEmpty(x, y - STEP_SIZE) == 4 || (m->IsEmpty(x, y - STEP_SIZE) == 14) || (m->IsEmpty(x, y - STEP_SIZE) == 30)) {
				a -= STEP_SIZE;
				y -= 64;
			}
			if (a == -30)
				isJumping = false;
		}



		if (m->ScreenX(x) > 300 && isMovingRight) {  //���⨫�L�e��x�W�L480 
			m->SetMovingRight(true);				 //�e���}�l�V�k
		}
		else {
			m->SetMovingRight(false);
		}

		if (m->ScreenX(x) < 100 && isMovingLeft) {   //���⨫�L�e��x�p��100  
			m->SetMovingLeft(true);					 //�e���}�l�V��
		}
		else {
			m->SetMovingLeft(false);
		}

		if (m->ScreenY(y) > 300) {   //���⨫�L�e��y�W�L300
			m->SetMovingDown(true);					 //�e���}�l�V�U
		}
		else {
			m->SetMovingDown(false);
		}

		if (m->ScreenY(y) < 100) {		 //���⨫�L�e��y�p��100
			m->SetMovingUp(true);					 //�e���}�l�V�W
		}
		else {
			m->SetMovingUp(false);
		}
	}




	bool CEraser::hitGoal1( GameMap* m) {
		if ((m->IsEmpty(x - 20, y)) == 5 || (m->IsEmpty(x + 20, y)) == 5) {
			return TRUE;
		}
		else
			return FALSE;
	}
	bool CEraser::reLevel(GameMap* m) {
		if ((m->IsEmpty(x - 20, y)) == 30 || (m->IsEmpty(x + 20, y)) == 30) {
			return TRUE;
		}
		else
			return FALSE;
	}
	void CEraser::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CEraser::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}
	
	int CEraser::getLife() {
		return Life;
	}
	void CEraser::lifeLeft(int add) {
		Life+=add;
	}
	void CEraser::restart() {
		Life=3;
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
	void CEraser::SetAlive(bool alive) {
		is_Alive = alive;
	}
	bool CEraser::isAlive() {
		return is_Alive ;
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