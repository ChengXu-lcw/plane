#include "GunnerBox.h"


CGunnerBox::CGunnerBox(void)
{
}


CGunnerBox::~CGunnerBox(void)
{
	//  ɾ�����е��ڵ�
	list<CGunner*>::iterator ite = m_lstGunner.begin();
	while(ite != m_lstGunner.end())
	{
		// ɾ���ڵ�����
		delete (*ite);
		//  ɾ���ڵ�
		ite = m_lstGunner.erase(ite);
	}
}
void CGunnerBox::AllGunnerMove()
{
	//  ��������
	list<CGunner*>::iterator ite = m_lstGunner.begin();
	while(ite != m_lstGunner.end())
	{
		//  �ж��ڵ��Ƿ񳬳��߽�
		if( (*ite)->y < 0 )
		{
			//  ɾ�����ڵ�
			delete (*ite);
			ite = m_lstGunner.erase(ite);
		}
		else
		{
			// �ڵ��ƶ�
			(*ite)->MoveGunner();
			++ite;
		}
	}
}
void CGunnerBox::AllGunnerShow(HDC hdc)
{
	//  ��������
	list<CGunner*>::iterator ite = m_lstGunner.begin();
	while(ite != m_lstGunner.end())
	{
		//  ��ʾ�ڵ�
		(*ite)->ShowGunner(hdc);
		++ite;
	}
}