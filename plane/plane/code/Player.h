#pragma once
#include "Sys.h"
#include "GunnerBox.h"

class CPlayer
{
public:
	CPlayer(void);
	~CPlayer(void);
public:
	HBITMAP m_hBmpPlayer;
	int x;
	int y;
	int m_nGunnerType;  //  ≈⁄µØ¿‡–Õ
public:
	void InitPlayer(HINSTANCE hIns);
	void MovePlayer(int FX);
	void ShowPlayer(HDC hdc);
	void SendGunner(HINSTANCE hIns, CGunnerBox& gunBox);
};

