#include "CollisionMgr.h"
#include "Transform.h"

IMPLEMENT_SINGLETON(CCollisionMgr)

CCollisionMgr::CCollisionMgr()
{
}

bool CCollisionMgr::CollisionCheck(class CTransform * p1Trans, class CTransform * p2Trans, _float fTimeDelta)
{
	_float3 p1pos = p1Trans->Get_State(CTransform::STATE_POSITION);
	_float fx1 = 0.15f*D3DXVec3Length(&p1Trans->Get_State(CTransform::STATE_RIGHT));
	_float fy1 = 0.3f*D3DXVec3Length(&p1Trans->Get_State(CTransform::STATE_UP));
	_float fz1 = 0.15f*D3DXVec3Length(&p1Trans->Get_State(CTransform::STATE_LOOK));

	_float3 p2pos = p2Trans->Get_State(CTransform::STATE_POSITION);
	_float fx2 = 0.5f*D3DXVec3Length(&p2Trans->Get_State(CTransform::STATE_RIGHT));
	_float fy2 = 0.5f*D3DXVec3Length(&p2Trans->Get_State(CTransform::STATE_UP));
	_float fz2 = 0.5f*D3DXVec3Length(&p2Trans->Get_State(CTransform::STATE_LOOK));

	//if( (  x1 <= x4  and   x2 >= x3 ) and ( y1 <= y4 and y2 >= y3 ) and ( z1 <= z4 and z2 >= z3 )
	
	if (((p1pos.x - fx1 <= p2pos.x + fx2) && (p1pos.x + fx1 >= p2pos.x - fx2)) &&
		((p1pos.y - fy1 <= p2pos.y + fy2) && (p1pos.y + fy1 >= p2pos.y - fy2)) &&
		((p1pos.z - fz1 <= p2pos.z + fz2) && (p1pos.z + fz1 >= p2pos.z - fz2)))
	{

		/*p1Trans->Set_Jump(false);
		p1Trans->Set_Fall(false);*/
	//	/*p1Trans->Set_State(CTransform::STATE_POSITION, _float3(p1Trans->Get_State(CTransform::STATE_POSITION).x,
	//	p2Trans->Get_State(CTransform::STATE_POSITION).y + p2Trans->Get_Scale().y, p1Trans->Get_State(CTransform::STATE_POSITION).z));*/
	//	
		/*if(fabs(p1Trans->Get_State(CTransform::STATE_POSITION).y-p2Trans->Get_State(CTransform::STATE_POSITION).y)>=0.04)*/
		//	p1Trans->Set_State(CTransform::STATE_POSITION, p1Trans->Get_Collision_Pos());

	//	/*if (p1pos.y <= p2pos.y + p2Trans->Get_State(CTransform::STATE_POSITION).y)
	//	{
	//		if (p1pos.x < p2pos.x)
	//		{
	//			if (p1pos.z > p2pos.z)
	//			{
	//				p1Trans->Go_Straight(fTimeDelta);
	//				if(p1pos.x > p2pos.x)
	//					p1Trans->Go_Left(fTimeDelta);
	//				return true;
	//			}
	//			else
	//				p1Trans->Go_Left(fTimeDelta);
	//		}
	//		else if (p1pos.x > p2pos.x)
	//		{
	//			if (p1pos.z < p2pos.z)
	//			{
	//				p1Trans->Go_Backward(fTimeDelta);
	//				if (p1pos.x < p2pos.x)
	//					p1Trans->Go_Right(fTimeDelta);
	//				return true;
	//			}		
	//			else
	//				p1Trans->Go_Right(fTimeDelta);
	//		}
	//		else if (p1pos.z < p2pos.z)
	//			p1Trans->Go_Backward(fTimeDelta);
	//		else if (p1pos.z > p2pos.z)
	//			p1Trans->Go_Straight(fTimeDelta);
	//	}*/
	//	/*else
	//	{
	//		if (p1pos.x > p2pos.x)
	//			p1Trans->Go_Right(fTimeDelta);
	//		else if (p1pos.x < p2pos.x)
	//			p1Trans->Go_Left(fTimeDelta);
	//		else if (p1pos.z > p2pos.z)
	//			p1Trans->Go_Straight(fTimeDelta);
	//		else if (p1pos.z < p2pos.z)
	//			p1Trans->Go_Backward(fTimeDelta);
	//	}*/

	//	/*if (p1pos.x > p2pos.x)
	//		p1Trans->Go_Right(fTimeDelta);
	//	if (p1pos.x < p2pos.x)
	//		p1Trans->Go_Left(fTimeDelta);
	//	if (p1pos.y > p2pos.y)
	//	{
	//		p1Trans->Set_Jump(false);
	//		p1Trans->Set_Fall(false);
	//		p1Trans->Set_State(CTransform::STATE_POSITION, _float3(p1Trans->Get_State(CTransform::STATE_POSITION).x, 
	//			p2Trans->Get_State(CTransform::STATE_POSITION).y + p2Trans->Get_Scale().y, p1Trans->Get_State(CTransform::STATE_POSITION).z));
	//	}
	//	if (p1pos.y < p2pos.y)
	//		p1Trans->Down(fTimeDelta);
	//	if (p1pos.z > p2pos.z)
	//		p1Trans->Go_Straight(fTimeDelta);
	//	if (p1pos.z < p2pos.z)
	//		p1Trans->Go_Backward(fTimeDelta);*/

	//	return true;//fGravity
	//	//ERR_MSG(TEXT("충돌 ㅇㅅㅇ"));
	//}
	//else
	//{
	//	//p1Trans->Set_Fall(true);
	//	//p1Trans->Set_Gravity(p1Trans->Get_Gravity() + 0.001f);
	//	//p1Trans->Down(fTimeDelta);
	//	//p1Trans->Jump(fTimeDelta, 0.f, 1.f);
	//	/*p1Trans->Set_State(CTransform::STATE_POSITION, _float3(p1Trans->Get_State(CTransform::STATE_POSITION).x,
	//		p1Trans->Get_State(CTransform::STATE_POSITION).y + 0.01f, p1Trans->Get_State(CTransform::STATE_POSITION).z));*/
	//	return false;
		//_float fDisX = fabs(p1pos.x - p2pos.x);
		//_float fDisY = fabs(p1pos.y - p2pos.y);//두 객체간 중점 거리
		//_float fDisZ = fabs(p1pos.z - p2pos.z);

		//if (fDisX > fDisY&&fDisX > fDisZ) //거리 비교
		//{
		//	if (p1pos.x > p2pos.x) //충돌체의 오른쪽
		//		p1Trans->Go_Right(fTimeDelta);
		//	else if (p1pos.x < p2pos.x) //충돌체의 왼쪽
		//		p1Trans->Go_Left(fTimeDelta);
		//}
		//if (fDisY > fDisX&&fDisY > fDisZ)
		//{
		//	if (p1pos.y > p2pos.y)
		//		p1Trans->Up(fTimeDelta);
		//	else if (p1pos.y < p2pos.y)
		//		p1Trans->Down(fTimeDelta);
		//}
		//if (fDisZ > fDisY&&fDisZ > fDisX)
		//{
		//	if (p1pos.z > p2pos.z)
		//		p1Trans->Go_Straight(fTimeDelta);
		//	else if (p1pos.z < p2pos.z)
		//		p1Trans->Go_Backward(fTimeDelta);
		//}
		/*if (_uint(p1pos.y*10) % 10 <= 1.05f&&_uint(p1pos.y * 10) % 10>1)
			p1Trans->Set_Fall(true);*/ //공중에 떠있을때 블럭 옆부분과 계속 충돌상태면 땅으로 떨어지지 않음
		return true;
	}
	else
	{
		//p1Trans->Set_Fall(true);

		return false;
	}
	// 단순 충돌검사
	// 앞뒤왼오위아래 6면 따로 검사해야함

	return false;
}

bool CCollisionMgr::Collision_Rect_Cube(CTransform * p1Trans, CTransform * p2Trans, _float fTimeDelta)
{ // 플레이어는 렉트고 블럭은 큐브 
	_float3 p1pos = p1Trans->Get_State(CTransform::STATE_POSITION);
	_float fx1 = 0.15f*D3DXVec3Length(&p1Trans->Get_State(CTransform::STATE_RIGHT));
	_float fy1 = 0.3f*D3DXVec3Length(&p1Trans->Get_State(CTransform::STATE_UP));
	_float fz1 = 0.15f*D3DXVec3Length(&p1Trans->Get_State(CTransform::STATE_LOOK)); //렉트 z는 그저 위치

	_float3 p2pos = p2Trans->Get_State(CTransform::STATE_POSITION);
	_float fx2 = 0.5f*D3DXVec3Length(&p2Trans->Get_State(CTransform::STATE_RIGHT));
	_float fy2 = 0.5f*D3DXVec3Length(&p2Trans->Get_State(CTransform::STATE_UP));
	_float fz2 = 0.5f*D3DXVec3Length(&p2Trans->Get_State(CTransform::STATE_LOOK));

	//if( (  x1 <= x4  and   x2 >= x3 ) and ( y1 <= y4 and y2 >= y3 ) and ( z1 <= z4 and z2 >= z3 )

	if (((p1pos.x - fx1 <= p2pos.x + fx2) && (p1pos.x + fx1 >= p2pos.x - fx2)) &&
		((p1pos.y - fy1 <= p2pos.y + fy2) && (p1pos.y + fy1 >= p2pos.y - fy2)) &&
		((p1pos.z - fz1 <= p2pos.z + fz2) && (p1pos.z + fz1 >= p2pos.z - fz2)))//렉트의 z가 큐브 z+zLength, z-zLength사이에 있으면 큐브 안에 렉트가 들어가있음
	{
		p1Trans->Set_Jump(false);
		p1Trans->Set_Fall(false);
		
		/*p1Trans->Set_State(CTransform::STATE_POSITION, _float3(p1Trans->Get_Collision_Pos().x,
			_float(_uint(p1Trans->Get_Collision_Pos().y/1)+1.f),p1Trans->Get_Collision_Pos().z ));*/
		//p1Trans->Set_State(CTransform::STATE_POSITION, p1Trans->Get_Collision_Pos());

		_float fDisX = fabs(p1pos.x - p2pos.x);
		_float fDisY = fabs(p1pos.y - p2pos.y);//두 객체간 중점 거리
		_float fDisZ = fabs(p1pos.z - p2pos.z);

		if (fDisX > fDisY&&fDisX > fDisZ) //거리 비교
		{
			if (p1pos.x > p2pos.x) //충돌체의 오른쪽
				p1Trans->Go_Right(fTimeDelta);
			if (p1pos.x < p2pos.x) //충돌체의 왼쪽
				p1Trans->Go_Left(fTimeDelta);
		}
		if (fDisY > fDisX&&fDisY > fDisZ)
		{
			if (p1pos.y > p2pos.y)
				p1Trans->Up(fTimeDelta*0.04f);
			if (p1pos.y < p2pos.y)
				p1Trans->Down(fTimeDelta);
		}
		if (fDisZ > fDisY&&fDisZ > fDisX)
		{
			if (p1pos.z > p2pos.z)
				p1Trans->Go_Straight(fTimeDelta);
			if (p1pos.z < p2pos.z)
				p1Trans->Go_Backward(fTimeDelta);
		}
		if (fDisX == fDisZ)
		{
			if (p1pos.x > p2pos.x&& p1pos.z > p2pos.z)
			{
				p1Trans->Go_Right(fTimeDelta);
				p1Trans->Go_Straight(fTimeDelta);
			}
			if (p1pos.x < p2pos.x&& p1pos.z > p2pos.z)
			{
				p1Trans->Go_Left(fTimeDelta);
				p1Trans->Go_Straight(fTimeDelta);
			}
			if (p1pos.x > p2pos.x&& p1pos.z < p2pos.z)
			{
				p1Trans->Go_Right(fTimeDelta);
				p1Trans->Go_Backward(fTimeDelta);
			}
			if (p1pos.x < p2pos.x&& p1pos.z < p2pos.z)
			{
				p1Trans->Go_Left(fTimeDelta);
				p1Trans->Go_Backward(fTimeDelta);
			}
		}
		return true;
	}
	else
	{
		//p1Trans->Set_Fall(true);

		return false;
	}
	// 단순 충돌검사
	// 앞뒤왼오위아래 6면 따로 검사해야함

	return false;
}

bool CCollisionMgr::CollisionBlock(CTransform * p1Trans, CTransform * p2Trans, _float fTimeDelta)
{
	return false;
}

void CCollisionMgr::Free()
{
}
