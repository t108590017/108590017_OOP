#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"
#include "Coin.h"
#include "Shoot.h"
#include "Health.h"
#include "BOSS.h"
#include "Ammo.h"
#include "jumpBall.h"



namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT,				// 2
		AUDIO_MENU,				// 3 Menu����
		AUDIO_INTRO,
		AUDIO_END,
		AUDIO_EAT,
		AUDIO_HURT,
		AUDIO_GUN,
		AUDIO_HIT

	};


	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame* g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void OnKeyDown(UINT, UINT, UINT);				// �B�z��LDown���ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
	protected:
		int x, y;										//Choose���y��
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap logo;								// csie��logo
		CMovingBitmap menu;								// csie��logo
		CMovingBitmap Choose;							// csie��logo
		CAnimation		finish;
		GameMap		gameMap;
		CEraser eraser;
		CShoot  Shoot;
		CCoin   Coin;



	};
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame* g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		const int		NUMBALLS;	// �y���`��
		const int		NUMSHOOT;
		int energy;
		GameMap		gameMap;	//�a��
		CMovingBitmap	background;	// �I����
		CMovingBitmap	help;		// ������
		CBall* ball;		// �y���}�C
		CCoin* coin;
		CHealth* health;
		CShoot *Shoot;
		CAmmo* Ammo;
		CBOSS* BOSS;
		CJBALL* Jball;
		CMovingBitmap	corner;		// ������
		CBall	enemy1;		// �ĤH��
		CAnimation		energyBar,Lives_P,coin_P,Gun_P;

		CEraser			eraser;		// ��l
		CInteger		hits_left,Lives;	// �ѤU��������

		CBouncingBall   bball;		// ���мu�����y
		int enemyHealth1 = 0;
		int enemyHealth2 = 0;
		int enemyHealth3 = 0;
		int enemyHealth4 = 0;
		int hits = 0;
		int numberShoot = 0;
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame* g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	// �˼Ƥ��p�ƾ�
		CAnimation		finish;


	};

	/////////////////////////////////////////////////////////////////////////////
// �o��class���C���ĤG������
// �C��Member function��Implementation���n����
/////////////////////////////////////////////////////////////////////////////

	class CGameState2 : public CGameState {
	public:
		CGameState2(CGame* g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	// �˼Ƥ��p�ƾ�
		GameMap		gameMap;
		CAnimation		finish;


	};
	/////////////////////////////////////////////////////////////////////////////
// �o��class���C���ĤG������
// �C��Member function��Implementation���n����
/////////////////////////////////////////////////////////////////////////////

	class CGameStateDead : public CGameState {
	public:
		CGameStateDead(CGame* g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	// �˼Ƥ��p�ƾ�
		CEraser			eraser;		// ��l
		GameMap		gameMap;
		CAnimation		finish;


	};

/////////////////////////////////////////////////////////////////////////////
// �o��class���C���ĤG������
// �C��Member function��Implementation���n����
/////////////////////////////////////////////////////////////////////////////

	class CGameStateAbout: public CGameState {
	public:
		CGameStateAbout(CGame* g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
		void OnKeyUp(UINT, UINT, UINT);				// �B�z��LDown���ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��

	private:
		int counter;	// �˼Ƥ��p�ƾ�
		CEraser			eraser;		// ��l
		GameMap		gameMap;
		CAnimation		About;


	};
	/////////////////////////////////////////////////////////////////////////////
// �o��class���C���ĤG������
// �C��Member function��Implementation���n����
/////////////////////////////////////////////////////////////////////////////

	class CGameStateConfiguration : public CGameState {
	public:
		CGameStateConfiguration(CGame* g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
		void OnKeyUp(UINT, UINT, UINT);				// �B�z��LDown���ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��

	private:
		int counter;	// �˼Ƥ��p�ƾ�
		CEraser			eraser;		// ��l
		GameMap		gameMap;
		CAnimation		Configuration;


	};
	
}