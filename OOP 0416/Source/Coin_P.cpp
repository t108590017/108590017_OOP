#include "stdafx.h"
#include "game.h"
#include "gamelib.h"
#include "MainFrm.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <direct.h>
#include <string.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {
	CMovingBitmap CCoins::digit[11];

	CCoins::CCoins(int digits)
		: NUMDIGITS(digits)
	{
		isBmpLoaded = false;
	}

	void CCoins::Add(int x)
	{
		n += x;
	}

	int CCoins::GetInteger()
	{
		return n;
	}

	void CCoins::LoadBitmap()
	{
		//
		// digit[i]��class varibale�A�ҥH�����קK����LoadBitmap
		//
		if (!isBmpLoaded) {
			int d[11] = { IDB_0,IDB_1,IDB_2,IDB_3,IDB_4,IDB_5,IDB_6,IDB_7,IDB_8,IDB_9,IDB_MINUS };
			for (int i = 0; i < 11; i++)
				digit[i].LoadBitmap(d[i], RGB(0, 0, 0));
			isBmpLoaded = true;
		}
	}

	void CCoins::SetInteger(int i)
	{
		n = i;
	}

	void CCoins::SetTopLeft(int nx, int ny)		// �N�ʵe�����W���y�в��� (x,y)
	{
		x = nx; y = ny;
	}

	void CCoins::ShowBitmap()
	{
		GAME_ASSERT(isBmpLoaded, "CInteger: �Х�����LoadBitmap�A�M��~��ShowBitmap");
		int nx;		// ����ܦ�ƪ� x �y��
		int MSB;	// �̥���(�t�Ÿ�)����ƪ��ƭ�
		if (n >= 0) {
			MSB = n;
			nx = x + digit[0].Width() * (NUMDIGITS - 1);
		}
		else {
			MSB = -n;
			nx = x + digit[0].Width() * NUMDIGITS;
		}
		for (int i = 0; i < 2; i++) {
			int d = MSB % 10;
			MSB /= 10;
			digit[d].SetTopLeft(nx, y);
			digit[d].ShowBitmap();
			nx -= digit[d].Width();
		}
		if (n < 0) { // �p�G�p��0�A�h��ܭt��
			digit[10].SetTopLeft(nx, y);
			digit[10].ShowBitmap();
		}
	}
}