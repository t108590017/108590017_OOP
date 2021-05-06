#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame* g)
		: CGameState(g)
	{

	}

	void CGameStateInit::OnInit()
	{
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
		//
		// �}�l���J���
		//
		menu.LoadBitmap(IDB_MENU);
		Choose.LoadBitmap(IDB_Choose, RGB(181, 230, 29));
		CAudio::Instance()->Load(AUDIO_MENU, "sounds\\menu.mp3");	// ���J�s��3���n��menu.mp3
		int x_pos = 210;
		int y_pos = 312;
		x = x_pos;
		y = y_pos;
		CAudio::Instance()->Play(AUDIO_MENU, true);			// ���� WAVE

		Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
		//
		// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
		//


	}


	void CGameStateInit::OnBeginState()
	{

	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{

		const char KEY_ESC = 27;
		const char KEY_ENTER = 13;
		const char KEY_UP = 0x26;	// keyboard�W�b�Y
		const char KEY_DOWN = 0x28; // keyboard�U�b�Y
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
			GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
		else if (nChar == KEY_ENTER && y == 420)
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
		else if (nChar == KEY_ESC)								// Demo �����C������k
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
	}

	void CGameStateInit::OnKeyDown(UINT, UINT, UINT)
	{

	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		//GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
	}

	void CGameStateInit::OnShow()
	{

		//
		// �K�Wlogo
		//
		menu.SetTopLeft(0, 0);
		menu.ShowBitmap();
		Choose.SetTopLeft(x, y);
		Choose.ShowBitmap();
		//
		// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
		//
		CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
		CFont f, * fp;
		f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f


		/*pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		pDC->TextOut(120, 220, "Please click mouse or press SPACE to begin.");
		pDC->TextOut(5, 395, "Press Ctrl-F to switch in between window mode and full screen mode.");
		if (ENABLE_GAME_PAUSE)
			pDC->TextOut(5, 425, "Press Ctrl-Q to pause the Game.");
		pDC->TextOut(5, 455, "Press Alt-F4 or ESC to Quit.");*/
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame* g)
		: CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{
		counter--;
		if (counter < 0) {
			CAudio::Instance()->Stop(AUDIO_END);			// ���� WAVE
			CAudio::Instance()->Play(AUDIO_MENU, true);			// ���� WAVE

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
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
		//
		// �}�l���J���
		//
		CAudio::Instance()->Load(AUDIO_END, "sounds\\End.mp3");	// ���J�s��3���n��menu.mp3
		finish.AddBitmap(IDB_FINISH);

		//
		// �̲׶i�׬�100%
		//

		ShowInitProgress(100);

	}

	void CGameStateOver::OnShow()
	{
		finish.OnShow();
		/*CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
		CFont f, * fp;
		f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
		sprintf(str, "Game Over ! (%d)", counter / 30);
		pDC->TextOut(240, 210, str);
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC*/

	}

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
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
		//for (int i = 0; i < NUMBALLS; i++) {				// �]�w�y���_�l�y��
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
		background.SetTopLeft(0, 0);				// �]�w�I�����_�l�y��
		help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��
		hits_left.SetInteger(HITS_LEFT);					// ���w�ѤU��������
		hits_left.SetTopLeft(HITS_LEFT_X, HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
		CAudio::Instance()->Stop(AUDIO_MENU);			// ���� WAVE

		CAudio::Instance()->Play(AUDIO_INTRO, false);		// ���� WAVE
	}

	void CGameStateRun::OnMove()							// ���ʹC������
	{
		//
		// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
		//
		// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
		//
		// ���ʭI���Ϫ��y��
		//
		//if (background.Top() > SIZE_Y)
		//	background.SetTopLeft(60, -background.Height());
		//background.SetTopLeft(background.Left(), background.Top() + 1);
		//
		// ���ʲy
		//
		int i;
		for (i = 0; i < NUMBALLS; i++)
			ball[i].OnMove();
		//
		// �������l
		//
		eraser.OnMove(&gameMap);
		//
		// �P�_���l�O�_�I��y
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
			//CAudio::Instance()->Play(AUDIO_END);			// ���� WAVE
			eraser.SetXY(288, 1676);
			gameMap.SetMapXY(288, 1676);
			gameMap.setLevel();
			gameMap.changeLevel();
			GotoGameState(GAME_STATE_2);
		}
		gameMap.OnMove();

		//
		// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
		//


//
// ���ʼu�����y
//
//bball.OnMove();
	}

	void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
	{
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
		//
		// �}�l���J���
		//
		int i;
		for (i = 0; i < NUMBALLS; i++)
			ball[i].LoadBitmap();								// ���J��i�Ӳy���ϧ�*/
		eraser.LoadBitmap();
		eraser.SetXY(0, 1356);

		energyBar.AddBitmap(IDB_energy1);
		gameMap.LoadBitmap();
		background.LoadBitmap(IDB_Map);					// ���J�I�����ϧ�

		//
		// ��������Loading�ʧ@�A�����i��
		//
		ShowInitProgress(50);
		Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
		//
		// �~����J��L���
		//
		help.LoadBitmap(IDB_HELP, RGB(255, 255, 255));				// ���J�������ϧ�
		corner.LoadBitmap(IDB_CORNER);							// ���J�����ϧ�
		//bball.LoadBitmap();										// ���J�ϧ�

		hits_left.LoadBitmap();
		CAudio::Instance()->Load(AUDIO_DING, "sounds\\ding.wav");	// ���J�s��0���n��ding.wav
		CAudio::Instance()->Load(AUDIO_LAKE, "sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
		CAudio::Instance()->Load(AUDIO_NTUT, "sounds\\ntut.mid");	// ���J�s��2���n��ntut.mid
		CAudio::Instance()->Load(AUDIO_INTRO, "sounds\\intro.mp3");	// ���J�s��2���n��ntut.mid
		CAudio::Instance()->Load(AUDIO_HIT, "sounds\\hit.mp3");	// ���J�s��2���n��ntut.mid


		//
		// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
		//
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		const char KEY_DOWN = 0x28; // keyboard�U�b�Y
		const char KEY_ATTACK = 0x5A; // keyboard��Z����
		const char KEY_JUMP = 0x58; // keyboard��X����

		const char KEY_WEAPONA = 0x41; // keyboard��A����
		const char KEY_WEAPONS = 0x53; // keyboard��S����
		const char KEY_WEAPOND = 0x44; // keyboard��D����
		const char KEY_WEAPONF = 0x46; // keyboard��F����

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
		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		const char KEY_DOWN = 0x28; // keyboard�U�b�Y
		const char KEY_ATTACK = 0x5A; // keyboard��Z����
		const char KEY_JUMP = 0x58; // keyboard��X����

		const char KEY_WEAPONA = 0x41; // keyboard��A����
		const char KEY_WEAPONS = 0x53; // keyboard��S����
		const char KEY_WEAPOND = 0x44; // keyboard��D����
		const char KEY_WEAPONF = 0x46; // keyboard��F����

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

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{
		eraser.SetMovingLeft(true);
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
		eraser.SetMovingLeft(false);
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
		// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{
		eraser.SetMovingRight(true);
	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
		eraser.SetMovingRight(false);
	}

	void CGameStateRun::OnShow()
	{
		gameMap.OnShow();

		//
		//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
		//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
		//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
		//
		//
		//  �K�W�I���ϡB�����ơB�y�B���l�B�u�����y
		//
		//help.ShowBitmap();					// �K�W������
		//hits_left.ShowBitmap();
		ball[0].OnShow();				// �K�W��i���y*/
		ball[1].OnShow();
		ball[2].OnShow();
		ball[3].OnShow();

		//bball.OnShow();						// �K�W�u�����y
		eraser.OnShow(&gameMap);					// �K�W���l
		energyBar.SetTopLeft(500, 0);
		energyBar.OnShow();					// �K�W�R
		//
		//  �K�W���W�Υk�U��������
		//


	}
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C���ĤG���e��
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
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
		//
		// �}�l���J���
		//
		finish.AddBitmap(IDB_FINISH);

		//
		// �̲׶i�׬�100%
		//

		ShowInitProgress(100);

	}

	void CGameState2::OnShow()
	{
		CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
		CFont f, * fp;
		f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
		sprintf(str, "Level %d",gameMap.getLevel());
		pDC->TextOut(240, 210, str);
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC

	}

}