#include "BigFoePlane.h"


CBigFoePlane::CBigFoePlane(void)
{
	m_nBlood = 5;
	//  随机飞机的位置
	x = rand()%(380-108);
	y = -128;
	m_nShowID = 3;
}


CBigFoePlane::~CBigFoePlane(void)
{
}
void CBigFoePlane::InitFoePlane(HINSTANCE hIns)
{
	//  加载大飞机的图片
	m_hBmpFoePlane = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BIG));
}
bool CBigFoePlane::IsGunnerHitFoePlane(CGunner* pGunner)
{
	if(pGunner->x >= this->x && pGunner->x <= this->x+108
		&& pGunner->y >= this->y && pGunner->y <= this->y+128)
		return true;
	return false;
}
bool CBigFoePlane::IsHitPlayer(CPlayer& plane)
{
	//x+30,y
	if(plane.x+30 >= this->x && plane.x+30 <= this->x+108
		&& plane.y >= this->y && plane.y <= this->y+128)
		return true;
	//x+60,y+50
	if(plane.x+60 >= this->x && plane.x+60 <= this->x+108
		&& plane.y+50 >= this->y && plane.y+50 <= this->y+128)
		return true;
	//x,y+50
	if(plane.x >= this->x && plane.x <= this->x+108
		&& plane.y+50 >= this->y && plane.y+50 <= this->y+128)
		return true;
	return false;
}
void CBigFoePlane::MoveFoePlane()
{
	y+=2;
}
void CBigFoePlane::ShowFoePlane(HDC hdc)
{
	HDC hMemDC = ::CreateCompatibleDC(hdc);
	::SelectObject(hMemDC,m_hBmpFoePlane);
	::BitBlt(hdc,x,y,108,128,hMemDC,0,(3-m_nShowID)*128,SRCAND);
	::DeleteDC(hMemDC);
}