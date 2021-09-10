#include "MidFoePlane.h"


CMidFoePlane::CMidFoePlane(void)
{
	m_nBlood = 3;
	//  随机飞机的位置
	x = rand()%(380-70);
	y = -90;
	m_nShowID = 2;
}


CMidFoePlane::~CMidFoePlane(void)
{
}
void CMidFoePlane::InitFoePlane(HINSTANCE hIns)
{
	//  加载大飞机的图片
	m_hBmpFoePlane = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_MID));
}
bool CMidFoePlane::IsGunnerHitFoePlane(CGunner* pGunner)
{
	if(pGunner->x >= this->x && pGunner->x <= this->x+70
		&& pGunner->y >= this->y && pGunner->y <= this->y+90)
		return true;
	return false;
}
bool CMidFoePlane::IsHitPlayer(CPlayer& plane)
{
	//x+30,y
	if(plane.x+30 >= this->x && plane.x+30 <= this->x+70
		&& plane.y >= this->y && plane.y <= this->y+90)
		return true;
	//x+60,y+50
	if(plane.x+60 >= this->x && plane.x+60 <= this->x+70
		&& plane.y+50 >= this->y && plane.y+50 <= this->y+90)
		return true;
	//x,y+50
	if(plane.x >= this->x && plane.x <= this->x+70
		&& plane.y+50 >= this->y && plane.y+50 <= this->y+90)
		return true;
	return false;
}
void CMidFoePlane::MoveFoePlane()
{
	y+=4;
}
void CMidFoePlane::ShowFoePlane(HDC hdc)
{
	HDC hMemDC = ::CreateCompatibleDC(hdc);
	::SelectObject(hMemDC,m_hBmpFoePlane);
	::BitBlt(hdc,x,y,70,90,hMemDC,0,(2-m_nShowID)*90,SRCAND);
	::DeleteDC(hMemDC);
}