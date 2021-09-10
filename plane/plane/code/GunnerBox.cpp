#include "GunnerBox.h"


CGunnerBox::CGunnerBox(void)
{
}


CGunnerBox::~CGunnerBox(void)
{
	//  删除所有的炮弹
	list<CGunner*>::iterator ite = m_lstGunner.begin();
	while(ite != m_lstGunner.end())
	{
		// 删除炮弹对象
		delete (*ite);
		//  删除节点
		ite = m_lstGunner.erase(ite);
	}
}
void CGunnerBox::AllGunnerMove()
{
	//  遍历链表
	list<CGunner*>::iterator ite = m_lstGunner.begin();
	while(ite != m_lstGunner.end())
	{
		//  判断炮弹是否超出边界
		if( (*ite)->y < 0 )
		{
			//  删除这炮弹
			delete (*ite);
			ite = m_lstGunner.erase(ite);
		}
		else
		{
			// 炮弹移动
			(*ite)->MoveGunner();
			++ite;
		}
	}
}
void CGunnerBox::AllGunnerShow(HDC hdc)
{
	//  遍历链表
	list<CGunner*>::iterator ite = m_lstGunner.begin();
	while(ite != m_lstGunner.end())
	{
		//  显示炮弹
		(*ite)->ShowGunner(hdc);
		++ite;
	}
}