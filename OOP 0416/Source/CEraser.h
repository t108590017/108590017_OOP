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
		void Initialize();				// 設定擦子為初始值
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

		bool isAttacking();
		bool GetDirection();
		bool isJump(bool jump);
		bool hitGoal1(GameMap* m);
		void SetXY(int nx, int ny);		// 設定擦子左上角座標

	protected:
		CAnimation animation;		// 擦子的動畫
		CAnimation gotRight;		// 往右的動畫
		CAnimation gotLeft;		    // 往左的動畫
		CAnimation Attack;		    // 往左的動畫
		bool Direction;				// 是否在右   右為true左為false
		int x, y;					// 擦子左上角座標
		bool isMovingDown;			// 是否正在往下移動
		bool isJumping =false;
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		bool isAttack;			    // 是否正在攻擊
		bool isFacingLeft;			// 是否面相左邊
		bool isFacingRight;			// 是否面相右邊
		bool isStick;				// 是否是棍子
		bool isRifle;				// 是否是槍
		bool isFire;				// 是否是噴火
		bool isRocket;				// 是否是火箭
		bool isVchip;				// 是否是電
		bool isGoal;				// 是否是到目標
		bool is_Alive;				// 是否是到目標




	};

}