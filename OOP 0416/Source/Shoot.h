namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////
	class CBOSS;
	class CJBALL;

	class CShoot
	{
	public:
		CShoot();
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		bool IsAlive();											// �O�_����
		void LoadBitmap();										// ���J�ϧ�
		bool hitBOSS(CBOSS *BOSS);
		bool hitJBall(CJBALL* JBALL);

		void OnMove();											// ����
		void OnShow(GameMap *m);											// �N�ϧζK��e��
		void SetXY(int nx, int ny);								// �]�w��ߪ��y��
		void SetIsAlive(bool alive);							// �]�w�O�_����
		void SetDelay(double d);									// �]�w���઺�t��
		void setFacingLeft(bool F);
		void setFacingRight(bool F);
		bool hitBall(CBall *ball);

		int	 getLeft();
		void setLeft(int n);
	protected:
		CEraser eraser;
		CAnimation bmp, bmp_center, bmp_center2, bmp_center3;
		int x, y;					// ��ߪ��y��
		int dx, dy;					// �y�Z����ߪ��첾�q
		int index=0;					// �y���u���סv�A0-17���0-360��
		double delay_counter;			// �վ����t�ת��p�ƾ�
		double delay;					// ���઺�t��
		bool FacingLeft = false;
		bool FacingRight = true;
		bool is_alive;				// �O�_����
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2  );	// �O�_�I��Ѽƽd�򪺯x��
	};
}