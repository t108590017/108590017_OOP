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
		void Initialize(GameMap* m);				// �]�w���l����l��
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
		bool isitRifle();
		bool isitStick();

		bool getFacingLeft();
		bool getFacingRight();

		int  getLife();
		void restart();
		int  isFacing();
		void lifeLeft(int add);
		int  getAttackType();
		void setAttackType(int n);
		bool isAttacking();
		bool GetDirection();
		bool isJump(bool jump);
		bool hitGoal1(GameMap* m);
		bool isRestart();
		void setRestart(bool n);
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
		bool reLevel(GameMap* m);
		void setG(bool flag);
		void setO(bool flag);
		void setD(bool flag);
		bool getG();
		bool getO();
		bool getD();
		void setF(bool flag);
		void setL(bool flag);
		void setY(bool flag);
		bool getF();
		bool getL();
		bool getY();
		void setFLY(bool flag);
		void setHurt(int H);
		int  getEnergy();
		void setHurtCount();
		void setEnergy(int n);
		


	protected:
		GameMap		gameMap;	//�a��
		CAnimation animation;		// ���l���ʵe
		CAnimation gotRight;		// ���k���ʵe
		CAnimation gotLeft;		    // �������ʵe
		CAnimation Attack;		    // �������ʵe
		bool Direction;				// �O�_�b�k   �k��true����false
		int x, y;					// ���l���W���y��
		int canAttack = 0;
		bool isMovingDown;			// �O�_���b���U����
		bool isJumping =false;
		bool isMovingLeft = false;;			// �O�_���b��������
		bool isMovingRight = true;			// �O�_���b���k����
		bool isMovingUp = false;;			// �O�_���b���W����
		bool isAttack = false;;			    // �O�_���b����
		bool isFacingLeft=false;			// �O�_���ۥ���
		bool isFacingRight=true;			// �O�_���ۥk��
		bool isStick = true;				// �O�_�O�Ҥl
		bool isRifle = false;;				// �O�_�O�j
		bool isFire = false;;				// �O�_�O�Q��
		bool isRocket = false;;				// �O�_�O���b
		bool isVchip = false;;				// �O�_�O�q
		bool isGoal = false;;				// �O�_�O��ؼ�
		bool is_Alive;				
		float attacktime = 15;
		int jumpTime = 0;
		bool G = false;
		bool O = false;
		bool D = false;
		bool isFly = false;
		bool F = false;
		bool L = false;
		bool Y = false;

		int  energy = 5;
		int counter=30*1;	// �˼Ƥ��p�ƾ�
		int hurtCount = 0;




	};

}