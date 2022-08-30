#include "stdafx.h"
#include "..\Public\Camera_Dynamic.h"
#include "GameInstance.h"
#include "Player.h"

CCamera_Dynamic::CCamera_Dynamic(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCamera(pGraphic_Device)
{
}

CCamera_Dynamic::CCamera_Dynamic(const CCamera_Dynamic & rhs)
	: CCamera(rhs)
{
}

HRESULT CCamera_Dynamic::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCamera_Dynamic::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(&((CAMERADESC_DERIVED*)pArg)->CameraDesc)))
		return E_FAIL;


	return S_OK;
}

void CCamera_Dynamic::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	CGameInstance*         pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	//카메라 위치 고정
	auto player = pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Player"));

	_float3 PlayerPos = dynamic_cast<CPlayer*>(player)->Get_TransformCom()->Get_State(CTransform::STATE_POSITION);

	m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(PlayerPos.x, PlayerPos.y + m_fCameraZoomY, PlayerPos.z - m_fCameraZoomZ));
	m_pTransform->LookAt(PlayerPos);

	// 카메라 돌리기
	//m_pTransform->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta * 15.f);

	//페이지 업다운으로 카메라 줌인, 줌아웃 기능
	_long         MouseMove = 0;
	bool         bDown = false;
	if (MouseMove = pGameInstance->Get_DIMMoveState(DIMM_WHEEL))
	{
		if (MouseMove < 0)
			bDown = true;

		if (bDown&&m_fCameraZoomY < 12) //줌아웃
		{
			m_fCameraZoomY += 0.42f;
			m_fCameraZoomZ += 0.3f;
		}
		else if (!bDown&&m_fCameraZoomY>0.5) //줌인
		{
			m_fCameraZoomY -= 0.42f;
			m_fCameraZoomZ -= 0.3f;
		}//ㅇㅇ
	}

	/*
	if (GetKeyState(VK_RIGHT) < 0)
	{
	m_pTransform->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta);
	// m_pTransformCom->Go_Right(fTimeDelta);
	}
	*/

	Safe_Release(pGameInstance);

	if (FAILED(Bind_OnGraphicDev()))
		return;


}

void CCamera_Dynamic::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

}

HRESULT CCamera_Dynamic::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;


	return S_OK;
}

CCamera_Dynamic * CCamera_Dynamic::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CCamera_Dynamic*   pInstance = new CCamera_Dynamic(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CCamera_Dynamic"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CCamera_Dynamic::Clone(void* pArg)
{
	CCamera_Dynamic*   pInstance = new CCamera_Dynamic(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CCamera_Dynamic"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCamera_Dynamic::Free()
{
	__super::Free();


}