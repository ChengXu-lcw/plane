#include "FoePlaneBox.h"
#include "MidFoePlane.h"
#include "BigFoePlane.h"
#include "SmallFoePlane.h"

CFoePlaneBox::CFoePlaneBox(void)
{
}


CFoePlaneBox::~CFoePlaneBox(void)
{
	//  删除所有的敌人飞机
	list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
	while(ite != m_lstFoePlane.end())
	{
		delete (*ite);
		ite = m_lstFoePlane.erase(ite);
	}
}
void CFoePlaneBox::CreateFoePlane(HINSTANCE hIns)  //  创建敌人飞机
{
	// 1.  随机一个敌人飞机对象
	CFoePlane* pFoePlane = 0;
	int index = rand()%12;
	if( index >= 0 && index <= 1)
		pFoePlane = new CBigFoePlane;
	else if(index >= 2 && index <= 5)
		pFoePlane = new CMidFoePlane;
	else
		pFoePlane = new CSmallFoePlane;

	// 2.  初始化
	pFoePlane->InitFoePlane(hIns);
	// 3.  添加到链表
	m_lstFoePlane.push_back(pFoePlane);
}
void CFoePlaneBox::AllFoePlaneMove()
{
	// 遍历链表
	list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
	while(ite != m_lstFoePlane.end())
	{
		//  判断敌人飞机是否超出边界
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
	// 遍历链表
	list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
	while(ite != m_lstFoePlane.end())
	{
		(*ite)->ShowFoePlane(hdc);
		++ite;
	}
}