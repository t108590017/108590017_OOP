
namespace game_framework {
	class GameMap {
	public:
		GameMap();
		void LoadBitmap();
		void OnShow();
		void OnMove();
		int IsEmpty(int x, int y);
		int ScreenX(int x);
		int ScreenY(int y);
		int getLevel();
		void setLevel();
		void changeLevel();
		void SetMapXY(int nx,int ny);
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		//~GameMap();
	protected:
		CMovingBitmap yellow, green, blue, block, block2,floor,floor_D,block6,circle,brickR,brickG,brickB,brick_BW,brick_BWG,Sting;
		int map[45][125];
		const int MW, MH;
		int X, Y;
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
	};
}