#ifndef ENEMY_H
#define ENEMY_H
#include "CEraser.h"
namespace game_framework {
	class GameMap;
	class Player;
	class CEraser;
	class Enemy :public CEraser {

	public:
		Enemy();
		virtual void LoadBitmap();
		virtual void OnShow(GameMap* m);
		virtual void OnMove(GameMap* m, Player* role);
		virtual  void Initialize();
		bool HitEraser(CEraser* eraser);						// 是否碰到擦子
		void SetIsAlive(bool alive);							// 設定是否活著
		bool IsAlive();											// 是否活著

	protected:

		CAnimation bmp;
		int x, y;					// 圓心的座標
		int dx, dy;					// 球距離圓心的位移量
		int index;					// 球的「角度」，0-17表示0-360度
		double delay_counter;			// 調整旋轉速度的計數器
		double delay;					// 旋轉的速度
		bool is_alive;				// 是否活著
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
	};
}
#endif