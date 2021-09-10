#pragma once
#include "gameapp.h"
#include "Back.h"
#include "Player.h"
#include "GunnerBox.h"
#include "FoePlaneBox.h"
#include "BlastFoePlaneBox.h"

class CPlaneApp :
	public CGameApp
{
public:
	CBack back;  //  ��������
	CPlayer plane;  //  ��ҷɻ�

	CGunnerBox gunBox;  //  �����ڵ�
	CFoePlaneBox foeBox;  //  ���еĵ��˷ɻ�
	CBlastFoePlaneBox blastBox;  //  ���еı�ը�ĵ��˷ɻ�
public:
	CPlaneApp(void);
	~CPlaneApp(void);
public:
	virtual void OnCreateGame();  //  WM_CREATE
	virtual void OnGameDraw(); // WM_PAINT
	virtual void OnGameRun(WPARAM nTimerID); // WM_TIMER
	virtual void OnKeyDown(WPARAM nKey); // WM_KEYDOWN
public:
	void GunnerHitFoePlane();   //  �ڵ�����˷ɻ�
	bool IsGameOver();        //  ��Ϸ����
};

