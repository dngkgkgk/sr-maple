#pragma once

/* 월드스페이스에서의 상태를 보관한다.(월드행렬) */
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CTransform final : public CComponent
{
public:
	enum STATE { STATE_RIGHT, STATE_UP, STATE_LOOK, STATE_POSITION, STATE_END };

public:
	typedef struct tagTransformDesc
	{
		_float		fSpeedPerSec;
		_float		fRotationPerSec;
	}TRANSFORMDESC;
private:
	CTransform(LPDIRECT3DDEVICE9 pGraphic_Device);
	CTransform(const CTransform& rhs);
	virtual ~CTransform() = default;

public:
	_float3 Get_State(STATE eState) const {		
		return *(_float3*)&m_WorldMatrix.m[eState][0];
	}

	_float4x4 Get_WorldMatrix() const {
		return m_WorldMatrix;
	}

	_float3 Get_Scale(); 
	
	_float Get_ScaleX();

	void Set_State(STATE eState, _float3 vState) {
		memcpy(&m_WorldMatrix.m[eState][0], &vState, sizeof(_float3));
	}
	void Set_TransformDesc(const TRANSFORMDESC& TransformDesc) {
		m_TransformDesc = TransformDesc;
	}

	void Set_Scaled(_float3 vScale);
	void Set_Jump(_bool bJump) { m_bJump = bJump; }
	_bool Get_Jump() { return m_bJump; }
	void Set_Fall(_bool bFall) { m_bFall = bFall; }
	_bool Get_Fall() { return m_bFall; }
	void Set_SecSavePosOn(_bool bSavePos) { m_bSecSave = bSavePos; }
	_bool Check_SecSavePos() { return m_bSecSave; }
	_float3 Get_Collision_Pos() { return m_fSavePos; }
public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);

public:
	HRESULT Bind_OnGraphicDev();

public:
	void Go_Straight(_float fTimeDelta);
	void Go_Backward(_float fTimeDelta);
	void Go_Right(_float fTimeDelta);
	void Go_Left(_float fTimeDelta);
	void Turn(_float3 vAxis, _float fTimeDelta);
	void LookAt(_float3 vPoint);
	void Up(_float fTimeDelta);
	void Down(_float fTimeDelta);
	void Fall(_float fTimeDelta);
	void Go_RT(_float fTimeDelta);
	void Go_LT(_float fTimeDelta);
	void Go_LD(_float fTimeDelta);
	void Go_RD(_float fTimeDelta);
	void Jump(_float fTimeDelta, _float fJumpPower, _float fFallSpeed);
	_float3 Save_Collision_Pos(_float _fTimeDelta);
	void Attacked_Move(_float3 vcolPos, _float fTimeDelta);

private:
	_float4x4			m_WorldMatrix;
	TRANSFORMDESC		m_TransformDesc;
	_float				m_fGravity=0.f;
	_bool				m_bJump=false;
	_bool				m_bFall = false;
	_float3				m_fSavePos;
	_float3				m_fSecSavePos;
	_bool				m_bSecSave=false;
public:
	static CTransform* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg = nullptr) override;
	virtual void Free() override;
};

END