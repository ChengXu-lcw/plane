#pragma once
#include "FoePlane.h"
class CFoePlaneBox
{
public:
	CFoePlaneBox(void);
	~CFoePlaneBox(void);
public:
	list<CFoePlane*> m_lstFoePlane;  //  װ���˷ɻ�
public:
	void CreateFoePlane(HINSTANCE hIns);  //  �������˷ɻ�
	void AllFoePlaneMove();
	void AllFoePlaneShow(HDC hdc);
};

