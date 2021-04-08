
namespace game_framework {
	class GameMap{
	public:
		GameMap();
		void LoadBitmap();
		void OnShow();
		void OnMove();
		int	 ScreenX(int x);
		int  ScreenY(int y);
		bool IsEmpty(int x ,int y);
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		//~GameMap();
	protected:
		CMovingBitmap yellow, green,blue;
		CMovingBitmap BackGround_0;
		static const int row = 15, col = 25;
		int map[row][col];
		const int MW, MH;
		int	 sx, sy;
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool KeepDraw;
	};
}