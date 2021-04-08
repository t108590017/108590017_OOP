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
		bool collision(int mX, int mY);											// �˴���Ӫ���O�_�I��
		bool IsHit(int mX, int mY, bool Direction, bool isSpecialAction);		// �˴��D���O�_����}��
		static int SetOffset(int x, int offset);								// �]�w���⼽�ʵe��������
		int GetBlood();															// �^�Ǩ����q
		void ShowProgress(int percent, int X);									// �������i��

	protected:
		CAnimation AnimationCurrent;// ��e�ʵe

		bool DirectionX;			// �k��true����false
		bool DirectionY;			// �W��true�U��false
		bool isMoving;				// ���b����
		bool isCollision;			// �O�_��}�ⱵĲ
		bool isHit;					// �D���O�_���b�X��
		bool BarIsShow;				// ������b���
		bool AnimationReset_State;					// �Ω󭫳]AnimationCurrent����Ϥ�����
		int  x, y;					// ����b�a�ϤW��x,y �y��
		int OffsetX, OffsetY;
		int Blood;					// �}���q
		int BloodX;					// �����m
		int BloodTime;				// �Ψӭp�ɦ������ɶ�
		int Time;					// �p�ɾ�
	};
}