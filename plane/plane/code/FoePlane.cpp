#include "FoePlane.h"


CFoePlane::CFoePlane(void)
{
	m_hBmpFoePlane = 0;
	m_nBlood = 0;
	m_nShowID = 0;
	x = 0;
	y = 0;
}


CFoePlane::~CFoePlane(void)
{
	::DeleteObject(m_hBmpFoePlane);
	m_hBmpFoePlane = 0;
}
bool CFoePlane::IsBoom()
{
	//  �ж��Ƿ�ը
	if(m_nBlood == 0)
		return true;
	return false;
}
void CFoePlane::DownBlood()
{
	m_nBlood--;
}