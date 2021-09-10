#pragma once
#include "Sys.h"

class CBack
{
public:
	CBack(void);
	~CBack(void);
public:
	HBITMAP m_hBmpBackDown;   //  ±³¾°µÄÍ¼Æ¬
	HBITMAP m_hBmpBackUp;
	int x;                      //  Î»ÖÃ
	int y; 
public:
	void InitBack(HINSTANCE hIns);
	void MoveBack();
	void ShowBack(HDC hdc);
};

