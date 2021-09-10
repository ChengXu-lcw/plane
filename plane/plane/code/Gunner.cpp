#include "Gunner.h"


CGunner::CGunner(void)
{
	m_hGunner = 0;
	x = 0;
	y = 0;
}


CGunner::~CGunner(void)
{
	::DeleteObject(m_hGunner);
	m_hGunner = 0;
}
void CGunner::IntiGunner(HINSTANCE hIns, int x1, int y1)
{
	m_hGunner = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_GUNNER));
	// ≥ı ºªØŒª÷√
	x = x1;
	y = y1;
}
void CGunner::MoveGunner()
{
	y-=10;
}
void CGunner::ShowGunner(HDC hdc)
{
	HDC hMemDC = ::CreateCompatibleDC(hdc);
	::SelectObject(hMemDC,m_hGunner);
	::BitBlt(hdc,x,y,6,9,hMemDC,0,0,SRCCOPY);
	::DeleteDC(hMemDC);
}