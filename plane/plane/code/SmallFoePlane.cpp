#include "SmallFoePlane.h"



CSmallFoePlane::CSmallFoePlane(void)
{
	m_nBlood = 1;
	//  随机飞机的位置
	x = rand()%(380-34);
	y = -28;
	m_nShowID = 1;
}


CSmallFoePlane::~CSmallFoePlane(void)
{
}
void CSmallFoePlane::InitFoePlane(HINSTANCE hIns)
{
	//  加载大飞机的图片
	m_hBmpFoePlane = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_SMALL));
}
bool CSmallFoePlane::IsGunnerHitFoePlane(CGunner* pGunner)
{
	if(pGunner->x	>= this->x && pGunner->x <= this->x+34
		&& pGunner->y >= this->y && pGunner->y <= this->y+28)
		return true;
	return false;
}
bool CSmallFoePlane::IsHitPlayer(CPlayer& plane)
{
	//x+30,y
	if(plane.x+30 >= this->x && plane.x+30 <= this->x+34
		&& plane.y >= this->y && plane.y <= this->y+28)
		return true;
	//x+60,y+50
	if(plane.x+60 >= this->x && plane.x+60 <= this->x+34
		&& plane.y+50 >= this->y && plane.y+50 <= this->y+28)
		return true;
	//x,y+50
	if(plane.x >= this->x && plane.x <= this->x+34
		&& plane.y+50 >= this->y && plane.y+50 <= this->y+28)
		return true;
	return false;
}
void CSmallFoePlane::MoveFoePlane()
{
	y+=5;
}
void CSmallFoePlane::ShowFoePlane(HDC hdc)
{
	HDC hMemDC = ::CreateCompatibleDC(hdc);
	::SelectObject(hMemDC,m_hBmpFoePlane);
	::BitBlt(hdc,x,y,34,28,hMemDC,0,(1-m_nShowID)*28,SRCAND);
	::DeleteDC(hMemDC);
}