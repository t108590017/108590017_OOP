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
		bool HitEraser(CEraser* eraser);						// �O�_�I�����l
		void SetIsAlive(bool alive);							// �]�w�O�_����
		bool IsAlive();											// �O�_����

	protected:

		CAnimation bmp;
		int x, y;					// ��ߪ��y��
		int dx, dy;					// �y�Z����ߪ��첾�q
		int index;					// �y���u���סv�A0-17���0-360��
		double delay_counter;			// �վ����t�ת��p�ƾ�
		double delay;					// ���઺�t��
		bool is_alive;				// �O�_����
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}
#endif