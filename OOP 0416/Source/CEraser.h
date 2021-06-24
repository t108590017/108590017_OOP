#include "Map.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////


	class CEraser
	{
	public:
		CEraser();
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		void Initialize(GameMap* m);				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove(GameMap* m);					// 移動擦子
		void OnShow(GameMap* m);					// 將擦子圖形貼到畫面
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetAttack(bool flag);	    // 設定是否攻擊
		void SetFaceLeft(bool flag);	// 設定是否面相左邊
		void SetFaceRight(bool flag);	// 設定是否面相右邊
		void SetWeaponA(bool flag);	// 設定是否換棍子
		void SetWeaponS(bool flag);		// 設定是否換噴火
		void SetWeaponD(bool flag);	// 設定是否換火箭
		void SetWeaponF (bool flag);	// 設定是否換槍
		void SetAlive(bool alive);	// 設定是否死
		bool isAlive();				// 判斷是否死
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
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
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
		GameMap		gameMap;	//地圖
		CAnimation animation;		// 擦子的動畫
		CAnimation gotRight;		// 往右的動畫
		CAnimation gotLeft;		    // 往左的動畫
		CAnimation Attack;		    // 往左的動畫
		bool Direction;				// 是否在右   右為true左為false
		int x, y;					// 擦子左上角座標
		int canAttack = 0;
		bool isMovingDown;			// 是否正在往下移動
		bool isJumping =false;
		bool isMovingLeft = false;;			// 是否正在往左移動
		bool isMovingRight = true;			// 是否正在往右移動
		bool isMovingUp = false;;			// 是否正在往上移動
		bool isAttack = false;;			    // 是否正在攻擊
		bool isFacingLeft=false;			// 是否面相左邊
		bool isFacingRight=true;			// 是否面相右邊
		bool isStick = true;				// 是否是棍子
		bool isRifle = false;;				// 是否是槍
		bool isFire = false;;				// 是否是噴火
		bool isRocket = false;;				// 是否是火箭
		bool isVchip = false;;				// 是否是電
		bool isGoal = false;;				// 是否是到目標
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
		int counter=30*1;	// 倒數之計數器
		int hurtCount = 0;




	};

}