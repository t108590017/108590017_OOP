#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"


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
		if (nChar == KEY_ENTER && y == 312)
			GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
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
		counter = 30 * 2; // 5 seconds
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
		: CGameState(g), NUMBALLS(28)
	{
		ball = new CBall[NUMBALLS];
	}

	CGameStateRun::~CGameStateRun()
	{
		delete[] ball;
	}

	void CGameStateRun::OnBeginState()
	{
		const int BALL_GAP = 90;
		const int BALL_XY_OFFSET = 45;
		const int BALL_PER_ROW = 7;
		const int HITS_LEFT = 10;
		const int HITS_LEFT_X = 590;
		const int HITS_LEFT_Y = 0;
		const int BACKGROUND_X = 0;
		const int ANIMATION_SPEED = 15;
		//for (int i = 0; i < NUMBALLS; i++) {				// 設定球的起始座標
		//int y_pos = i / BALL_PER_ROW;
		ball[0].SetXY(500, 280);
		ball[0].SetDelay(0);
		ball[0].SetIsAlive(true);
		ball[1].SetXY(100, 230);
		ball[1].SetDelay(0);
		ball[1].SetIsAlive(true);
		ball[2].SetXY(200, 150);
		ball[2].SetDelay(0);
		ball[2].SetIsAlive(true);
		ball[3].SetXY(300, 200);
		ball[3].SetDelay(0);
		ball[3].SetIsAlive(true);
		//}
		eraser.Initialize();
		background.SetTopLeft(0, 0);				// 設定背景的起始座標
		help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
		hits_left.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
		hits_left.SetTopLeft(HITS_LEFT_X, HITS_LEFT_Y);		// 指定剩下撞擊數的座標
		CAudio::Instance()->Stop(AUDIO_MENU);			// 撥放 WAVE

		CAudio::Instance()->Play(AUDIO_INTRO, false);		// 撥放 WAVE
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
		//background.SetTopLeft(background.Left(), background.Top() + 1);
		//
		// 移動球
		//
		int i;
		for (i = 0; i < NUMBALLS; i++)
			ball[i].OnMove();
		//
		// 移動擦子
		//
		eraser.OnMove(&gameMap);
		//
		// 判斷擦子是否碰到球
		//
		if (ball[0].IsAlive() && ball[0].HitEraser(&eraser) && eraser.isAttacking()) {
			enemyHealth1 += 1;
			if (enemyHealth1 == 5) {
				ball[0].SetIsAlive(false);
				enemyHealth1 = 0;
			}
			CAudio::Instance()->Play(AUDIO_HIT);
			hits_left.Add(-1);
		}
		if (ball[1].IsAlive() && ball[1].HitEraser(&eraser) && eraser.isAttacking()) {
			enemyHealth2 += 1;
			if (enemyHealth2 == 5) {
				ball[1].SetIsAlive(false);
				enemyHealth2 = 0;

			}
			CAudio::Instance()->Play(AUDIO_HIT);
			hits_left.Add(-1);
		}
		if (ball[2].IsAlive() && ball[2].HitEraser(&eraser) && eraser.isAttacking()) {
			enemyHealth3 += 1;
			if (enemyHealth3 == 5) {
				ball[2].SetIsAlive(false);
				enemyHealth3 = 0;
			}
			CAudio::Instance()->Play(AUDIO_HIT);
			hits_left.Add(-1);
		}
		if (ball[3].IsAlive() && ball[3].HitEraser(&eraser) && eraser.isAttacking()) {
			enemyHealth4 += 1;
			if (enemyHealth4 == 5) {
				enemyHealth4 = 0;

				ball[3].SetIsAlive(false);
			}
			CAudio::Instance()->Play(AUDIO_HIT);
			hits_left.Add(-1);

		}
		if (eraser.hitGoal1(&gameMap)==TRUE) {
			//CAudio::Instance()->Play(AUDIO_END);			// 撥放 WAVE
			eraser.SetXY(0, 1356);
			gameMap.SetMapXY(0, 1356);
			gameMap.setLevel();
			gameMap.changeLevel();
			GotoGameState(GAME_STATE_2);
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
		for (i = 0; i < NUMBALLS; i++)
			ball[i].LoadBitmap();								// 載入第i個球的圖形*/
		eraser.LoadBitmap();
		eraser.SetXY(0, 1356);

		energyBar.AddBitmap(IDB_energy1);
		gameMap.LoadBitmap();
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

		hits_left.LoadBitmap();
		CAudio::Instance()->Load(AUDIO_DING, "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
		CAudio::Instance()->Load(AUDIO_LAKE, "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
		CAudio::Instance()->Load(AUDIO_NTUT, "sounds\\ntut.mid");	// 載入編號2的聲音ntut.mid
		CAudio::Instance()->Load(AUDIO_INTRO, "sounds\\intro.mp3");	// 載入編號2的聲音ntut.mid
		CAudio::Instance()->Load(AUDIO_HIT, "sounds\\hit.mp3");	// 載入編號2的聲音ntut.mid


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

		const char KEY_WEAPONA = 0x41; // keyboard的A按鍵
		const char KEY_WEAPONS = 0x53; // keyboard的S按鍵
		const char KEY_WEAPOND = 0x44; // keyboard的D按鍵
		const char KEY_WEAPONF = 0x46; // keyboard的F按鍵

		if (nChar == KEY_RIGHT) {
			eraser.SetMovingRight(true);
			eraser.SetFaceRight(true);
			eraser.SetFaceLeft(false);

		}
		if (nChar == KEY_LEFT) {
			eraser.SetMovingLeft(true);
			eraser.SetFaceLeft(true);
			eraser.SetFaceRight(false);

		}
		if (nChar == KEY_JUMP)
			eraser.isJump(true);
		if (nChar == KEY_UP)
			eraser.SetMovingUp(true);
		if (nChar == KEY_DOWN)
			eraser.SetMovingDown(true);
		if (nChar == KEY_ATTACK)
			eraser.SetAttack(true);
		if (nChar == KEY_WEAPONA)
			eraser.SetWeaponA(true);
		if (nChar == KEY_WEAPONS)
			eraser.SetWeaponS(true);
		if (nChar == KEY_WEAPOND)
			eraser.SetWeaponD(true);
		if (nChar == KEY_WEAPONF)
			eraser.SetWeaponF(true);
	}
	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_ATTACK = 0x5A; // keyboard的Z按鍵
		const char KEY_JUMP = 0x58; // keyboard的X按鍵

		const char KEY_WEAPONA = 0x41; // keyboard的A按鍵
		const char KEY_WEAPONS = 0x53; // keyboard的S按鍵
		const char KEY_WEAPOND = 0x44; // keyboard的D按鍵
		const char KEY_WEAPONF = 0x46; // keyboard的F按鍵

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
		if (nChar == KEY_ATTACK)
			eraser.SetAttack(false);
		if (nChar == KEY_WEAPONA)
			eraser.SetWeaponA(true);
		if (nChar == KEY_WEAPONS)
			eraser.SetWeaponS(true);
		if (nChar == KEY_WEAPOND)
			eraser.SetWeaponD(true);
		if (nChar == KEY_WEAPONF)
			eraser.SetWeaponF(true);
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		eraser.SetMovingLeft(true);
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		eraser.SetMovingLeft(false);
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		eraser.SetMovingRight(true);
	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		eraser.SetMovingRight(false);
	}

	void CGameStateRun::OnShow()
	{
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
		//hits_left.ShowBitmap();
		ball[0].OnShow();				// 貼上第i號球*/
		ball[1].OnShow();
		ball[2].OnShow();
		ball[3].OnShow();

		//bball.OnShow();						// 貼上彈跳的球
		eraser.OnShow(&gameMap);					// 貼上擦子
		energyBar.SetTopLeft(500, 0);
		energyBar.OnShow();					// 貼上命
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
		counter = 30 * 2; // 5 seconds
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
		sprintf(str, "Level %d",gameMap.getLevel());
		pDC->TextOut(240, 210, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC

	}

}