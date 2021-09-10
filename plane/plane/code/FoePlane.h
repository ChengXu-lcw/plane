#pragma once
#include "Sys.h"
#include "Player.h"
#include "Gunner.h"

class CFoePlane
{
public:
	CFoePlane(void);
	virtual ~CFoePlane(void);
public:
	HBITMAP m_hBmpFoePlane;   //  ͼƬ
	int x;
	int y;
	int m_nBlood;  //  Ѫ��
	int m_nShowID;  //  ��ʾͼƬ����һ��
public:
	virtual void InitFoePlane(HINSTANCE hIns)=0;
	virtual bool IsGunnerHitFoePlane(CGunner* pGunner)=0;
	virtual bool IsHitPlayer(CPlayer& plane)=0;
	virtual void MoveFoePlane()=0;
	virtual void ShowFoePlane(HDC hdc)=0;
public:
	bool IsBoom();
	void DownBlood();
};

