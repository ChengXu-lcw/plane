#pragma once
#include "Sys.h"

class CGunner
{
public:
	CGunner(void);
	~CGunner(void);
public:
	HBITMAP m_hGunner;
	int x;
	int y;
public:
	void IntiGunner(HINSTANCE hIns, int x1, int y1);
	void MoveGunner();
	void ShowGunner(HDC hdc);
};

