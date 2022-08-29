#pragma once
#include "Base.h"

BEGIN(Engine)
class CCollisionMgr final: public CBase
{
	DECLARE_SINGLETON(CCollisionMgr)
public:
	CCollisionMgr();
	virtual ~CCollisionMgr()=default;

public:
	bool CollisionCheck(class CTransform* p1Trans, class CTransform* p2Trans, _float fTimeDelta);
	bool Collision_Rect_Cube(class CTransform* p1Trans, class CTransform* p2Trans, _float fTimeDelta);
	bool CollisionBlock(class CTransform* p1Trans, class CTransform* p2Trans, _float fTimeDelta);

public:
	virtual void Free()override;
};
END
