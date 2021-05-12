#include "Map.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class CEraser
	{
	public:
		CEraser();
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		void Initialize();				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove(GameMap* m);					// �������l
		void OnShow(GameMap* m);					// �N���l�ϧζK��e��
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetAttack(bool flag);	    // �]�w�O�_����
		void SetFaceLeft(bool flag);	// �]�w�O�_���ۥ���
		void SetFaceRight(bool flag);	// �]�w�O�_���ۥk��
		void SetWeaponA(bool flag);	// �]�w�O�_���Ҥl
		void SetWeaponS(bool flag);		// �]�w�O�_���Q��
		void SetWeaponD(bool flag);	// �]�w�O�_�����b
		void SetWeaponF (bool flag);	// �]�w�O�_���j
		void SetAlive(bool alive);	// �]�w�O�_��
		bool isAlive();				// �P�_�O�_��

		bool isAttacking();
		bool GetDirection();
		bool isJump(bool jump);
		bool hitGoal1(GameMap* m);
		void SetXY(int nx, int ny);		// �]�w���l���W���y��

	protected:
		CAnimation animation;		// ���l���ʵe
		CAnimation gotRight;		// ���k���ʵe
		CAnimation gotLeft;		    // �������ʵe
		CAnimation Attack;		    // �������ʵe
		bool Direction;				// �O�_�b�k   �k��true����false
		int x, y;					// ���l���W���y��
		bool isMovingDown;			// �O�_���b���U����
		bool isJumping =false;
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool isAttack;			    // �O�_���b����
		bool isFacingLeft;			// �O�_���ۥ���
		bool isFacingRight;			// �O�_���ۥk��
		bool isStick;				// �O�_�O�Ҥl
		bool isRifle;				// �O�_�O�j
		bool isFire;				// �O�_�O�Q��
		bool isRocket;				// �O�_�O���b
		bool isVchip;				// �O�_�O�q
		bool isGoal;				// �O�_�O��ؼ�
		bool is_Alive;				// �O�_�O��ؼ�




	};

}