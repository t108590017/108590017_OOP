#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include <time.h>


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame* g)
		: CGameState(g)
	{

	}

	void CGameStateInit::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(0);	// 一開始的loading進度為0%
		//
		// 開始載入資料
		//
		menu.LoadBitmap(IDB_MENU);
		Choose.LoadBitmap(IDB_Choose, RGB(181, 230, 29));
		CAudio::Instance()->Load(AUDIO_MENU, "sounds\\menu.mp3");	// 載入編號3的聲音menu.mp3
		int x_pos = 210;
		int y_pos = 312;
		x = x_pos;
		y = y_pos;
		CAudio::Instance()->Play(AUDIO_MENU, true);			// 撥放 WAVE


		Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
		//


	}


	void CGameStateInit::OnBeginState()
	{

	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{

		const char KEY_ESC = 27;
		const char KEY_ENTER = 13;
		const char KEY_UP = 0x26;	// keyboard上箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		if (nChar == KEY_UP) {
			y -= 27;
			if (y < 312) {
				y = 312;
			}
		}
		if (nChar == KEY_DOWN) {
			y += 27;
			if (y > 420) {
				y = 420;
			}
		}
		if (nChar == KEY_ENTER && y == 312){
			eraser.restart(); 
			Shoot.setLeft(-999);
			eraser.setEnergy(6);
			gameMap.SetMapXY(-64, 1676);
			gameMap.changeLevel();
			Coin.setLeft(-99);
			GotoGameState(GAME_STATE_RUN);
		}
		else if (nChar == KEY_ENTER && y == 339) {
			GotoGameState(GAME_STATE_CONFIGURATION);
		}
		else if (nChar == KEY_ENTER && y == 366) {
			GotoGameState(GAME_STATE_ABOUT);
		}
		else if (nChar == KEY_ENTER && y == 420)
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
		else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
	}

	void CGameStateInit::OnKeyDown(UINT, UINT, UINT)
	{

	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		//GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
	}

	void CGameStateInit::OnShow()
	{

		//
		// 貼上logo
		//
		menu.SetTopLeft(0, 0);
		menu.ShowBitmap();
		Choose.SetTopLeft(x, y);
		Choose.ShowBitmap();
		//
		// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
		//
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, * fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f


		/*pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		pDC->TextOut(120, 220, "Please click mouse or press SPACE to begin.");
		pDC->TextOut(5, 395, "Press Ctrl-F to switch in between window mode and full screen mode.");
		if (ENABLE_GAME_PAUSE)
			pDC->TextOut(5, 425, "Press Ctrl-Q to pause the Game.");
		pDC->TextOut(5, 455, "Press Alt-F4 or ESC to Quit.");*/


		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame* g)
		: CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{
		counter--;
		if (counter < 0) {
			CAudio::Instance()->Stop(AUDIO_END);			// 撥放 WAVE
			CAudio::Instance()->Play(AUDIO_MENU, true);			// 撥放 WAVE

			GotoGameState(GAME_STATE_INIT);
		}
	}

	void CGameStateOver::OnBeginState()
	{
		counter = 30 * 5; // 5 seconds
	}

	void CGameStateOver::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
		//
		// 開始載入資料
		//
		CAudio::Instance()->Load(AUDIO_END, "sounds\\End.mp3");	// 載入編號3的聲音menu.mp3
		finish.AddBitmap(IDB_FINISH);

		//
		// 最終進度為100%
		//

		ShowInitProgress(100);

	}

	void CGameStateOver::OnShow()
	{
		finish.OnShow();
		/*CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
		CFont f, * fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str, "Game Over ! (%d)", counter / 30);
		pDC->TextOut(240, 210, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC*/

	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame* g)
		: CGameState(g), NUMBALLS(40),NUMSHOOT(20)
	{
		ball = new CBall[NUMBALLS];
		coin = new CCoin[NUMBALLS];
		health = new CHealth[NUMBALLS];
		BOSS = new CBOSS[NUMBALLS];
		Shoot = new CShoot[NUMBALLS];
		Ammo = new CAmmo[NUMBALLS];
		Jball = new CJBALL[NUMBALLS];


	}

	CGameStateRun::~CGameStateRun()
	{
		delete[] ball;
		delete[] coin;
		delete[] health;
		delete[] BOSS;
		delete[] Shoot;
		delete[] Ammo;
		delete[] Jball;


	}

	void CGameStateRun::OnBeginState()
	{
		const int BALL_GAP = 90;
		const int BALL_XY_OFFSET = 45;
		const int BALL_PER_ROW = 7;
		const int HITS_LEFT = 10;
		const int Lives_LEFT_X = 590;
		const int Lives_LEFT_Y = 450;
		const int Coin_X = 600;
		const int Coin_Y = 32;
		const int BACKGROUND_X = 0;
		const int ANIMATION_SPEED = 15;
		eraser.Initialize(&gameMap);
		eraser.SetAlive(TRUE);
		background.SetTopLeft(0, 0);				// 設定背景的起始座標
		//help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
		Lives.SetInteger(eraser.getLife());					// 指定剩下的撞擊數
		Lives.SetTopLeft(Lives_LEFT_X, Lives_LEFT_Y);		// 指定剩下撞擊數的座標

		CAudio::Instance()->Stop(AUDIO_MENU);			// 撥放 WAVE

		CAudio::Instance()->Play(AUDIO_INTRO, false);		// 撥放 WAVE
		CAudio::Instance()->Stop(AUDIO_MENU);			// 撥放 WAVE

		//for (int i = 0; i < NUMBALLS; i++) {				// 設定球的起始座標
		//int y_pos = i / BALL_PER_ROW;
		if (gameMap.getLevel() == 1) {
			for (int num = 0; num < 5; num++) {
				health[num].SetXY(0, 0);
				health[num].SetDelay(0);
				health[num].SetIsAlive(false);
				BOSS[num].SetXY(0, 0);
				BOSS[num].SetDelay(0);
				BOSS[num].SetIsAlive(false);
				Shoot[num].SetXY(0, 0);
				Shoot[num].SetDelay(0);
				Shoot[num].SetIsAlive(false);
				Ammo[num].SetXY(0, 0);
				Ammo[num].SetDelay(0);
				Ammo[num].SetIsAlive(false);
			}
			for (int num = 0; num < 25; num++) {
				coin[num].SetXY(0, 0);
				coin[num].SetDelay(0);
				coin[num].SetIsAlive(false);
				ball[num].SetXY(0, 0);
				ball[num].SetDelay(0);
				ball[num].SetIsAlive(false);
				Jball[num].SetXY(0, 0);
				Jball[num].SetDelay(0);
				Jball[num].SetIsAlive(false);
			}

			Ammo[0].SetXY(1024, 1924-3*64 + 20);
			Ammo[0].SetDelay(0);
			Ammo[0].SetIsAlive(true);
			health[0].SetXY(77 * 64, 29*64);
			health[0].SetDelay(0);
			health[0].SetIsAlive(true);
			health[1].SetXY(1024 + 91 * 64, 1921-2*64);
			health[1].SetDelay(0);
			health[1].SetIsAlive(true);
			coin[0].SetXY(1024 + 6 * 64, 1921);
			coin[0].SetDelay(0);
			coin[0].SetIsAlive(true);

			coin[1].SetXY(1024 + 49 * 64, 1921 + 64);
			coin[1].SetDelay(0);
			coin[1].SetIsAlive(true);

			coin[2].SetXY(1024 + 50 * 64, 1921 + 64);
			coin[2].SetDelay(0);
			coin[2].SetIsAlive(true);

			Ammo[1].SetXY(1024 + 48 * 64, 1924 + 64 + 20);
			Ammo[1].SetDelay(0);
			Ammo[1].SetIsAlive(true);

			coin[3].SetXY(1024 + 69 * 64, 1921);
			coin[3].SetDelay(0);
			coin[3].SetIsAlive(true);

			coin[4].SetXY(1024 + 68 * 64, 1921);
			coin[4].SetDelay(0);
			coin[4].SetIsAlive(true);

			coin[5].SetXY(1024 + 69 * 64, 1921 - 7 * 64);
			coin[5].SetDelay(0);
			coin[5].SetIsAlive(true);

			coin[6].SetXY(1024 + 64 * 64, 1921 - 10 * 64);
			coin[6].SetDelay(0);
			coin[6].SetIsAlive(true);

			coin[7].SetXY(1024 + 64 * 64, 1921 - 12 * 64);
			coin[7].SetDelay(0);
			coin[7].SetIsAlive(true);

			coin[8].SetXY(1024 + 69 * 64, 1921 - 12 * 64);
			coin[8].SetDelay(0);
			coin[8].SetIsAlive(true);

			coin[9].SetXY(1024 + 68 * 64, 1921 - 12 * 64);
			coin[9].SetDelay(0);
			coin[9].SetIsAlive(true);



			coin[10].SetXY(1024 + 67 * 64, 1921);
			coin[10].SetDelay(0);
			coin[10].SetIsAlive(true);

			coin[11].SetXY(1024 + 87 * 64, 1921 - 64);
			coin[11].SetDelay(0);
			coin[11].SetIsAlive(true);

			coin[12].SetXY(1024 + 86 * 64, 1921 - 64);
			coin[12].SetDelay(0);
			coin[12].SetIsAlive(true);

			ball[0].SetXY(1024, 1921);
			ball[0].SetDelay(0);
			ball[0].SetIsAlive(true);
			ball[1].SetXY(1664, 1729);
			ball[1].SetDelay(0);
			ball[1].SetIsAlive(true);
			ball[2].SetXY(1664 + 20 * 64, 1729 + 3 * 64);
			ball[2].SetDelay(0);
			ball[2].SetIsAlive(true);
			ball[3].SetXY(1664 + 30 * 64, 1729 + 3 * 64);
			ball[3].SetDelay(0);
			ball[3].SetIsAlive(true);
			ball[4].SetXY(1664 + 39 * 64, 1729);
			ball[4].SetDelay(0);
			ball[4].SetIsAlive(true);
			ball[5].SetXY(1664 + 45 * 64, 1729 + 4 * 64);
			ball[5].SetDelay(0);
			ball[5].SetIsAlive(true);
			ball[6].SetXY(1664 + 56 * 64, 1729 - 64);
			ball[6].SetDelay(0);
			ball[6].SetIsAlive(true);
			ball[7].SetXY(1664 + 64 * 64, 1729 + 5 * 64);
			ball[7].SetDelay(0);
			ball[7].SetIsAlive(true);
		}
		else if (gameMap.getLevel() == 2) {
			for (int num = 0; num < 5; num++) {
				health[num].SetXY(0, 0);
				health[num].SetDelay(0);
				health[num].SetIsAlive(false);
				BOSS[num].SetXY(0, 0);
				BOSS[num].SetDelay(0);
				BOSS[num].SetIsAlive(false);
				Shoot[num].SetXY(0, 0);
				Shoot[num].SetDelay(0);
				Shoot[num].SetIsAlive(false);
				Ammo[num].SetXY(0, 0);
				Ammo[num].SetDelay(0);
				Ammo[num].SetIsAlive(false);
			}
			for (int num = 0; num < 25; num++) {
				coin[num].SetXY(0, 0);
				coin[num].SetDelay(0);
				coin[num].SetIsAlive(false);
				ball[num].SetXY(0, 0);
				ball[num].SetDelay(0);
				ball[num].SetIsAlive(false);
				Jball[num].SetXY(0, 0);
				Jball[num].SetDelay(0);
				Jball[num].SetIsAlive(false);
			}

			coin[0].SetXY(14 * 64, 1921 + 6 * 64);
			coin[0].SetDelay(0);
			coin[0].SetIsAlive(true);

			coin[1].SetXY(15 * 64, 1921 + 6 * 64);
			coin[1].SetDelay(0);
			coin[1].SetIsAlive(true);

			coin[2].SetXY(16 * 64, 1921 + 6 * 64);
			coin[2].SetDelay(0);
			coin[2].SetIsAlive(true);

			coin[3].SetXY(17 * 64, 1921 + 6 * 64);
			coin[3].SetDelay(0);
			coin[3].SetIsAlive(true);

			Ammo[0].SetXY(18 * 64, 1921 + 8 * 64 + 20);
			Ammo[0].SetDelay(0);
			Ammo[0].SetIsAlive(true);

			coin[4].SetXY(1024 + 39 * 64, 1921 + 64);
			coin[4].SetDelay(0);
			coin[4].SetIsAlive(true);

			coin[5].SetXY(1024 + 41 * 64, 1921 + 64);
			coin[5].SetDelay(0);
			coin[5].SetIsAlive(true);

			coin[6].SetXY(1024 + 40 * 64, 1921 + 64);
			coin[6].SetDelay(0);
			coin[6].SetIsAlive(true);



			coin[7].SetXY(1664 + 53 * 64, 1921 + 3 * 64);
			coin[7].SetDelay(0);
			coin[7].SetIsAlive(true);

			coin[8].SetXY(1664 + 52 * 64, 1921 + 3 * 64);
			coin[8].SetDelay(0);
			coin[8].SetIsAlive(true);


			coin[9].SetXY(1024 + 69 * 64, 1729 + 11 * 64);
			coin[9].SetDelay(0);
			coin[9].SetIsAlive(true);

			coin[10].SetXY(1024 + 70 * 64, 1729 + 11 * 64);
			coin[10].SetDelay(0);
			coin[10].SetIsAlive(true);


			coin[11].SetXY(1664 + 69 * 64, 1729 + 9 * 64);
			coin[11].SetDelay(0);
			coin[11].SetIsAlive(true);

			coin[12].SetXY(1664 + 70 * 64, 1729 + 9 * 64);
			coin[12].SetDelay(0);
			coin[12].SetIsAlive(true);

			coin[13].SetXY(1664 + 71 * 64, 1729 + 9 * 64);
			coin[13].SetDelay(0);
			coin[13].SetIsAlive(true);


			ball[0].SetXY(1024 + 5 * 64, 1921 + 8 * 64);
			ball[0].SetDelay(0);
			ball[0].SetIsAlive(true);
			ball[1].SetXY(1024 + 14 * 64, 1921 + 8 * 64);
			ball[1].SetDelay(0);
			ball[1].SetIsAlive(true);
			ball[2].SetXY(1024 + 28 * 64, 1921 + 7 * 64);
			ball[2].SetDelay(0);
			ball[2].SetIsAlive(true);
			ball[3].SetXY(1664 + 30 * 64, 1729 + 5 * 64);
			ball[3].SetDelay(0);
			ball[2].SetIsAlive(true);
			ball[3].SetXY(1664 + 30 * 64, 1729 + 5 * 64);
			ball[3].SetDelay(0);
			ball[3].SetIsAlive(true);
			Ammo[1].SetXY(1664 + 31 * 64, 1729 + 5 * 64 + 20);
			Ammo[1].SetDelay(0);
			Ammo[1].SetIsAlive(true);

			ball[4].SetXY(1664 + 41 * 64, 1729 + 9 * 64);
			ball[4].SetDelay(0);
			ball[4].SetIsAlive(true);
			ball[5].SetXY(1664 + 48 * 64, 1729 + 7 * 64);
			ball[5].SetDelay(0);
			ball[5].SetIsAlive(true);
			ball[6].SetXY(1664 + 55 * 64, 1729 + 9 * 64);
			ball[6].SetDelay(0);
			ball[6].SetIsAlive(true);
			ball[7].SetXY(1664 + 64 * 64, 1729 + 9 * 64);
			ball[7].SetDelay(0);
			ball[7].SetIsAlive(true);
		}
		else if (gameMap.getLevel() == 3) {
			for (int num = 0; num < 5; num++) {
				health[num].SetXY(0, 0);
				health[num].SetDelay(0);
				health[num].SetIsAlive(false);
				BOSS[num].SetXY(0, 0);
				BOSS[num].SetDelay(0);
				BOSS[num].SetIsAlive(false);
				Shoot[num].SetXY(0, 0);
				Shoot[num].SetDelay(0);
				Shoot[num].SetIsAlive(false);
				Ammo[num].SetXY(0, 0);
				Ammo[num].SetDelay(0);
				Ammo[num].SetIsAlive(false);
			}
			for (int num = 0; num < 25; num++) {
				coin[num].SetXY(0, 0);
				coin[num].SetDelay(0);
				coin[num].SetIsAlive(false);
				ball[num].SetXY(0, 0);
				ball[num].SetDelay(0);
				ball[num].SetIsAlive(false);
				Jball[num].SetXY(0, 0);
				Jball[num].SetDelay(0);
				Jball[num].SetIsAlive(false);
			}
			health[0].SetXY(21*64,20*64);
			health[0].SetDelay(0);
			health[0].SetIsAlive(true);

			health[1].SetXY(66 * 64, 27 * 64);
			health[1].SetDelay(0);
			health[1].SetIsAlive(true);

			ball[0].SetXY(12 * 64, 1921);
			ball[0].SetDelay(0);
			ball[0].SetIsAlive(true);

			coin[0].SetXY(15 * 64, 1921 - 4 * 64);
			coin[0].SetDelay(0);
			coin[0].SetIsAlive(true);

			coin[1].SetXY(16 * 64, 1921 - 4 * 64);
			coin[1].SetDelay(0);
			coin[1].SetIsAlive(true);

			coin[2].SetXY(17 * 64, 1921 - 4 * 64);
			coin[2].SetDelay(0);
			coin[2].SetIsAlive(true);

			Ammo[0].SetXY(16 * 64, 1921 - 3 * 64 + 20);
			Ammo[0].SetDelay(0);
			Ammo[0].SetIsAlive(true);
			Ammo[1].SetXY(17 * 64, 1921 - 3 * 64 + 20);
			Ammo[1].SetDelay(0);
			Ammo[1].SetIsAlive(true);


			coin[3].SetXY(21 * 64, 1921 - 2 * 64);
			coin[3].SetDelay(0);
			coin[3].SetIsAlive(true);

			coin[4].SetXY(22 * 64, 1921 - 2 * 64);
			coin[4].SetDelay(0);
			coin[4].SetIsAlive(true);

			coin[5].SetXY(23 * 64, 1921 - 2 * 64);
			coin[5].SetDelay(0);
			coin[5].SetIsAlive(true);

			ball[1].SetXY(23 * 64, 1921 - 4 * 64);
			ball[1].SetDelay(0);
			ball[1].SetIsAlive(true);

			ball[2].SetXY(26 * 64, 1921 - 4 * 64);
			ball[2].SetDelay(0);
			ball[2].SetIsAlive(true);

			ball[3].SetXY(29 * 64, 1921 - 4 * 64);
			ball[3].SetDelay(0);
			ball[3].SetIsAlive(true);

			ball[4].SetXY(38 * 64, 1921 - 10 * 64);
			ball[4].SetDelay(0);
			ball[4].SetIsAlive(true);

			ball[5].SetXY(27 * 64, 1921 - 10 * 64);
			ball[5].SetDelay(0);
			ball[5].SetIsAlive(true);

			ball[6].SetXY(38 * 64, 1921 - 18 * 64);
			ball[6].SetDelay(0);
			ball[6].SetIsAlive(true);

			coin[6].SetXY(42 * 64, 1921 - 22 * 64);
			coin[6].SetDelay(0);
			coin[6].SetIsAlive(true);

			coin[7].SetXY(58 * 64, 1921 - 5 * 64);
			coin[7].SetDelay(0);
			coin[7].SetIsAlive(true);

			coin[8].SetXY(58 * 64, 1921 - 7 * 64);
			coin[8].SetDelay(0);
			coin[8].SetIsAlive(true);

			coin[9].SetXY(58 * 64, 1921 - 8 * 64);
			coin[9].SetDelay(0);
			coin[9].SetIsAlive(true);

			coin[10].SetXY(58 * 64, 1921 - 3 * 64);
			coin[10].SetDelay(0);
			coin[10].SetIsAlive(true);

			coin[11].SetXY(58 * 64, 1921 - 6 * 64);
			coin[11].SetDelay(0);
			coin[11].SetIsAlive(true);

			coin[12].SetXY(58 * 64, 1921 - 4 * 64);
			coin[12].SetDelay(0);
			coin[12].SetIsAlive(true);

			coin[13].SetXY(63 * 64, 1921 - 10 * 64);
			coin[13].SetDelay(0);
			coin[13].SetIsAlive(true);

			coin[14].SetXY(63 * 64, 1921 - 11 * 64);
			coin[14].SetDelay(0);
			coin[14].SetIsAlive(true);

			coin[15].SetXY(63 * 64, 1921 - 12 * 64);
			coin[15].SetDelay(0);
			coin[15].SetIsAlive(true);

			coin[16].SetXY(63 * 64, 1921 - 9 * 64);
			coin[16].SetDelay(0);
			coin[16].SetIsAlive(true);

			coin[17].SetXY(63 * 64, 1921 - 8 * 64);
			coin[17].SetDelay(0);
			coin[17].SetIsAlive(true);
		}
		else if (gameMap.getLevel() == 4) {
			for (int num = 0; num < 5; num++) {
				health[num].SetXY(0, 0);
				health[num].SetDelay(0);
				health[num].SetIsAlive(false);
				BOSS[num].SetXY(0, 0);
				BOSS[num].SetDelay(0);
				BOSS[num].SetIsAlive(false);
				Shoot[num].SetXY(0, 0);
				Shoot[num].SetDelay(0);
				Shoot[num].SetIsAlive(false);
				Ammo[num].SetXY(0, 0);
				Ammo[num].SetDelay(0);
				Ammo[num].SetIsAlive(false);
			}
			for (int num = 0; num < 25; num++) {
				coin[num].SetXY(0, 0);
				coin[num].SetDelay(0);
				coin[num].SetIsAlive(false);
				ball[num].SetXY(0, 0);
				ball[num].SetDelay(0);
				ball[num].SetIsAlive(false);
				Jball[num].SetXY(0, 0);
				Jball[num].SetDelay(0);
				Jball[num].SetIsAlive(false);
			}
			health[0].SetXY(120 * 64, 13* 64);
			health[0].SetDelay(0);
			health[0].SetIsAlive(true);

			coin[0].SetXY(17 * 64, 1921 - 5 * 64);
			coin[0].SetDelay(0);
			coin[0].SetIsAlive(true);

			coin[1].SetXY(18 * 64, 1921 - 5 * 64);
			coin[1].SetDelay(0);
			coin[1].SetIsAlive(true);

			coin[2].SetXY(19 * 64, 1921 - 5 * 64);
			coin[2].SetDelay(0);
			coin[2].SetIsAlive(true);

			ball[0].SetXY(18 * 64, 1921 - 1 * 64);
			ball[0].SetDelay(0);
			ball[0].SetIsAlive(true);
			ball[1].SetXY(32 * 64, 1921 - 1 * 64);
			ball[1].SetDelay(0);
			ball[1].SetIsAlive(true);

			Ammo[0].SetXY(32 * 64, 1921 - 4 * 64 + 20);
			Ammo[0].SetDelay(0);
			Ammo[0].SetIsAlive(true);
			Ammo[1].SetXY(31 * 64, 1921 - 1 * 64 + 20);
			Ammo[1].SetDelay(0);
			Ammo[1].SetIsAlive(true);
			Ammo[2].SetXY(30 * 64, 1921 - 1 * 64 + 20);
			Ammo[2].SetDelay(0);
			Ammo[2].SetIsAlive(true);

			ball[2].SetXY(37 * 64, 1921 - 1 * 64);
			ball[2].SetDelay(0);
			ball[2].SetIsAlive(true);
			ball[3].SetXY(43 * 64, 1921 - 1 * 64);
			ball[3].SetDelay(0);
			ball[3].SetIsAlive(true);
			ball[4].SetXY(0, 0);
			ball[4].SetDelay(0);
			ball[4].SetIsAlive(true);

			coin[3].SetXY(63 * 64, 1921 - 4 * 64);
			coin[3].SetDelay(0);
			coin[3].SetIsAlive(true);
			coin[4].SetXY(63 * 64, 1921 - 6 * 64);
			coin[4].SetDelay(0);
			coin[4].SetIsAlive(true);
			coin[5].SetXY(63 * 64, 1921 - 5 * 64);
			coin[5].SetDelay(0);
			coin[5].SetIsAlive(true);

			ball[5].SetXY(59 * 64, 1921);
			ball[5].SetDelay(0);
			ball[5].SetIsAlive(true);
			ball[6].SetXY(52 * 64, 1921 - 12 * 64);
			ball[6].SetDelay(0);
			ball[6].SetIsAlive(true);
			ball[7].SetXY(47 * 64, 1921 - 11 * 64);
			ball[7].SetDelay(0);
			ball[7].SetIsAlive(true);
			ball[8].SetXY(38 * 64, 1921 - 11 * 64);
			ball[8].SetDelay(0);
			ball[8].SetIsAlive(true);

			ball[9].SetXY(32 * 64, 1921 - 11 * 64);
			ball[9].SetDelay(0);
			ball[9].SetIsAlive(true);

			coin[6].SetXY(64 + 10 * 64, 1921 - 19 * 64);
			coin[6].SetDelay(0);
			coin[6].SetIsAlive(true);
			coin[7].SetXY(64 + 11 * 64, 1921 - 19 * 64);
			coin[7].SetDelay(0);
			coin[7].SetIsAlive(true);
			coin[8].SetXY(64 + 12 * 64, 1921 - 19 * 64);
			coin[8].SetDelay(0);
			coin[8].SetIsAlive(true);
			coin[9].SetXY(64, 1921 - 16 * 64);
			coin[9].SetDelay(0);
			coin[9].SetIsAlive(true);

			ball[10].SetXY(12 * 64, 1921 - 13 * 64);
			ball[10].SetDelay(0);
			ball[10].SetIsAlive(true);

			ball[11].SetXY(21 * 64, 1921 - 13 * 64);
			ball[11].SetDelay(0);
			ball[11].SetIsAlive(true);
			ball[12].SetXY(21 * 64, 1921 - 19 * 64);
			ball[12].SetDelay(0);
			ball[12].SetIsAlive(true);

			ball[9].SetXY(25 * 64, 1921 - 24 * 64);
			ball[9].SetDelay(0);
			ball[9].SetIsAlive(true);

			ball[10].SetXY(35 * 64, 1921 - 24 * 64);
			ball[10].SetDelay(0);
			ball[10].SetIsAlive(true);

			ball[11].SetXY(43 * 64, 1921 - 24 * 64);
			ball[11].SetDelay(0);
			ball[11].SetIsAlive(true);

			coin[10].SetXY(50 * 64, 1921 - 23 * 64);
			coin[10].SetDelay(0);
			coin[10].SetIsAlive(true);
			coin[11].SetXY(48 * 64, 1921 - 23 * 64);
			coin[11].SetDelay(0);
			coin[11].SetIsAlive(true);
			coin[12].SetXY(49 * 64, 1921 - 23 * 64);
			coin[12].SetDelay(0);
			coin[12].SetIsAlive(true);

			ball[12].SetXY(57 * 64, 1921 - 26 * 64);
			ball[12].SetDelay(0);
			ball[12].SetIsAlive(true);

		}
		else if (gameMap.getLevel() == 5) {
			for (int num = 0; num < 5; num++) {
				health[num].SetXY(0, 0);
				health[num].SetDelay(0);
				health[num].SetIsAlive(false);
				BOSS[num].SetXY(0, 0);
				BOSS[num].SetDelay(0);
				BOSS[num].SetIsAlive(false);
				Shoot[num].SetXY(0, 0);
				Shoot[num].SetDelay(0);
				Shoot[num].SetIsAlive(false);
				Ammo[num].SetXY(0, 0);
				Ammo[num].SetDelay(0);
				Ammo[num].SetIsAlive(false);

			}
			for (int num = 0; num < 15; num++) {
				ball[num].SetXY(0, 0);
				ball[num].SetDelay(0);
				ball[num].SetIsAlive(false);

				coin[num].SetXY(0, 0);
				coin[num].SetDelay(0);
				coin[num].SetIsAlive(false);
			}
			health[0].SetXY(19 * 64, 1920 );
			health[0].SetDelay(0);
			health[0].SetIsAlive(true);
			Ammo[0].SetXY(4*64, 1920);
			Ammo[0].SetDelay(0);
			Ammo[0].SetIsAlive(true);
			Ammo[1].SetXY(5 * 64, 1920 - 3 * 64 + 20);
			Ammo[1].SetDelay(0);
			Ammo[1].SetIsAlive(true);
			Ammo[2].SetXY(6 * 64, 1920 - 3 * 64 + 20);
			Ammo[2].SetDelay(0);
			Ammo[2].SetIsAlive(true);
			Ammo[3].SetXY(7 * 64, 1920 - 3 * 64 + 20);
			Ammo[3].SetDelay(0);
			Ammo[3].SetIsAlive(true);
			Jball[0].SetXY(10 * 64, 1920);
			Jball[0].SetDelay(0);
			Jball[0].SetIsAlive(true);
			Jball[1].SetXY(11 * 64, 1920);
			Jball[1].SetDelay(0);
			Jball[1].SetIsAlive(true);
			Jball[2].SetXY(12 * 64, 1920-2*64);
			Jball[2].SetDelay(0);
			Jball[2].SetIsAlive(true);
			Jball[3].SetXY(13 * 64, 1920-2*64);
			Jball[3].SetDelay(0);
			Jball[3].SetIsAlive(true);
			Jball[4].SetXY(14 * 64, 1920-2*64);
			Jball[4].SetDelay(0);
			Jball[4].SetIsAlive(true);
			Jball[5].SetXY(15 * 64, 1920);
			Jball[5].SetDelay(0);
			Jball[5].SetIsAlive(true);
			Jball[6].SetXY(16 * 64, 1920);
			Jball[6].SetDelay(0);
			Jball[6].SetIsAlive(true);
			Jball[7].SetXY(22 * 64, 1920);
			Jball[7].SetDelay(0);
			Jball[7].SetIsAlive(true);
			Jball[13].SetXY(23 * 64, 1920);
			Jball[13].SetDelay(0);
			Jball[13].SetIsAlive(true);
			Jball[8].SetXY(20 * 64, 1920-5*64);
			Jball[8].SetDelay(0);
			Jball[8].SetIsAlive(true);
			Jball[9].SetXY(21 * 64, 1920);
			Jball[9].SetDelay(0);
			Jball[9].SetIsAlive(true);
			Jball[10].SetXY(17 * 64, 1920);
			Jball[10].SetDelay(0);
			Jball[10].SetIsAlive(true);
			Jball[11].SetXY(18 * 64, 1920 - 5 * 64);
			Jball[11].SetDelay(0);
			Jball[11].SetIsAlive(true);
			Jball[12].SetXY(19 * 64, 1920-5*64);
			Jball[12].SetDelay(0);
			Jball[12].SetIsAlive(true);

		}
		else if (gameMap.getLevel() == 6) {
			for (int num = 0; num < 5; num++) {
				health[num].SetXY(0, 0);
				health[num].SetDelay(0);
				health[num].SetIsAlive(false);
				BOSS[num].SetXY(0, 0);
				BOSS[num].SetDelay(0);
				BOSS[num].SetIsAlive(false);
				Shoot[num].SetXY(0, 0);
				Shoot[num].SetDelay(0);
				Shoot[num].SetIsAlive(false);
				Ammo[num].SetXY(0, 0);
				Ammo[num].SetDelay(0);
				Ammo[num].SetIsAlive(false);
				Jball[num].SetXY(0, 0);
				Jball[num].SetDelay(0);
				Jball[num].SetIsAlive(false);
			}
			for (int num = 0; num < 25; num++) {
				coin[num].SetXY(0, 0);
				coin[num].SetDelay(0);
				coin[num].SetIsAlive(false);
				ball[num].SetXY(0, 0);
				ball[num].SetDelay(0);
				ball[num].SetIsAlive(false);
				Jball[num].SetXY(0, 0);
				Jball[num].SetDelay(0);
				Jball[num].SetIsAlive(false);
			}
			health[0].SetXY(68 * 64, 10 * 64);
			health[0].SetDelay(0);
			health[0].SetIsAlive(true);
			coin[0].SetXY(45 * 64, 10 * 64);
			coin[0].SetDelay(0);
			coin[0].SetIsAlive(true);
			coin[1].SetXY(43 * 64, 10 * 64);
			coin[1].SetDelay(0);
			coin[1].SetIsAlive(true);
			coin[2].SetXY(44 * 64, 10 * 64);
			coin[2].SetDelay(0);
			coin[2].SetIsAlive(true);
			Ammo[0].SetXY(40 * 64, 11 * 64 + 20);
			Ammo[0].SetDelay(0);
			Ammo[0].SetIsAlive(true);
			Ammo[1].SetXY(42 * 64, 11 * 64 + 20);
			Ammo[1].SetDelay(0);
			Ammo[1].SetIsAlive(true);
			Ammo[2].SetXY(41 * 64, 11 * 64 + 20);
			Ammo[2].SetDelay(0);
			Ammo[2].SetIsAlive(true);
			Ammo[3].SetXY(34 * 64, 13 * 64 + 20    );
			Ammo[3].SetDelay(0);
			Ammo[3].SetIsAlive(true);

			coin[3].SetXY(52 * 64, 10 * 64);
			coin[3].SetDelay(0);
			coin[3].SetIsAlive(true);

			ball[0].SetXY(32 * 64, 13 * 64);
			ball[0].SetDelay(0);
			ball[0].SetIsAlive(true);

			ball[1].SetXY(41 * 64, 13 * 64);
			ball[1].SetDelay(0);
			ball[1].SetIsAlive(true);

			ball[1].SetXY(59 * 64, 13 * 64);
			ball[1].SetDelay(0);
			ball[1].SetIsAlive(true);
			ball[2].SetXY(60 * 64, 13 * 64);
			ball[2].SetDelay(0);
			ball[2].SetIsAlive(true);
			ball[3].SetXY(61 * 64, 13 * 64);
			ball[3].SetDelay(0);
			ball[3].SetIsAlive(true);
			ball[4].SetXY(62 * 64, 13 * 64);
			ball[4].SetDelay(0);
			ball[4].SetIsAlive(true);
			ball[5].SetXY(63 * 64, 13 * 64);
			ball[5].SetDelay(0);
			ball[5].SetIsAlive(true);
			ball[6].SetXY(64 * 64, 13 * 64);
			ball[6].SetDelay(0);
			ball[6].SetIsAlive(true);
			ball[7].SetXY(65 * 64, 13 * 64);
			ball[7].SetDelay(0);
			ball[7].SetIsAlive(true);
			ball[8].SetXY(66 * 64, 13 * 64);
			ball[8].SetDelay(0);
			ball[8].SetIsAlive(true);
			ball[9].SetXY(58 * 64, 13 * 64);
			ball[9].SetDelay(0);
			ball[9].SetIsAlive(true);
			ball[10].SetXY(73 * 64, 12 * 64);
			ball[10].SetDelay(0);
			ball[10].SetIsAlive(true);
			ball[11].SetXY(78 * 64, 13 * 64);
			ball[11].SetDelay(0);
			ball[11].SetIsAlive(true);
			ball[12].SetXY(79 * 64, 13 * 64);
			ball[12].SetDelay(0);
			ball[12].SetIsAlive(true);
			ball[13].SetXY(98 * 64, 16 * 64);
			ball[13].SetDelay(0);
			ball[13].SetIsAlive(true);
			ball[14].SetXY(99 * 64, 16 * 64);
			ball[14].SetDelay(0);
			ball[14].SetIsAlive(true);

			coin[4].SetXY(101 * 64, 16 * 64);
			coin[4].SetDelay(0);
			coin[4].SetIsAlive(true);
			coin[5].SetXY(106 * 64, 17 * 64);
			coin[5].SetDelay(0);
			coin[5].SetIsAlive(true);
			coin[6].SetXY(107 * 64, 17 * 64);
			coin[6].SetDelay(0);
			coin[6].SetIsAlive(true);

			ball[15].SetXY(113 * 64, 17 * 64);
			ball[15].SetDelay(0);
			ball[15].SetIsAlive(true);
			ball[16].SetXY(114 * 64, 17 * 64);
			ball[16].SetDelay(0);
			ball[16].SetIsAlive(true);
			ball[17].SetXY(115 * 64, 17 * 64);
			ball[17].SetDelay(0);
			ball[17].SetIsAlive(true);

			ball[18].SetXY(130 * 64, 17 * 64);
			ball[18].SetDelay(0);
			ball[18].SetIsAlive(true);
			ball[19].SetXY(135 * 64, 17 * 64);
			ball[19].SetDelay(0);
			ball[19].SetIsAlive(true);
			ball[20].SetXY(133 * 64, 14 * 64);
			ball[20].SetDelay(0);
			ball[20].SetIsAlive(true);
			coin[7].SetXY(139 * 64, 18 * 64);
			coin[7].SetDelay(0);
			coin[7].SetIsAlive(true);
			coin[8].SetXY(125 * 64, 24 * 64);
			coin[8].SetDelay(0);
			coin[8].SetIsAlive(true);
			ball[21].SetXY(130 * 64, 24 * 64);
			ball[21].SetDelay(0);
			ball[21].SetIsAlive(true);
			ball[25].SetXY(103 * 64, 24 * 64);
			ball[25].SetDelay(0);
			ball[25].SetIsAlive(true);
			coin[10].SetXY(102 * 64, 24 * 64);
			coin[10].SetDelay(0);
			coin[10].SetIsAlive(true);
			coin[11].SetXY(100 * 64, 25 * 64);
			coin[11].SetDelay(0);
			coin[11].SetIsAlive(true);
			ball[22].SetXY(99 * 64, 28 * 64);
			ball[22].SetDelay(0);
			ball[22].SetIsAlive(true);


			coin[14].SetXY(71 * 64, 25 * 64);
			coin[14].SetDelay(0);
			coin[14].SetIsAlive(true);
			coin[12].SetXY(71 * 64, 24 * 64);
			coin[12].SetDelay(0);
			coin[12].SetIsAlive(true);
			coin[13].SetXY(71 * 64, 23 * 64);
			coin[13].SetDelay(0);
			coin[13].SetIsAlive(true);
			health[1].SetXY(72 * 64, 23 * 64);
			health[1].SetDelay(0);
			health[1].SetIsAlive(true);
			ball[23].SetXY(72 * 64, 25 * 64);
			ball[23].SetDelay(0);
			ball[23].SetIsAlive(true);
			ball[24].SetXY(75 * 64, 25 * 64);
			ball[24].SetDelay(0);
			ball[24].SetIsAlive(true);
			health[1].SetXY(28 * 64, 28 * 64);
			health[1].SetDelay(0);
			health[1].SetIsAlive(true);

		}
		else if (gameMap.getLevel() == 7) {
			for (int num = 0; num < 5; num++) {
				health[num].SetXY(0, 0);
				health[num].SetDelay(0);
				health[num].SetIsAlive(false);

				Shoot[num].SetXY(0, 0);
				Shoot[num].SetDelay(0);
				Shoot[num].SetIsAlive(false);
				Ammo[num].SetXY(0, 0);
				Ammo[num].SetDelay(0);
				Ammo[num].SetIsAlive(false);
			}
			for (int num = 0; num < 25; num++) {
				coin[num].SetXY(0, 0);
				coin[num].SetDelay(0);
				coin[num].SetIsAlive(false);
				ball[num].SetXY(0, 0);
				ball[num].SetDelay(0);
				ball[num].SetIsAlive(false);
				Jball[num].SetXY(0, 0);
				Jball[num].SetDelay(0);
				Jball[num].SetIsAlive(false);
			}
			BOSS[0].SetXY(120*64, 35*64);
			BOSS[0].SetDelay(0);
			BOSS[0].SetIsAlive(true);
			ball[0].SetXY(12 * 64, 35 * 64);
			ball[0].SetDelay(0);
			ball[0].SetIsAlive(true);

			Ammo[0].SetXY(16 * 64, 35 * 64+20);
			Ammo[0].SetDelay(0);
			Ammo[0].SetIsAlive(true);
			Ammo[1].SetXY(17 * 64, 35 * 64 + 20);
			Ammo[1].SetDelay(0);
			Ammo[1].SetIsAlive(true);
			Ammo[2].SetXY(18 * 64, 35 * 64 + 20);
			Ammo[2].SetDelay(0);
			Ammo[2].SetIsAlive(true);
			Ammo[3].SetXY(19 * 64, 35 * 64 + 20);
			Ammo[3].SetDelay(0);
			Ammo[3].SetIsAlive(true);

			coin[0].SetXY(22 * 64, 31 * 64);
			coin[0].SetDelay(0);
			coin[0].SetIsAlive(true);

			ball[1].SetXY(12 * 64, 28* 64);
			ball[1].SetDelay(0);
			ball[1].SetIsAlive(true);

			ball[2].SetXY(13 * 64, 22 * 64);
			ball[2].SetDelay(0);
			ball[2].SetIsAlive(true);

			ball[3].SetXY(8 * 64, 25 * 64);
			ball[3].SetDelay(0);
			ball[3].SetIsAlive(true);
			ball[4].SetXY(8 * 64, 20 * 64);
			ball[4].SetDelay(0);
			ball[4].SetIsAlive(true);
			ball[5].SetXY(13 * 64, 17 * 64);
			ball[5].SetDelay(0);
			ball[5].SetIsAlive(true);
			ball[6].SetXY(23 * 64, 17 * 64);
			ball[6].SetDelay(0);
			ball[6].SetIsAlive(true);
			ball[7].SetXY(24 * 64, 17 * 64);
			ball[7].SetDelay(0);
			ball[7].SetIsAlive(true);
			ball[8].SetXY(25 * 64, 17 * 64);
			ball[8].SetDelay(0);
			ball[8].SetIsAlive(true);
			coin[1].SetXY(2 * 64, 20 * 64);
			coin[1].SetDelay(0);
			coin[1].SetIsAlive(true);
			ball[9].SetXY(39 * 64, 14 * 64);
			ball[9].SetDelay(0);
			ball[9].SetIsAlive(true);
			ball[10].SetXY(51 * 64, 14 * 64);
			ball[10].SetDelay(0);
			ball[10].SetIsAlive(true);
			coin[2].SetXY(44 * 64, 17 * 64);
			coin[2].SetDelay(0);
			coin[2].SetIsAlive(true);
			coin[3].SetXY(45 * 64, 17 * 64);
			coin[3].SetDelay(0);
			coin[3].SetIsAlive(true);
			coin[17].SetXY(46 * 64, 17 * 64);
			coin[17].SetDelay(0);
			coin[17].SetIsAlive(true);
			health[0].SetXY(45 * 64, 16 * 64);
			health[0].SetDelay(0);
			health[0].SetIsAlive(true);

			ball[11].SetXY(59 * 64, 13 * 64);
			ball[11].SetDelay(0);
			ball[11].SetIsAlive(true);
			ball[12].SetXY(59 * 64, 11 * 64);
			ball[12].SetDelay(0);
			ball[12].SetIsAlive(true);
			coin[4].SetXY(59 * 64, 13 * 64);
			coin[4].SetDelay(0);
			coin[4].SetIsAlive(true);
			coin[5].SetXY(58 * 64, 13 * 64);
			coin[5].SetDelay(0);
			coin[5].SetIsAlive(true);
			coin[6].SetXY(60 * 64, 13 * 64);
			coin[6].SetDelay(0);
			coin[6].SetIsAlive(true);
			coin[7].SetXY(59 * 64, 11 * 64);
			coin[7].SetDelay(0);
			coin[7].SetIsAlive(true);
			coin[8].SetXY(58 * 64, 11* 64);
			coin[8].SetDelay(0);
			coin[8].SetIsAlive(true);
			coin[9].SetXY(60 * 64, 11 * 64);
			coin[9].SetDelay(0);
			coin[9].SetIsAlive(true);

			coin[10].SetXY(84 * 64, 16 * 64);
			coin[10].SetDelay(0);
			coin[10].SetIsAlive(true);
			coin[11].SetXY(85 * 64, 16 * 64);
			coin[11].SetDelay(0);
			coin[11].SetIsAlive(true);
			coin[12].SetXY(86 * 64, 16 * 64);
			coin[12].SetDelay(0);
			coin[12].SetIsAlive(true);
			health[1].SetXY(85 * 64, 17 * 64);
			health[1].SetDelay(0);
			health[1].SetIsAlive(true);
			ball[13].SetXY(85 * 64, 13 * 64);
			ball[13].SetDelay(0);
			ball[13].SetIsAlive(true);
			ball[14].SetXY(79 * 64, 10 * 64);
			ball[14].SetDelay(0);
			ball[14].SetIsAlive(true);
			ball[15].SetXY(85 * 64, 7 * 64);
			ball[15].SetDelay(0);
			ball[15].SetIsAlive(true);
			ball[16].SetXY(76 * 64, 5 * 64);
			ball[16].SetDelay(0);
			ball[16].SetIsAlive(true);
			ball[17].SetXY(70 * 64, 5 * 64);
			ball[17].SetDelay(0);
			ball[17].SetIsAlive(true);
			ball[18].SetXY(57 * 64, 5 * 64);
			ball[18].SetDelay(0);
			ball[18].SetIsAlive(true);
			ball[19].SetXY(56 * 64, 5 * 64);
			ball[19].SetDelay(0);
			ball[19].SetIsAlive(true);
			ball[20].SetXY(58 * 64, 5 * 64);
			ball[20].SetDelay(0);
			ball[20].SetIsAlive(true);
			coin[13].SetXY(64 * 64, 7 * 64);
			coin[13].SetDelay(0);
			coin[13].SetIsAlive(true);

			ball[21].SetXY(44 * 64, 5 * 64);
			ball[21].SetDelay(0);
			ball[21].SetIsAlive(true);
			ball[22].SetXY(46 * 64, 5 * 64);
			ball[22].SetDelay(0);
			ball[22].SetIsAlive(true);
			coin[14].SetXY(36 * 64, 7 * 64);
			coin[14].SetDelay(0);
			coin[14].SetIsAlive(true);
			coin[15].SetXY(26 * 64, 7 * 64);
			coin[15].SetDelay(0);
			coin[15].SetIsAlive(true);
			coin[16].SetXY(25 * 64, 7 * 64);
			coin[16].SetDelay(0);
			coin[16].SetIsAlive(true);
		}
		else if (gameMap.getLevel()== 8) {
		for (int num = 0; num < 20; num++) {
			health[num].SetXY(0, 0);
			health[num].SetDelay(0);
			health[num].SetIsAlive(false);

			Shoot[num].SetXY(0, 0);
			Shoot[num].SetDelay(0);
			Shoot[num].SetIsAlive(false);
			Ammo[num].SetXY(0, 0);
			Ammo[num].SetDelay(0);
			Ammo[num].SetIsAlive(false);
		}
		for (int num = 0; num < 30; num++) {
			coin[num].SetXY(0, 0);
			coin[num].SetDelay(0);
			coin[num].SetIsAlive(false);
			ball[num].SetXY(0, 0);
			ball[num].SetDelay(0);
			ball[num].SetIsAlive(false);
			Jball[num].SetXY(0, 0);
			Jball[num].SetDelay(0);
			Jball[num].SetIsAlive(false);
		}
			BOSS[0].SetXY(9 * 64, 28 * 64+30);
			BOSS[0].SetDelay(0);
			BOSS[0].SetIsAlive(true);

}
	}

	void CGameStateRun::OnMove()							// 移動遊戲元素
	{
		//
		// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
		//
		// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
		//
		// 移動背景圖的座標
		//
		//if (background.Top() > SIZE_Y)
		//	background.SetTopLeft(60, -background.Height());
		//	background.SetTopLeft(background.Left(), background.Top() + 1);
		//
		// 移動球
		//
		int i;

		for (i = 0; i < NUMBALLS; i++)
			ball[i].OnMove();
		for (i = 0; i < NUMBALLS; i++)
			Shoot[i].OnMove();
		for (i = 0; i < NUMBALLS; i++)
			Jball[i].OnMove();
		BOSS[0].OnMove();
		//
		// 移動擦子
		//
		eraser.OnMove(&gameMap);
		//
		// 判斷擦子是否碰到球
		//


		if (health[0].IsAlive() && health[0].HitEraser(&eraser)) {
			health[0].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			if(!(eraser.getD() && eraser.getG() && eraser.getO()))
				eraser.setEnergy(5);
		}
		if (health[1].IsAlive() && health[1].HitEraser(&eraser)) {
			health[1].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			if (!(eraser.getD() && eraser.getG() && eraser.getO()))
				eraser.setEnergy(5);
		}
		if (health[2].IsAlive() && health[1].HitEraser(&eraser)) {
			health[2].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			if (!(eraser.getD() && eraser.getG() && eraser.getO()))
				eraser.setEnergy(5);
		}
		if (Ammo[0].IsAlive() && Ammo[0].HitEraser(&eraser)) {
			Ammo[0].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			Shoot[0].setLeft(50);
		}
		if (Ammo[1].IsAlive() && Ammo[1].HitEraser(&eraser)) {
			Ammo[1].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			Shoot[0].setLeft(50);
		}
		if (Ammo[2].IsAlive() && Ammo[2].HitEraser(&eraser)) {
			Ammo[2].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			Shoot[0].setLeft(50);
		}
		if (Ammo[3].IsAlive() && Ammo[3].HitEraser(&eraser)) {
			Ammo[3].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			Shoot[0].setLeft(50);
		}
		if (Ammo[4].IsAlive() && Ammo[4].HitEraser(&eraser)) {
			Ammo[4].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			Shoot[0].setLeft(50);
		}


		if (coin[0].IsAlive() && coin[0].HitEraser(&eraser)) {
			coin[0].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			coin[0].setLeft(1);
		}

		if (coin[1].IsAlive() && coin[1].HitEraser(&eraser)) {
			coin[1].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			coin[0].setLeft(1);
		}
		if (coin[2].IsAlive() && coin[2].HitEraser(&eraser)) {
			coin[2].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			coin[0].setLeft(1);
		}
		if (coin[3].IsAlive() && coin[3].HitEraser(&eraser)) {
			coin[3].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			coin[0].setLeft(1);
		}
		if (coin[4].IsAlive() && coin[4].HitEraser(&eraser)) {
			coin[4].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			coin[0].setLeft(1);
		}
		if (coin[5].IsAlive() && coin[5].HitEraser(&eraser)) {
			coin[5].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			coin[0].setLeft(1);
		}
		if (coin[6].IsAlive() && coin[6].HitEraser(&eraser)) {
			coin[6].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			coin[0].setLeft(1);
		}
		if (coin[7].IsAlive() && coin[7].HitEraser(&eraser)) {
			coin[7].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			coin[0].setLeft(1);
		}
		if (coin[8].IsAlive() && coin[8].HitEraser(&eraser)) {
			coin[8].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			coin[0].setLeft(1);
		}
		if (coin[9].IsAlive() && coin[9].HitEraser(&eraser)) {
			coin[9].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			coin[0].setLeft(1);
		}
		if (coin[10].IsAlive() && coin[10].HitEraser(&eraser)) {
			coin[10].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			coin[0].setLeft(1);
		}
		if (coin[11].IsAlive() && coin[11].HitEraser(&eraser)) {
			coin[11].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			coin[0].setLeft(1);
		}
		if (coin[12].IsAlive() && coin[12].HitEraser(&eraser)) {
			coin[12].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			coin[0].setLeft(1);
		}
		if (coin[13].IsAlive() && coin[13].HitEraser(&eraser)) {
			coin[13].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			coin[0].setLeft(1);
		}
		if (coin[14].IsAlive() && coin[14].HitEraser(&eraser)) {
			coin[14].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			coin[0].setLeft(1);
		}
		if (coin[15].IsAlive() && coin[15].HitEraser(&eraser)) {
			coin[15].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			coin[0].setLeft(1);
		}
		if (coin[16].IsAlive() && coin[16].HitEraser(&eraser)) {
			coin[16].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			coin[0].setLeft(1);
		}
		if (coin[17].IsAlive() && coin[17].HitEraser(&eraser)) {
			coin[17].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			coin[0].setLeft(1);
		}
		if (coin[18].IsAlive() && coin[18].HitEraser(&eraser)) {
			coin[18].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_EAT);
			coin[0].setLeft(1);
		}
		for (int num = 0; num <= NUMSHOOT; num++) {
			if (BOSS[0].IsAlive() && ((BOSS[0].HitEraser(&eraser) && eraser.isAttacking())|| Shoot[num].hitBOSS(&BOSS[0]) ) && hits == 0)  {
				enemyHealth1 += 1;
				if (enemyHealth1 == 40) {
					BOSS[0].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}
			if (Jball[0].IsAlive() && ((Jball[0].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitJBall(&Jball[0])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					Jball[0].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}
			if (Jball[1].IsAlive() && ((Jball[1].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitJBall(&Jball[1])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					Jball[1].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}
			if (Jball[2].IsAlive() && ((Jball[2].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitJBall(&Jball[3])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					Jball[2].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}
			if (Jball[3].IsAlive() && ((Jball[3].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitJBall(&Jball[3])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					Jball[3].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}
			if (Jball[4].IsAlive() && ((Jball[4].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitJBall(&Jball[4])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					Jball[4].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}
			if (Jball[5].IsAlive() && ((Jball[5].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitJBall(&Jball[5])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					Jball[5].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}
			if (Jball[6].IsAlive() && ((Jball[6].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitJBall(&Jball[6])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					Jball[6].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}
			if (Jball[7].IsAlive() && ((Jball[7].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitJBall(&Jball[7])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					Jball[7].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}
			if (Jball[8].IsAlive() && ((Jball[8].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitJBall(&Jball[8])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					Jball[8].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}
			if (Jball[9].IsAlive() && ((Jball[9].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitJBall(&Jball[9])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					Jball[9].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}
			if (Jball[10].IsAlive() && ((Jball[10].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitJBall(&Jball[10])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					Jball[10].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}
			if (Jball[11].IsAlive() && ((Jball[11].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitJBall(&Jball[11])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					Jball[11].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}
			if (Jball[12].IsAlive() && ((Jball[12].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitJBall(&Jball[12])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					Jball[12].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}
			if (Jball[13].IsAlive() && ((Jball[13].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitJBall(&Jball[13])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					Jball[13].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}
			if (Jball[14].IsAlive() && ((Jball[14].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitJBall(&Jball[1])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					Jball[0].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}
			if (Jball[15].IsAlive() && ((Jball[15].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitJBall(&Jball[15])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					Jball[15].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}
			if (Jball[16].IsAlive() && ((Jball[16].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitJBall(&Jball[16])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					Jball[16].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}


			if (ball[0].IsAlive() &&( (ball[0].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[0])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[0].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}
			if (ball[1].IsAlive() && ((ball[1].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[1])) && hits == 0) {
				enemyHealth2 += 1;

				if (enemyHealth2 == 5) {
					ball[1].SetIsAlive(false);
					enemyHealth2 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[2].IsAlive() && ((ball[2].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[2])) && hits == 0) {

				enemyHealth3 += 1;
				if (enemyHealth3 == 5) {
					ball[2].SetIsAlive(false);
					enemyHealth3 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[3].IsAlive() && ((ball[3].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[3])) && hits == 0) {
				enemyHealth4 += 1;
				if (enemyHealth4 == 5) {
					enemyHealth4 = 0;

					ball[3].SetIsAlive(false);
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[4].IsAlive() && ((ball[4].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[4])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[4].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[5].IsAlive() && ((ball[5].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[5])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[5].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[6].IsAlive() && ((ball[6].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[6])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[6].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[7].IsAlive() && ((ball[7].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[7])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[7].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[8].IsAlive() && ((ball[8].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[8]) )&& hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[8].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[9].IsAlive() && ((ball[9].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[9])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[9].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[10].IsAlive() && ((ball[10].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[10]) )&& hits == 0) {

				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[10].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[11].IsAlive() && ((ball[11].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[11]) )&& hits == 0) {

				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[11].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[12].IsAlive() && ((ball[12].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[12]) )&& hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[12].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[13].IsAlive() && ((ball[13].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[13]) )&& hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[13].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[14].IsAlive() && ((ball[14].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[14])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[14].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[15].IsAlive() && ((ball[15].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[15])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[15].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[16].IsAlive() && ((ball[16].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[16])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[16].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[17].IsAlive() && ((ball[17].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[17])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[17].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[18].IsAlive() && ((ball[18].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[18])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[18].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[19].IsAlive() && ((ball[19].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[19])) && hits == 0){
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[19].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[20].IsAlive() && ((ball[20].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[20])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[20].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[21].IsAlive() && ((ball[21].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[21])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[21].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[22].IsAlive() && ((ball[22].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[22])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[22].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}
			if (ball[23].IsAlive() && ((ball[23].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[23])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[23].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[24].IsAlive() && ((ball[24].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[24])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[24].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;

			}
			if (ball[25].IsAlive() && ((ball[25].HitEraser(&eraser) && eraser.isAttacking()) || Shoot[num].hitBall(&ball[25])) && hits == 0) {
				enemyHealth1 += 1;
				if (enemyHealth1 == 5) {
					ball[25].SetIsAlive(false);
					enemyHealth1 = 0;
				}
				CAudio::Instance()->Play(AUDIO_HIT);
				hits_left.Add(-1);
				hits = 1;
			}
		}
		if (BOSS[0].IsAlive() && BOSS[0].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (Jball[0].IsAlive() && Jball[0].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (Jball[1].IsAlive() && Jball[1].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (Jball[2].IsAlive() && Jball[2].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (Jball[3].IsAlive() && Jball[3].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (Jball[4].IsAlive() && Jball[4].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (Jball[5].IsAlive() && Jball[5].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (Jball[6].IsAlive() && Jball[6].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (Jball[7].IsAlive() && Jball[7].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (Jball[8].IsAlive() && Jball[8].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (Jball[9].IsAlive() && Jball[9].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (Jball[10].IsAlive() && Jball[10].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (Jball[11].IsAlive() && Jball[11].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (Jball[12].IsAlive() && Jball[12].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (Jball[13].IsAlive() && Jball[13].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (Jball[14].IsAlive() && Jball[14].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (Jball[15].IsAlive() && Jball[15].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (Jball[16].IsAlive() && Jball[16].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}


		if (ball[0].IsAlive() && ball[0].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[1].IsAlive() && ball[1].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[2].IsAlive() && ball[2].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[3].IsAlive() && ball[3].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[4].IsAlive() && ball[4].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[5].IsAlive() && ball[5].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[6].IsAlive() && ball[6].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[7].IsAlive() && ball[7].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[8].IsAlive() && ball[8].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[9].IsAlive() && ball[9].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[10].IsAlive() && ball[10].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[11].IsAlive() && ball[11].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[12].IsAlive() && ball[12].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[13].IsAlive() && ball[13].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[14].IsAlive() && ball[14].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[14].IsAlive() && ball[14].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[15].IsAlive() && ball[15].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[16].IsAlive() && ball[16].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[17].IsAlive() && ball[17].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[18].IsAlive() && ball[18].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[19].IsAlive() && ball[19].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[20].IsAlive() && ball[20].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[21].IsAlive() && ball[21].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[22].IsAlive() && ball[22].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[23].IsAlive() && ball[23].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[24].IsAlive() && ball[24].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}
		if (ball[25].IsAlive() && ball[25].HurtEraser(&eraser)) {
			CAudio::Instance()->Play(AUDIO_HURT);
			eraser.setHurt(-1);
			eraser.setHurtCount();
		}

		if ((!Jball[0].IsAlive() && !Jball[1].IsAlive() && !Jball[2].IsAlive() && !Jball[3].IsAlive() && !Jball[4].IsAlive() && !Jball[5].IsAlive() && !Jball[6].IsAlive() && !Jball[7].IsAlive() && !Jball[8].IsAlive() && !Jball[9].IsAlive() && !Jball[10].IsAlive() && !Jball[11].IsAlive() && !Jball[12].IsAlive())&&gameMap.getLevel()==5)
		{
			eraser.SetXY(288, -18 * 64);
			gameMap.SetMapXY(-64, 1676 - 18 * 64);
			gameMap.setLevel();
			gameMap.changeLevel();
			GotoGameState(GAME_STATE_2);
		}

		if (eraser.hitGoal1(&gameMap) == TRUE) {
			//CAudio::Instance()->Play(AUDIO_END);			// 撥放 WAVE
			if (gameMap.getLevel() == 6) {
			eraser.SetXY(288, -18*64);
			gameMap.SetMapXY(-64, 1676-18*64);

			}
			else {
				eraser.SetXY(288, 0);
				gameMap.SetMapXY(-64, 1676);

			}
			gameMap.setLevel();
			gameMap.changeLevel();
			GotoGameState(GAME_STATE_2);
		}
		if (BOSS[0].IsAlive() == false && gameMap.getLevel()==8) {
			gameMap.restart();
			eraser.setRestart(true);
			GotoGameState(GAME_STATE_OVER);
		}
		if (eraser.reLevel(&gameMap) == TRUE) {
			eraser.SetXY(288, 0);
			gameMap.SetMapXY(-64, 1676);
			gameMap.JumpLevel(1);
			gameMap.changeLevel();
			GotoGameState(GAME_STATE_2);
		}
		if (eraser.getEnergy() == 0) {
			eraser.SetAlive(false);
		}
		if (eraser.isAlive() == FALSE) {
			eraser.SetXY(288, 0);
			eraser.setEnergy(5);
			if (gameMap.getLevel() == 6) {
				eraser.SetXY(288, -18 * 64);
				gameMap.SetMapXY(-64, 1676 - 18 * 64);

			}
			else {
				eraser.SetXY(288, 0);
				gameMap.SetMapXY(-64, 1676);

			}
			GotoGameState(GAME_STATE_DEAD);
		}
		if (coin[0].getLeft() >= 30) {
			Lives.Add(1);
			eraser.lifeLeft(1);
			coin[0].setLeft(-30);
		}

		gameMap.OnMove();

		//
		// 若剩餘碰撞次數為0，則跳到Game Over狀態
		//


//
// 移動彈跳的球
//
//bball.OnMove();
	}

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
		//
		// 開始載入資料
		//
		int i;
		for (i = 0; i < NUMBALLS; i++) {
			ball[i].LoadBitmap();								// 載入第i個球的圖形*/
			coin[i].LoadBitmap();
			health[i].LoadBitmap();
			BOSS[i].LoadBitmap();
			Ammo[i].LoadBitmap();
			Jball[i].LoadBitmap();

		}
		for (i = 0; i < NUMBALLS; i++) {
			Shoot[i].LoadBitmap();
		}

		eraser.LoadBitmap();
		eraser.SetAttack(FALSE);
		eraser.isJump(FALSE);

		energyBar.AddBitmap(IDB_energy1);
		Lives_P.AddBitmap(IDB_Lives_P,RGB(0,0,0));
		coin_P.AddBitmap(IDB_Coin1);
		Gun_P.AddBitmap(IDB_Rifle, RGB(181, 230, 29));
		gameMap.LoadBitmap();
		gameMap.OnShow();
		background.LoadBitmap(IDB_Map);					// 載入背景的圖形

		//
		// 完成部分Loading動作，提高進度
		//
		ShowInitProgress(50);
		Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 繼續載入其他資料
		//
		help.LoadBitmap(IDB_HELP, RGB(255, 255, 255));				// 載入說明的圖形
		corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
		//bball.LoadBitmap();										// 載入圖形
		Lives.LoadBitmap();
		CAudio::Instance()->Load(AUDIO_DING, "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
		CAudio::Instance()->Load(AUDIO_LAKE, "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
		CAudio::Instance()->Load(AUDIO_NTUT, "sounds\\ntut.mid");	// 載入編號2的聲音ntut.mid
		CAudio::Instance()->Load(AUDIO_INTRO, "sounds\\intro.mp3");	// 載入進入關卡聲音
		CAudio::Instance()->Load(AUDIO_HIT, "sounds\\hit.mp3");		// 載入攻擊聲音
		CAudio::Instance()->Load(AUDIO_EAT, "sounds\\eat.mp3");		// 載入吃的聲音
		CAudio::Instance()->Load(AUDIO_HURT, "sounds\\hurt.mp3");	// 載入受傷的聲音
		CAudio::Instance()->Load(AUDIO_GUN, "sounds\\gun.mp3");	// 載入受傷的聲音





		//
		// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
		//
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_ATTACK = 0x5A; // keyboard的Z按鍵
		const char KEY_JUMP = 0x58; // keyboard的X按鍵
		const char KEY_L1 = 0x31; // keyboard的1按鍵
		const char KEY_L2 = 0x32; // keyboard的2按鍵
		const char KEY_L3 = 0x33; // keyboard的3按鍵
		const char KEY_L4 = 0x34; // keyboard的4按鍵
		const char KEY_L5 = 0x35; // keyboard的5按鍵
		const char KEY_L6 = 0x36; // keyboard的6按鍵
		const char KEY_L7 = 0x37; // keyboard的7按鍵
		const char KEY_L8 = 0x38; // keyboard的8按鍵
		const char KEY_J = 74; // keyboard的J按鍵
		const char KEY_U = 85; // keyboard的U按鍵
		const char KEY_M = 77; // keyboard的M按鍵
		const char KEY_P = 80; // keyboard的P按鍵
		const char KEY_G = 71; // keyboard的G按鍵
		const char KEY_O = 79; // keyboard的O按鍵
		const char KEY_D = 68; // keyboard的D按鍵
		const char KEY_F = 70; // keyboard的F按鍵
		const char KEY_L = 76; // keyboard的L按鍵
		const char KEY_Y = 89; // keyboard的Y按鍵
		const char KEY_FLY = 67; // keyboard的C按鍵


		const char KEY_ESC = 27; // keyboard的X按鍵


		const char KEY_WEAPONA = 0x41; // keyboard的A按鍵
		const char KEY_WEAPONS = 0x53; // keyboard的S按鍵


		if (nChar == KEY_RIGHT) {
			eraser.SetMovingRight(true);
			eraser.SetFaceRight(true);
			eraser.SetFaceLeft(false);
			for (int num = 0; num <= NUMSHOOT; num++) {
				Shoot[num].setFacingLeft(false);
				Shoot[num].setFacingRight(true);
			}
		}
		if (nChar == KEY_LEFT) {
			eraser.SetMovingLeft(true);
			eraser.SetFaceLeft(true);
			eraser.SetFaceRight(false);
			for (int num = 0; num <= NUMSHOOT; num++) {
				Shoot[num].setFacingLeft(true);
				Shoot[num].setFacingRight(false);
			}
		}
		if (nChar == KEY_JUMP)
			eraser.isJump(true);
		if (nChar == KEY_UP)
			eraser.SetMovingUp(true);
		if (nChar == KEY_DOWN)
			eraser.SetMovingDown(true);
		if (nChar == KEY_ATTACK && eraser.isitStick()) {
				eraser.SetAttack(true);
		}

		if (nChar == KEY_ATTACK && eraser.isitRifle()&& Shoot[0].getLeft()!=0){
			Shoot[numberShoot].SetIsAlive(true);
			CAudio::Instance()->Play(AUDIO_GUN);			// 撥放 WAVE

			Shoot[0].setLeft(-1);
			if (eraser.isFacing() == 0) {
				Shoot[numberShoot].SetXY(eraser.GetX2(), ((eraser.GetY2() + eraser.GetY1()) / 2)+17);
			}
			else if (eraser.isFacing() == 1) {
				Shoot[numberShoot].SetXY(eraser.GetX1(), ((eraser.GetY2() + eraser.GetY1()) / 2) +17);
			}
			Shoot[numberShoot].SetDelay(0);
			numberShoot++;
			if (numberShoot >= NUMSHOOT) {
				numberShoot = 0;
			}
		}


		if (nChar == KEY_WEAPONA)
			eraser.SetWeaponA(true);
		if (nChar == KEY_WEAPONS)
			eraser.SetWeaponS(true);
		if (nChar == KEY_J) {	
			gameMap.setJ(true);
		}
		if (nChar == KEY_U && gameMap.getJ() ) {
			gameMap.setU(true);
		}
		if (nChar == KEY_M && gameMap.getJ() && gameMap.getU()) {
			gameMap.setM(true);
		}
		if (nChar == KEY_P && gameMap.getJ() && gameMap.getU() && gameMap.getM()) {
				gameMap.setP(true);
		}
		if (nChar == KEY_G) {
			eraser.setG(true);
		}
		if (nChar == KEY_O && eraser.getG()) {
			eraser.setO(true);
		}
		if (nChar == KEY_D && eraser.getG() && eraser.getO()) {
			eraser.lifeLeft(99);
			eraser.setEnergy(99999);
			Lives.SetInteger(99);
			Shoot[0].setLeft(999);
			eraser.setG(false);
			eraser.setO(false);
			eraser.setD(false);
		}

		if (nChar == KEY_F) {
			eraser.setF(true);
		}
		if (nChar == KEY_L && eraser.getF()) {
			eraser.setL(true);
		}
		if (nChar == KEY_Y && eraser.getL() && eraser.getF()) {
			eraser.setY(true);
		}
		if (nChar == KEY_FLY && eraser.getL() && eraser.getF() && eraser.getY()) {
			eraser.setFLY(true);
		}
		if (nChar == KEY_L1 && gameMap.getJ() && gameMap.getU() && gameMap.getM() && gameMap.getP()) {
				gameMap.SetMapXY(-64, 1676);
				gameMap.JumpLevel(1);
				gameMap.changeLevel();
				GotoGameState(GAME_STATE_2);	
		}
		if (  nChar == KEY_L2 && gameMap.getJ() && gameMap.getU() && gameMap.getM() && gameMap.getP()) {
				gameMap.SetMapXY(-64, 1676);
				gameMap.JumpLevel(2);
				gameMap.changeLevel();
				GotoGameState(GAME_STATE_2);
			
		}
		if (nChar == KEY_L3 && gameMap.getJ() && gameMap.getU() && gameMap.getM() && gameMap.getP()) {
			gameMap.SetMapXY(-64, 1676);
			gameMap.JumpLevel(3);
			gameMap.changeLevel();
			GotoGameState(GAME_STATE_2);
		}
		if (nChar == KEY_L4 && gameMap.getJ() && gameMap.getU() && gameMap.getM() && gameMap.getP()) {
			gameMap.SetMapXY(-64, 1676);
			gameMap.JumpLevel(4);
			gameMap.changeLevel();
			GotoGameState(GAME_STATE_2);
		}
		if (nChar == KEY_L5 && gameMap.getJ() && gameMap.getU() && gameMap.getM() && gameMap.getP()) {
			gameMap.SetMapXY(-64, 1676);
			gameMap.JumpLevel(5);
			gameMap.changeLevel();
			GotoGameState(GAME_STATE_2);
		}
		if (nChar == KEY_L6 && gameMap.getJ() && gameMap.getU() && gameMap.getM() && gameMap.getP()) {
			eraser.SetXY(288, -18 * 64);
			gameMap.SetMapXY(-64, 1676-18*64);			
			gameMap.JumpLevel(6);
			gameMap.changeLevel();
			GotoGameState(GAME_STATE_2);
		}
		if (nChar == KEY_L7 && gameMap.getJ() && gameMap.getU() && gameMap.getM() && gameMap.getP()) {
			gameMap.SetMapXY(-64, 1676);
			gameMap.JumpLevel(7);
			gameMap.changeLevel();
			GotoGameState(GAME_STATE_2);
		}
		if (nChar == KEY_L8 && gameMap.getJ() && gameMap.getU() && gameMap.getM() && gameMap.getP()) {
			gameMap.SetMapXY(-64, 1676);
			gameMap.JumpLevel(8);
			gameMap.changeLevel();
			GotoGameState(GAME_STATE_2);
		}
		if (nChar == KEY_ESC)
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
	}
	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_ATTACK = 0x5A; // keyboard的Z按鍵
		const char KEY_JUMP = 0x58; // keyboard的X按鍵
		const char KEY_FLY = 67; // keyboard的C按鍵

		const char KEY_WEAPONA = 0x41; // keyboard的A按鍵
		const char KEY_WEAPONS = 0x53; // keyboard的S按鍵


		if (nChar == KEY_RIGHT) {
			eraser.SetMovingRight(false);
			eraser.SetFaceRight(true);
			eraser.SetFaceLeft(false);

		}
		if (nChar == KEY_LEFT) {
			eraser.SetMovingLeft(false);
			eraser.SetFaceLeft(true);
			eraser.SetFaceRight(false);

		}

		if (nChar == KEY_JUMP)
			eraser.isJump(false);
		if (nChar == KEY_UP)
			eraser.SetMovingUp(false);
		if (nChar == KEY_DOWN)
			eraser.SetMovingDown(false);
		if (nChar == KEY_ATTACK) {
			eraser.SetAttack(false);
			hits = 0;
		}
		if (nChar == KEY_WEAPONA)
			eraser.SetWeaponA(true);
		if (nChar == KEY_WEAPONS)
			eraser.SetWeaponS(true);
		if (nChar == KEY_FLY) {
			eraser.setFLY(false);
		}
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		//eraser.SetMovingLeft(true);
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		//eraser.SetMovingLeft(false);
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		//eraser.SetMovingRight(true);
	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		//eraser.SetMovingRight(false);
	}

	void CGameStateRun::OnShow()
	{
		background.ShowBitmap();
		gameMap.OnShow();
		//
		//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
		//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
		//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
		//
		//
		//  貼上背景圖、撞擊數、球、擦子、彈跳的球
		//
		//help.ShowBitmap();					// 貼上說明圖
		int num;
		for (num = 0; num <= 28; num++) {
			ball[num].OnShow(&gameMap);				// 貼上第i號球*/
			Jball[num].OnShow(&gameMap);				// 貼上第i號球*/
		}
		for (num = 0; num <= 25; num++) {
			coin[num].OnShow(&gameMap);				// 貼上第i號球*/
		}

		for (num = 0; num <= 10; num++) {
			health[num].OnShow(&gameMap);				// 貼上第i號球*/
			BOSS[num].OnShow(&gameMap);				// 貼上第i號球*/
			Ammo[num].OnShow(&gameMap);				// 貼上第i號球*/
		}

		for (num = 0; num <=20; num++) {
			Shoot[num].OnShow(&gameMap);
		}

		//bball.OnShow();						// 貼上彈跳的球
		eraser.OnShow(&gameMap);					// 貼上擦子
		energyBar.SetTopLeft(560, 0);
		if(eraser.getEnergy()==5){
			energyBar.deleteBMP();
			energyBar.AddBitmap(IDB_energy1);

			energyBar.OnShow();					// 貼上5命
		}
		else if (eraser.getEnergy() == 4) {
			energyBar.deleteBMP();
			energyBar.AddBitmap(IDB_energy2);
			energyBar.OnShow();					// 貼上4命
		}
		else if (eraser.getEnergy() == 3) {
			energyBar.deleteBMP();
			energyBar.AddBitmap(IDB_energy3);
			energyBar.OnShow();					// 貼上3命
		}
		else if (eraser.getEnergy() == 2) {
			energyBar.deleteBMP();
			energyBar.AddBitmap(IDB_energy4);
			energyBar.OnShow();					// 貼上2命
		}
		else if (eraser.getEnergy() == 1) {
			energyBar.deleteBMP();
			energyBar.AddBitmap(IDB_energy5);
			energyBar.OnShow();					// 貼上1命
		}
		else {
			energyBar.deleteBMP();
			energyBar.AddBitmap(IDB_energy6);
			energyBar.OnShow();					// 貼上1命
		}

		Lives_P.SetTopLeft(572, 453);
		Lives_P.OnShow();					// 貼上LIVES字樣
		coin_P.SetTopLeft(572,32 );
		coin_P.OnShow();					// 貼上LIVES字樣
		Gun_P.SetTopLeft(10, 10);
		Gun_P.OnShow();					// 貼上LIVES字樣
		Lives.ShowBitmap();
		//
		//  貼上左上及右下角落的圖
		//


	}
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲第二關畫面
	/////////////////////////////////////////////////////////////////////////////

	CGameState2::CGameState2(CGame* g)
		: CGameState(g)
	{
	}

	void CGameState2::OnMove()
	{
		counter--;
		if (counter < 0) {
			GotoGameState(GAME_STATE_RUN);
		}
	}

	void CGameState2::OnBeginState()
	{
		counter = 30 * 2; // 2 seconds
	}

	void CGameState2::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
		//
		// 開始載入資料
		//
		finish.AddBitmap(IDB_FINISH);

		//
		// 最終進度為100%
		//

		ShowInitProgress(100);

	}

	void CGameState2::OnShow()
	{
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
		CFont f, * fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str, "Level %d", gameMap.getLevel());
		pDC->TextOut(240, 210, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC

	}


	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateDead::CGameStateDead(CGame* g)
		: CGameState(g)
	{
	}

	void CGameStateDead::OnMove()
	{
		counter--;
		if (counter < 0 && eraser.getLife()<=0) {
			gameMap.restart();
			eraser.setRestart(true);
			CAudio::Instance()->Stop(AUDIO_END);			// 撥放 WAVE
			CAudio::Instance()->Play(AUDIO_MENU, true);			// 撥放 WAVE
			GotoGameState(GAME_STATE_INIT);
		}
		else if ((counter < 0 && eraser.getLife() > 0)) {
			eraser.setHurt(5);
			eraser.lifeLeft(-1);
			GotoGameState(GAME_STATE_RUN);

		}
	}

	void CGameStateDead::OnBeginState()
	{

		counter = 30 * 2; // 5 seconds
	}

	void CGameStateDead::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
		//
		// 開始載入資料
		//

		//
		// 最終進度為100%
		//

		ShowInitProgress(100);
		gameMap.LoadBitmap();
	}

	void CGameStateDead::OnShow()
	{
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
		CFont f, * fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str, "YOU DIED ! (%d)", counter / 30);
		pDC->TextOut(240, 210, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC

	}


	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////


	CGameStateAbout::CGameStateAbout(CGame* g)
		: CGameState(g)
	{
	}

	void CGameStateAbout::OnMove()
	{
	}

	void CGameStateAbout::OnBeginState()
	{
	}
	void CGameStateAbout::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (nChar != NULL) {
			GotoGameState(GAME_STATE_INIT);
		}
	}


	void CGameStateAbout::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
		//
		// 開始載入資料
		//
		About.AddBitmap(IDB_About);

		//
		// 最終進度為100%
		//

		ShowInitProgress(100);

	}

	void CGameStateAbout::OnShow()
	{
		About.OnShow();


	}
	/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////


	CGameStateConfiguration::CGameStateConfiguration(CGame* g)
		: CGameState(g)
	{
	}

	void CGameStateConfiguration::OnMove()
	{
	}

	void CGameStateConfiguration::OnBeginState()
	{
	}
	void CGameStateConfiguration::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (nChar != NULL) {
			GotoGameState(GAME_STATE_INIT);
		}
	}


	void CGameStateConfiguration::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
		//
		// 開始載入資料
		//
		Configuration.AddBitmap(IDB_Configuration);

		//
		// 最終進度為100%
		//

		ShowInitProgress(100);

	}

	void CGameStateConfiguration::OnShow()
	{
		Configuration.OnShow();


	}
}