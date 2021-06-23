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
	bool Re = false;

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
		if (m->getLevel() == 6 ) {
			y = 1920 - 18 * 64;

		}
		else if (isRestart()) {
			setRestart(false);
			y = 0;
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
	int CEraser ::getAttackType() {
		return canAttack;
	}
	void CEraser::setAttackType(int n) {
			canAttack = n;
		
	}

	void CEraser::OnMove(GameMap* m)
	{
		counter--;
		if (counter < 0) {
			hurtCount = 0;
		}
		const int STEP_SIZE = 20;
		animation.OnMove();
		if (isMovingLeft) {
			if ((m->IsEmpty(x - STEP_SIZE, y)) == 1 || (m->IsEmpty(x - STEP_SIZE, y)) == 4 || (m->IsEmpty(x - STEP_SIZE, y)) == 5 || (m->IsEmpty(x - STEP_SIZE, y)) == 14 || (m->IsEmpty(x - STEP_SIZE, y)) == 30)
				x -= STEP_SIZE;
		}
		if (isMovingRight) {
			if ((m->IsEmpty(x + STEP_SIZE + 50, y)) == 1 || (m->IsEmpty(x + STEP_SIZE + 50, y)) == 4 || (m->IsEmpty(x + STEP_SIZE + 50, y)) == 5 || (m->IsEmpty(x + STEP_SIZE + 50, y)) == 14 || (m->IsEmpty(x + STEP_SIZE + 50, y)) == 30)
				x += STEP_SIZE;
		}

		if ((((m->IsEmpty(x, y + STEP_SIZE + 54)) == 1) || ((m->IsEmpty(x, y + STEP_SIZE + 54)) == 5) || jumpTime == -192)) {
			y += 32;
			if (((m->IsEmpty(x, y + STEP_SIZE + 54)) == 13) || ((m->IsEmpty(x, y + STEP_SIZE + 54)) == 14) || ((m->IsEmpty(x, y + STEP_SIZE + 54)) == 30)) {
				is_Alive = false;
			}
		}
		else {
		jumpTime = 0;
		}
		if (isJumping) {
			if ((m->IsEmpty(x, y - STEP_SIZE ) == 1|| m->IsEmpty(x, y - STEP_SIZE) == 5 || (m->IsEmpty(x, y - STEP_SIZE) == 4) || (m->IsEmpty(x, y - STEP_SIZE) == 14) || (m->IsEmpty(x, y - STEP_SIZE) == 30))) {
				jumpTime -= STEP_SIZE;
				y -= 64;
			}
			if (jumpTime < -192)
				isJumping = false;
		}
		if (isFly) {
			if ((m->IsEmpty(x, y - STEP_SIZE) == 1 || m->IsEmpty(x, y - STEP_SIZE) == 5 || (m->IsEmpty(x, y - STEP_SIZE) == 4) || (m->IsEmpty(x, y - STEP_SIZE) == 14) || (m->IsEmpty(x, y - STEP_SIZE) == 30))) {
				jumpTime -= STEP_SIZE;
				y -= 64;
			}
		}




		if (m->ScreenX(x) > 300 && isMovingRight) {  //角色走過畫面x超過300
			m->SetMovingRight(true);				 //畫面開始向右
		}
		else {
			m->SetMovingRight(false);
		}

		if (m->ScreenX(x) < 200 && isMovingLeft) {   //角色走過畫面x小於100  
			m->SetMovingLeft(true);					 //畫面開始向左
		}
		else {
			m->SetMovingLeft(false);
		}

		if (m->ScreenY(y) > 250) {   //角色走過畫面y超過300
			m->SetMovingDown(true);					 //畫面開始向下
		}
		else {
			m->SetMovingDown(false);
		}

		if (m->ScreenY(y) < 200) {		 //角色走過畫面y小於100
			m->SetMovingUp(true);					 //畫面開始向上
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
		Life += add;
		if (Life > 99) {
			Life = 99;
		}
	}
	void CEraser::restart() {
		energy = 5;
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
	bool CEraser::isRestart() {
		return Re ;
	}
	void CEraser::setRestart(bool n) {
		Re=n;
	}
	bool CEraser::isAlive() {
		return is_Alive;
	}
	int CEraser::isFacing() {
		if (isFacingRight)
			return 0; //面對右邊
		else
			return 1; //面對左邊
	}
	void CEraser::setG(bool flag) {
		G = true;
	}
	void CEraser::setO(bool flag) {
		O = true;
	}
	void CEraser::setD(bool flag) {
		D = true;
	}
	bool CEraser::getG() {
		return G;
	}
	bool CEraser::getO() {
		return O;
	}
	bool CEraser::getD() {
		return D;
	}
	void CEraser::setF(bool flag) {
		F = true;
	}
	void CEraser::setL(bool flag) {
		L = true;
	}
	void CEraser::setY(bool flag) {
		Y = true;
	}
	bool CEraser::getF() {
		return F;
	}
	bool CEraser::getL() {
		return L;
	}
	bool CEraser::getY() {
		return Y;
	}
	void CEraser::setFLY(bool flag) {
		isFly=flag;
	}
	void CEraser::setHurt(int H) {
		if (counter<0 &&hurtCount==0) {
			energy += H;
			counter = 30;

		}
	}
	void CEraser::setEnergy(int n) {
		energy = n;
	}
	void CEraser::setHurtCount() {
		hurtCount = 1;
	}
	int CEraser::getEnergy() {
		return energy;
	}
	void CEraser::OnShow(GameMap *m){


		if (isStick) {
			if (isMovingRight|| isFacingRight) {
				if ((isAttack) && (getAttackType() == 0)) {
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
				if ((isAttack) && (getAttackType() == 0)) {
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
				if ((isAttack) && (getAttackType() == 0)) {
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
				if ((isAttack) && (getAttackType() == 0)) {
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
				if ((isAttack) && (getAttackType() == 0)) {
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
				if ((isAttack) && (getAttackType() == 0)) {
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
				if ((isAttack) && (getAttackType() == 0)) {
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
				if ((isAttack) && (getAttackType() == 0)) {
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