#include "FoePlaneBox.h"
#include "MidFoePlane.h"
#include "BigFoePlane.h"
#include "SmallFoePlane.h"

CFoePlaneBox::CFoePlaneBox(void)
{
}


CFoePlaneBox::~CFoePlaneBox(void)
{
	//  ɾ�����еĵ��˷ɻ�
	list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
	while(ite != m_lstFoePlane.end())
	{
		delete (*ite);
		ite = m_lstFoePlane.erase(ite);
	}
}
void CFoePlaneBox::CreateFoePlane(HINSTANCE hIns)  //  �������˷ɻ�
{
	// 1.  ���һ�����˷ɻ�����
	CFoePlane* pFoePlane = 0;
	int index = rand()%12;
	if( index >= 0 && index <= 1)
		pFoePlane = new CBigFoePlane;
	else if(index >= 2 && index <= 5)
		pFoePlane = new CMidFoePlane;
	else
		pFoePlane = new CSmallFoePlane;

	// 2.  ��ʼ��
	pFoePlane->InitFoePlane(hIns);
	// 3.  ��ӵ�����
	m_lstFoePlane.push_back(pFoePlane);
}
void CFoePlaneBox::AllFoePlaneMove()
{
	// ��������
	list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
	while(ite != m_lstFoePlane.end())
	{
		//  �жϵ��˷ɻ��Ƿ񳬳��߽�
		if((*ite)->y > 550)
		{
			delete (*ite);
			ite = m_lstFoePlane.erase(ite);
		}
		else
		{
			(*ite)->MoveFoePlane();
			++ite;
		}
	}	
}
void CFoePlaneBox::AllFoePlaneShow(HDC hdc)
{
	// ��������
	list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
	while(ite != m_lstFoePlane.end())
	{
		(*ite)->ShowFoePlane(hdc);
		++ite;
	}
}