#include "PlaneApp.h"

DECLARE(CPlaneApp)
CPlaneApp::CPlaneApp(void)
{
}


CPlaneApp::~CPlaneApp(void)
{
}
void CPlaneApp::OnCreateGame()  //  WM_CREATE
{
	// 1.  ��ʼ������
	back.InitBack(m_hIns);
	// 2.  �Գ�ʼ����ҷɻ�
	plane.InitPlayer(m_hIns);
	// 3.  �������еĶ�ʱ��
	::SetTimer(m_hMainWnd,BACK_MOVE_TIMER_ID,100,0);   //  ���Ʊ����ƶ�
	::SetTimer(m_hMainWnd,PLAYER_MOVE_TIMER_ID,1,0);   //  ������ҷɻ��ƶ�
	::SetTimer(m_hMainWnd,SEND_GUNNER_TIMER_ID,350,0);  // ������ҷɻ����ڵ�
	::SetTimer(m_hMainWnd,GUNNER_MOVE_TIMER_ID,10,0);   // �����ڵ��ƶ�
	::SetTimer(m_hMainWnd,CREATE_FOEPLANE_TIMER_ID,1000,0);
	::SetTimer(m_hMainWnd,FOEPLANE_MOVE_TIMER_ID,10,0);
	::SetTimer(m_hMainWnd,CHANGE_SHOWID_TIMER_ID,150,0);
	
}
void CPlaneApp::OnGameDraw() // WM_PAINT
{
	PAINTSTRUCT ps = {0};
	HDC hdc = ::BeginPaint(m_hMainWnd,&ps);

	HDC hMemDC = ::CreateCompatibleDC(hdc);
	HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc,380,550);
	::SelectObject(hMemDC,hBitmap)	;

	//--------------------------------------------------
	back.ShowBack(hMemDC);//  ��ʾ����
	plane.ShowPlayer(hMemDC);//  ��ʾ��ҷɻ�
	gunBox.AllGunnerShow(hMemDC);  //  ��ʾ�����ڵ�
	foeBox.AllFoePlaneShow(hMemDC);  //  ��ʾ���е��˷ɻ�
	blastBox.AllFoePlaneShow(hMemDC);  //  ��ʾ��ը�ĵ��˷ɻ�
	//---------------------------------------------------
	::BitBlt(hdc,0,0,380,550,hMemDC,0,0,SRCCOPY);

	::DeleteObject(hBitmap);
	::DeleteDC(hMemDC);
	::EndPaint(m_hMainWnd,&ps);
}
void CPlaneApp::OnGameRun(WPARAM nTimerID) // WM_TIM	ER
{
	//  �л���ը��Ч��ͼ
	if(nTimerID == CHANGE_SHOWID_TIMER_ID)
		blastBox.ChangeShowID();

	//  �������˷ɻ�
	if(nTimerID == CREATE_FOEPLANE_TIMER_ID)
		foeBox.CreateFoePlane(m_hIns);
	//  ���˷ɻ��ƶ�
	if(nTimerID == FOEPLANE_MOVE_TIMER_ID)
	{
		foeBox.AllFoePlaneMove();
		if(this->IsGameOver() == true)
		{
			//  ������ʱ��
			::KillTimer(m_hMainWnd,BACK_MOVE_TIMER_ID);   //  ���Ʊ����ƶ�
			::KillTimer(m_hMainWnd,PLAYER_MOVE_TIMER_ID);   //  ������ҷɻ��ƶ�
			::KillTimer(m_hMainWnd,SEND_GUNNER_TIMER_ID);  // ������ҷɻ����ڵ�
			::KillTimer(m_hMainWnd,GUNNER_MOVE_TIMER_ID);   // �����ڵ��ƶ�
			::KillTimer(m_hMainWnd,CREATE_FOEPLANE_TIMER_ID);
			::KillTimer(m_hMainWnd,FOEPLANE_MOVE_TIMER_ID);
			::KillTimer(m_hMainWnd,CHANGE_SHOWID_TIMER_ID);
			::MessageBox(0,"GameOver","��ʾ",MB_OK);
		}
	}
	//  �����ڵ�
	if(nTimerID == SEND_GUNNER_TIMER_ID)
		plane.SendGunner(m_hIns,gunBox);   
	//  �ڵ��ƶ�
	if(nTimerID == GUNNER_MOVE_TIMER_ID)
	{
		gunBox.AllGunnerMove();
		//  �ڵ�����˷ɻ�
		this->GunnerHitFoePlane();
	}
	//  ��ҷɻ��ƶ�
	if(nTimerID == PLAYER_MOVE_TIMER_ID)
	{
		//  �ж��Ƿ񰴷����
		if(::GetAsyncKeyState(VK_LEFT))
			plane.MovePlayer(VK_LEFT);
		if(::GetAsyncKeyState(VK_RIGHT))
			plane.MovePlayer(VK_RIGHT);
		if(::GetAsyncKeyState(VK_UP))
			plane.MovePlayer(VK_UP);
		if(::GetAsyncKeyState(VK_DOWN))
			plane.MovePlayer(VK_DOWN);
	}

	//  �����ƶ�
	if(nTimerID == BACK_MOVE_TIMER_ID)  
		back.MoveBack();
	
	//  �ػ�
	RECT rect = {0,0,380,550};
	::InvalidateRect(m_hMainWnd,&rect,FALSE);
}
void CPlaneApp::OnKeyDown(WPARAM nKey) // WM_KEYDOWN
{
	if(nKey == VK_SPACE)
	{
		blastBox.m_lstBlastFoePlane.splice(
			blastBox.m_lstBlastFoePlane.end(),foeBox.m_lstFoePlane);
	}
	//  �ػ�
	RECT rect = {0,0,380,550};
	::InvalidateRect(m_hMainWnd,&rect,FALSE);
}
void CPlaneApp::GunnerHitFoePlane()
{
	bool bflag = false;  //  ��� �ڵ��Ƿ���е��˷ɻ�
	//  �������е��ڵ�
	list<CGunner*>::iterator iteGun = gunBox.m_lstGunner.begin();
	while(iteGun != gunBox.m_lstGunner.end())
	{
		//---------�������е��˷ɻ�--------------------
		list<CFoePlane*>::iterator iteFoe = foeBox.m_lstFoePlane.begin();
		while(iteFoe != foeBox.m_lstFoePlane.end())
		{
			//  �ж��ڵ��Ƿ���е��˷ɻ�
			if((*iteFoe)->IsGunnerHitFoePlane(*iteGun) == true)
			{
				bflag = true;
				// ɾ��iteGun����ڵ�
				delete (*iteGun);
				iteGun = gunBox.m_lstGunner.erase(iteGun);
				// ���˷ɻ���Ѫ
				(*iteFoe)->DownBlood();
				// �жϵ��˷ɻ��Ƿ�ը
				if( (*iteFoe)->IsBoom() == true)
				{
					//  ��iteFoe����ŵ���һ����������ʾ��ը��Ч��
					blastBox.m_lstBlastFoePlane.push_back(*iteFoe);
					//  ɾ���ڵ�
					iteFoe = foeBox.m_lstFoePlane.erase(iteFoe);
				}
				break;
			}
			++iteFoe;
		}
		//---------�������е��˷ɻ�--------------------
		if(bflag == false)
			++iteGun;
		else
			bflag = false;
	}
}
bool CPlaneApp::IsGameOver()
{
	//  �������˷ɻ�
	list<CFoePlane*>::iterator ite = foeBox.m_lstFoePlane.begin();
	while(ite != foeBox.m_lstFoePlane.end())
	{
		if((*ite)->IsHitPlayer(plane) == true)
			return true;
		++ite;
	}
	return false;
}