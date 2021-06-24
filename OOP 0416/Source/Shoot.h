namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	class CBOSS;
	class CJBALL;

	class CShoot
	{
	public:
		CShoot();
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		bool IsAlive();											// 是否活著
		void LoadBitmap();										// 載入圖形
		bool hitBOSS(CBOSS *BOSS);
		bool hitJBall(CJBALL* JBALL);

		void OnMove();											// 移動
		void OnShow(GameMap *m);											// 將圖形貼到畫面
		void SetXY(int nx, int ny);								// 設定圓心的座標
		void SetIsAlive(bool alive);							// 設定是否活著
		void SetDelay(double d);									// 設定旋轉的速度
		void setFacingLeft(bool F);
		void setFacingRight(bool F);
		bool hitBall(CBall *ball);

		int	 getLeft();
		void setLeft(int n);
	protected:
		CEraser eraser;
		CAnimation bmp, bmp_center, bmp_center2, bmp_center3;
		int x, y;					// 圓心的座標
		int dx, dy;					// 球距離圓心的位移量
		int index=0;					// 球的「角度」，0-17表示0-360度
		double delay_counter;			// 調整旋轉速度的計數器
		double delay;					// 旋轉的速度
		bool FacingLeft = false;
		bool FacingRight = true;
		bool is_alive;				// 是否活著
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2  );	// 是否碰到參數範圍的矩形
	};
}