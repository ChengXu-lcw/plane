#pragma once
#include "Gunner.h"
class CGunnerBox
{
public:
	CGunnerBox(void);
	~CGunnerBox(void);
public:
	list<CGunner*> m_lstGunner;  //  װ�ڵ�������
public:
	void AllGunnerMove();
	void AllGunnerShow(HDC hdc);
};

