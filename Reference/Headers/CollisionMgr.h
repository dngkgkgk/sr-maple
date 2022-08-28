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
	bool CollisionPlayer(class CTransform* pPlayer, class CTransform* pMonster, _float fTimeDelta);
	bool CollisionSkill(class CTransform* pPlayer_Skill, class CTransform* pMonster, _float fTimeDelta);

public:
	virtual void Free()override;
};
END
