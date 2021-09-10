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
	// 1.  初始化背景
	back.InitBack(m_hIns);
	// 2.  吃初始化玩家飞机
	plane.InitPlayer(m_hIns);
	// 3.  启动所有的定时器
	::SetTimer(m_hMainWnd,BACK_MOVE_TIMER_ID,100,0);   //  控制背景移动
	::SetTimer(m_hMainWnd,PLAYER_MOVE_TIMER_ID,1,0);   //  控制玩家飞机移动
	::SetTimer(m_hMainWnd,SEND_GUNNER_TIMER_ID,350,0);  // 控制玩家飞机发炮弹
	::SetTimer(m_hMainWnd,GUNNER_MOVE_TIMER_ID,10,0);   // 控制炮弹移动
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
	back.ShowBack(hMemDC);//  显示背景
	plane.ShowPlayer(hMemDC);//  显示玩家飞机
	gunBox.AllGunnerShow(hMemDC);  //  显示所有炮弹
	foeBox.AllFoePlaneShow(hMemDC);  //  显示所有敌人飞机
	blastBox.AllFoePlaneShow(hMemDC);  //  显示爆炸的敌人飞机
	//---------------------------------------------------
	::BitBlt(hdc,0,0,380,550,hMemDC,0,0,SRCCOPY);

	::DeleteObject(hBitmap);
	::DeleteDC(hMemDC);
	::EndPaint(m_hMainWnd,&ps);
}
void CPlaneApp::OnGameRun(WPARAM nTimerID) // WM_TIM	ER
{
	//  切换爆炸的效果图
	if(nTimerID == CHANGE_SHOWID_TIMER_ID)
		blastBox.ChangeShowID();

	//  创建敌人飞机
	if(nTimerID == CREATE_FOEPLANE_TIMER_ID)
		foeBox.CreateFoePlane(m_hIns);
	//  敌人飞机移动
	if(nTimerID == FOEPLANE_MOVE_TIMER_ID)
	{
		foeBox.AllFoePlaneMove();
		if(this->IsGameOver() == true)
		{
			//  结束定时器
			::KillTimer(m_hMainWnd,BACK_MOVE_TIMER_ID);   //  控制背景移动
			::KillTimer(m_hMainWnd,PLAYER_MOVE_TIMER_ID);   //  控制玩家飞机移动
			::KillTimer(m_hMainWnd,SEND_GUNNER_TIMER_ID);  // 控制玩家飞机发炮弹
			::KillTimer(m_hMainWnd,GUNNER_MOVE_TIMER_ID);   // 控制炮弹移动
			::KillTimer(m_hMainWnd,CREATE_FOEPLANE_TIMER_ID);
			::KillTimer(m_hMainWnd,FOEPLANE_MOVE_TIMER_ID);
			::KillTimer(m_hMainWnd,CHANGE_SHOWID_TIMER_ID);
			::MessageBox(0,"GameOver","提示",MB_OK);
		}
	}
	//  发射炮弹
	if(nTimerID == SEND_GUNNER_TIMER_ID)
		plane.SendGunner(m_hIns,gunBox);   
	//  炮弹移动
	if(nTimerID == GUNNER_MOVE_TIMER_ID)
	{
		gunBox.AllGunnerMove();
		//  炮弹打敌人飞机
		this->GunnerHitFoePlane();
	}
	//  玩家飞机移动
	if(nTimerID == PLAYER_MOVE_TIMER_ID)
	{
		//  判断是否按方向键
		if(::GetAsyncKeyState(VK_LEFT))
			plane.MovePlayer(VK_LEFT);
		if(::GetAsyncKeyState(VK_RIGHT))
			plane.MovePlayer(VK_RIGHT);
		if(::GetAsyncKeyState(VK_UP))
			plane.MovePlayer(VK_UP);
		if(::GetAsyncKeyState(VK_DOWN))
			plane.MovePlayer(VK_DOWN);
	}

	//  背景移动
	if(nTimerID == BACK_MOVE_TIMER_ID)  
		back.MoveBack();
	
	//  重绘
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
	//  重绘
	RECT rect = {0,0,380,550};
	::InvalidateRect(m_hMainWnd,&rect,FALSE);
}
void CPlaneApp::GunnerHitFoePlane()
{
	bool bflag = false;  //  标记 炮弹是否打中敌人飞机
	//  遍历所有的炮弹
	list<CGunner*>::iterator iteGun = gunBox.m_lstGunner.begin();
	while(iteGun != gunBox.m_lstGunner.end())
	{
		//---------遍历所有敌人飞机--------------------
		list<CFoePlane*>::iterator iteFoe = foeBox.m_lstFoePlane.begin();
		while(iteFoe != foeBox.m_lstFoePlane.end())
		{
			//  判断炮弹是否打中敌人飞机
			if((*iteFoe)->IsGunnerHitFoePlane(*iteGun) == true)
			{
				bflag = true;
				// 删除iteGun这个炮弹
				delete (*iteGun);
				iteGun = gunBox.m_lstGunner.erase(iteGun);
				// 敌人飞机掉血
				(*iteFoe)->DownBlood();
				// 判断敌人飞机是否爆炸
				if( (*iteFoe)->IsBoom() == true)
				{
					//  把iteFoe对象放到另一个链表中显示爆炸的效果
					blastBox.m_lstBlastFoePlane.push_back(*iteFoe);
					//  删除节点
					iteFoe = foeBox.m_lstFoePlane.erase(iteFoe);
				}
				break;
			}
			++iteFoe;
		}
		//---------遍历所有敌人飞机--------------------
		if(bflag == false)
			++iteGun;
		else
			bflag = false;
	}
}
bool CPlaneApp::IsGameOver()
{
	//  遍历敌人飞机
	list<CFoePlane*>::iterator ite = foeBox.m_lstFoePlane.begin();
	while(ite != foeBox.m_lstFoePlane.end())
	{
		if((*ite)->IsHitPlayer(plane) == true)
			return true;
		++ite;
	}
	return false;
}