namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class CHealth
	{
	public:
		CHealth();
		bool HitEraser(CEraser* eraser);						// �O�_�I�����l
		bool IsAlive();											// �O�_����
		void LoadBitmap();										// ���J�ϧ�
		void OnMove();											// ����
		void OnShow(GameMap* m);											// �N�ϧζK��e��
		void SetXY(int nx, int ny);								// �]�w��ߪ��y��
		void SetIsAlive(bool alive);							// �]�w�O�_����
		void SetDelay(double d);									// �]�w���઺�t��
	protected:
		//CMovingBitmap bmp_center,bmp_center2;	// ��ߪ���			
		CAnimation bmp;
		int x, y;					// ��ߪ��y��
		int dx, dy;					// �y�Z����ߪ��첾�q
		int index;					// �y���u���סv�A0-17����0-360��
		double delay_counter;			// �վ����t�ת��p�ƾ�
		double delay;					// ���઺�t��
		bool is_alive;				// �O�_����
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}