
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
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		//~GameMap();
	protected:
		CMovingBitmap yellow, green, blue, block, block2,floor,floor_D,block6,circle,brickR,brickG,brickB,brick_BW,brick_BWG,Sting;
		int map[45][125];
		const int MW, MH;
		int X, Y;
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
	};
}