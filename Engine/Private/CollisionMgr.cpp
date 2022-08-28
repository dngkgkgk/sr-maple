#include "CollisionMgr.h"
#include "Transform.h"

IMPLEMENT_SINGLETON(CCollisionMgr)

CCollisionMgr::CCollisionMgr()
{
}

bool CCollisionMgr::CollisionCheck(class CTransform * p1Trans, class CTransform * p2Trans, _float fTimeDelta)
{
	_float3 p1pos = p1Trans->Get_State(CTransform::STATE_POSITION);
	_float fx1 = 0.5f*D3DXVec3Length(&p1Trans->Get_State(CTransform::STATE_RIGHT)); 
	_float fy1 = 0.5f*D3DXVec3Length(&p1Trans->Get_State(CTransform::STATE_UP));
	_float fz1 = 0.5f*D3DXVec3Length(&p1Trans->Get_State(CTransform::STATE_LOOK));

	_float3 p2pos = p2Trans->Get_State(CTransform::STATE_POSITION);
	_float fx2 = 0.5f*D3DXVec3Length(&p2Trans->Get_State(CTransform::STATE_RIGHT));
	_float fy2 = 0.5f*D3DXVec3Length(&p2Trans->Get_State(CTransform::STATE_UP));
	_float fz2 = 0.5f*D3DXVec3Length(&p2Trans->Get_State(CTransform::STATE_LOOK));

	//if( (  x1 <= x4  and   x2 >= x3 ) and ( y1 <= y4 and y2 >= y3 ) and ( z1 <= z4 and z2 >= z3 )

	if (((p1pos.x - fx1 <= p2pos.x + fx2) && (p1pos.x + fx1 >= p2pos.x - fx2)) &&
		((p1pos.y - fy1 <= p2pos.y + fy2) && (p1pos.y + fy1 >= p2pos.y - fy2)) &&
		((p1pos.z - fz1 <= p2pos.z + fz2) && (p1pos.z + fz1 >= p2pos.z - fz2)))
	{
		p1Trans->Up(fTimeDelta);

		return true;
		//ERR_MSG(TEXT("충돌 ㅇㅅㅇ"));
	}
	else
	{
		//p1Trans->Down(fTimeDelta);
		return false;
	}
	// 단순 충돌검사
	// 앞뒤왼오위아래 6면 따로 검사해야함

	return false;
}

bool CCollisionMgr::CollisionPlayer(CTransform * pPlayer, CTransform * pMonster, _float fTimeDelta)
{
	return false;
}

bool CCollisionMgr::CollisionSkill(CTransform * pPlayer_Skill, CTransform * pMonster, _float fTimeDelta)
{
	return false;
}

void CCollisionMgr::Free()
{
	
}
