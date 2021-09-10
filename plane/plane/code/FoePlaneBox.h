#pragma once
#include "FoePlane.h"
class CFoePlaneBox
{
public:
	CFoePlaneBox(void);
	~CFoePlaneBox(void);
public:
	list<CFoePlane*> m_lstFoePlane;  //  装敌人飞机
public:
	void CreateFoePlane(HINSTANCE hIns);  //  创建敌人飞机
	void AllFoePlaneMove();
	void AllFoePlaneShow(HDC hdc);
};

