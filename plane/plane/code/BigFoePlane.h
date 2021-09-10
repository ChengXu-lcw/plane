#pragma once
#include "foeplane.h"
class CBigFoePlane :
	public CFoePlane
{
public:
	CBigFoePlane(void);
	~CBigFoePlane(void);
public:
	virtual void InitFoePlane(HINSTANCE hIns);
	virtual bool IsGunnerHitFoePlane(CGunner* pGunner);
	virtual bool IsHitPlayer(CPlayer& plane);
	virtual void MoveFoePlane();
	virtual void ShowFoePlane(HDC hdc);
};

