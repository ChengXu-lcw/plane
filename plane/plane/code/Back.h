#pragma once
#include "Sys.h"

class CBack
{
public:
	CBack(void);
	~CBack(void);
public:
	HBITMAP m_hBmpBackDown;   //  ������ͼƬ
	HBITMAP m_hBmpBackUp;
	int x;                      //  λ��
	int y; 
public:
	void InitBack(HINSTANCE hIns);
	void MoveBack();
	void ShowBack(HDC hdc);
};

