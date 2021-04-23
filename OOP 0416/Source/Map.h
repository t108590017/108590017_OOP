
namespace game_framework {
	class GameMap {
	public:
		GameMap();
		void LoadBitmap();
		void OnShow();
		void OnMove();
		bool IsEmpty(int x, int y);
		int ScreenX(int x);
		int ScreenY(int y);
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		//~GameMap();
	protected:
		CMovingBitmap yellow, green, blue, block, block2;
		int map[15][20];
		const int MW, MH;
		int X, Y;
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
	};
}