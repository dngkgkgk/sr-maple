#pragma once

#include "Client_Defines.h"
#include "Camera.h"

BEGIN(Engine)
END

BEGIN(Client)

class CCamera_Dynamic final : public CCamera
{
public:
	typedef struct tagCameraDesc_Derived
	{
		_uint						iTest;
		CCamera::CAMERADESC			CameraDesc;
	}CAMERADESC_DERIVED;
private:
	CCamera_Dynamic(LPDIRECT3DDEVICE9 pGraphic_Device);
	CCamera_Dynamic(const CCamera_Dynamic& rhs);
	virtual ~CCamera_Dynamic() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta)override;
	virtual void Late_Tick(_float fTimeDelta)override;
	virtual HRESULT Render() override;



public:
	static CCamera_Dynamic* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;

private:
	_float	m_fCameraZoomY = 10;
	_float	m_fCameraZoomZ = 10;
};

END