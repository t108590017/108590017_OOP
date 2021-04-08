namespace game_framework {
	class GameMap;
	class CEraser;
	class Enemy {

	public:
		Enemy();
		Enemy(int InputX, int InputY);
		void LoadBitmap();
		void OnShow(GameMap* m);
		void OnMove(GameMap* m, CEraser* role);
		void Initialize(int InputX, int InputY);
		void SetDirection(bool flag);
		bool collision(int mX, int mY);											// 檢測兩個物體是否碰撞
		bool IsHit(int mX, int mY, bool Direction, bool isSpecialAction);		// 檢測主角是否打到腳色
		static int SetOffset(int x, int offset);								// 設定角色播動畫的偏移植
		int GetBlood();															// 回傳角色血量
		void ShowProgress(int percent, int X);									// 播放血條進度

	protected:
		CAnimation AnimationCurrent;// 當前動畫

		bool DirectionX;			// 右為true左為false
		bool DirectionY;			// 上為true下為false
		bool isMoving;				// 正在移動
		bool isCollision;			// 是否跟腳色接觸
		bool isHit;					// 主角是否正在出拳
		bool BarIsShow;				// 血條正在顯示
		bool AnimationReset_State;					// 用於重設AnimationCurrent播放圖片順序
		int  x, y;					// 角色在地圖上的x,y 座標
		int OffsetX, OffsetY;
		int Blood;					// 腳色血量
		int BloodX;					// 血條位置
		int BloodTime;				// 用來計時血條持續時間
		int Time;					// 計時器
	};
}