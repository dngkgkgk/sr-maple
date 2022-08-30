#include "stdafx.h"
#include "..\Public\Player_Attack.h"
#include "GameInstance.h"
#include "Player.h"
#include "Monster.h"

CPlayer_Attack::CPlayer_Attack(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CPlayer_Attack::CPlayer_Attack(const CPlayer_Attack & rhs)
	: CGameObject(rhs)
{
}

HRESULT CPlayer_Attack::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPlayer_Attack::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	//D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinSizeX, g_iWinSizeY, 0.f, 1.f);

	//_float3 Attack_Pos= m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	//CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	//Safe_AddRef(pGameInstance);

	//auto Player_Pos = pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Player"));


	//_float3 TargetPos = Player_Pos->Get_Transform()->Get_State(CTransform::STATE_POSITION);

	//_float3 Target = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	//// _float3 Target ;

	//Target = *D3DXVec3Normalize(&TargetPos, &TargetPos);

	//m_pTransformCom->Set_Scaled(_float3(m_fSizeX, m_fSizeY, 1.f));
	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, Target);


	//Safe_Release(pGameInstance);


	
	/*m_fSizeX = 1.1f;
	m_fSizeY = 1.1f;
	m_fX = 1.f;
	m_fY = 4.f;
*/
	if (FAILED(SetUp_Components()))
		return E_FAIL;


	return S_OK;
}

void CPlayer_Attack::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


	m_SkillTime += m_SkillTime+fTimeDelta+0.2f;
	/*
	RECT		rcRect;
	SetRect(&rcRect, m_fX - m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.5f, m_fX + m_fSizeX * 0.5f, m_fY + m_fSizeY * 0.5f);

	POINT		ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	if (PtInRect(&rcRect, ptMouse))
	{
	ERR_MSG(L"Ãæµ¹");
	}*/

	m_fAttack_Frame = m_fAttack_Frame + 0.2f;

	if (m_fAttack_Frame <= 0 || m_fAttack_Frame >= 8)
	{ 
		 
		m_fAttack_Frame = 0;

	}


	

	//auto Monster = pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Monster"));

	//_float MonsterPosx = Monster->CMonster::Get_Transform()->Get_State(CTransform::STATE_POSITION).x;
	//_float MonsterPosy = Monster->CMonster::Get_Transform()->Get_State(CTransform::STATE_POSITION).y;
	//_float MonsterPosz = Monster->CMonster::Get_Transform()->Get_State(CTransform::STATE_POSITION).z;

	 //_float3 MonsterPos = Monster->Get_Transform()->Get_State(CTransform::STATE_POSITION);
	//_float3 PlayerPos = Player->Get_Transform()->Get_State(CTransform::STATE_POSITION);
	//CGameInstance*			pGameInstance = CGameInstance::Get_Instance();

	if (m_SkillTime > 0.3f)
	{
		//CGameInstance*			pGameInstance = CGameInstance::Get_Instance();

		//Safe_AddRef(pGameInstance);

		//auto Monster = pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Monster"));

		//_float3 MonsterPos = Monster->Get_Transform()->Get_State(CTransform::STATE_POSITION);

		////_float3 vPosition	m_pTransformCom->Get_State(CTransform::STATE_POSITION);

		//m_pTransformCom->Set_State(CTransform::STATE_POSITION, MonsterPos);// _float3(MonsterPos->x, MonsterPos->y+140,MonsterPos->z));


		CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
		Safe_AddRef(pGameInstance);

		//auto Player = pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Player"));

		auto Monster = pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Monster"));

		//_float3 PlayerPos = Player->Get_Transform()->Get_State(CTransform::STATE_POSITION);

		_float3 MonsterPos = Monster->Get_Transform()->Get_State(CTransform::STATE_POSITION);


		_float3 AttackPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	
		AttackPos += *D3DXVec3Normalize(&MonsterPos, &MonsterPos)*fTimeDelta * 10;

		m_pTransformCom->Set_Scaled(_float3(m_fSizeX, m_fSizeY, 1.f));
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, AttackPos);


		Safe_Release(pGameInstance);


	}

}

void CPlayer_Attack::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CPlayer_Attack::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_OnGraphicDev()))
		return E_FAIL;

	//_float4x4		ViewMatrix;
	//D3DXMatrixIdentity(&ViewMatrix);

	//m_pGraphic_Device->SetTransform(D3DTS_VIEW, &ViewMatrix);
	//m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	if (FAILED(m_pTextureCom->Bind_OnGraphicDev(m_fAttack_Frame)))
		return E_FAIL;

	if (FAILED(SetUp_RenderState()))
		return E_FAIL;

	m_pVIBufferCom->Render();

	if (FAILED(Release_RenderState()))
		return E_FAIL;



	return S_OK;
}

HRESULT CPlayer_Attack::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Components(TEXT("Com_Texture"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::Add_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;


	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 5.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	if (FAILED(__super::Add_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;


	return S_OK;
}

HRESULT CPlayer_Attack::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 250);
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	//m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	return S_OK;
}

HRESULT CPlayer_Attack::Release_RenderState()
{
	//m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	return S_OK;
}

CPlayer_Attack * CPlayer_Attack::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CPlayer_Attack*	pInstance = new CPlayer_Attack(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CPlayer_Attack"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPlayer_Attack::Clone(void* pArg)
{
	CPlayer_Attack*	pInstance = new CPlayer_Attack(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CPlayer_Attack"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPlayer_Attack::Free()
{
	__super::Free();

	//Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
}
