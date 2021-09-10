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
	CBack back;  //  背景对象
	CPlayer plane;  //  玩家飞机

	CGunnerBox gunBox;  //  所有炮弹
	CFoePlaneBox foeBox;  //  所有的敌人飞机
	CBlastFoePlaneBox blastBox;  //  所有的爆炸的敌人飞机
public:
	CPlaneApp(void);
	~CPlaneApp(void);
public:
	virtual void OnCreateGame();  //  WM_CREATE
	virtual void OnGameDraw(); // WM_PAINT
	virtual void OnGameRun(WPARAM nTimerID); // WM_TIMER
	virtual void OnKeyDown(WPARAM nKey); // WM_KEYDOWN
public:
	void GunnerHitFoePlane();   //  炮弹打敌人飞机
	bool IsGameOver();        //  游戏结束
};

