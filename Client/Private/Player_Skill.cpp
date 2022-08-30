#include "stdafx.h"
#include "..\Public\Player_Skill.h"
#include "GameInstance.h"
#include "Player.h"
#include "Monster.h"

CPlayer_Skill::CPlayer_Skill(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CPlayer_Skill::CPlayer_Skill(const CPlayer_Skill & rhs)
	: CGameObject(rhs)
{
}

HRESULT CPlayer_Skill::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPlayer_Skill::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinSizeX, g_iWinSizeY, 0.f, 1.f);



	m_fSizeX = 10.0f;
	m_fSizeY = 20.0f;
	m_fX = 1000.f;
	m_fY = 400.f;

	if (FAILED(SetUp_Components()))
		return E_FAIL;


	return S_OK;
}

void CPlayer_Skill::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
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

	m_fSkill_Frame = m_fSkill_Frame + 0.2f;

	if (m_fSkill_Frame <= 0 || m_fSkill_Frame >= 8)
	{
		m_fSkill_Frame = 0;

	}
	//_float MonsterPosx = Monster->CMonster::Get_Transform()->Get_State(CTransform::STATE_POSITION).x;
	//_float MonsterPosy = Monster->CMonster::Get_Transform()->Get_State(CTransform::STATE_POSITION).y;
	//_float MonsterPosz = Monster->CMonster::Get_Transform()->Get_State(CTransform::STATE_POSITION).z;


	for (_uint i = 0; i < 5; i++)
	{

		CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
		Safe_AddRef(pGameInstance);

		auto Player_Pos = pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Monster"));


		_float3 TargetPos = Player_Pos->Get_Transform()->Get_State(CTransform::STATE_POSITION);

		_float3 Target = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
		// _float3 Target ;

		Target += *D3DXVec3Normalize(&TargetPos, &TargetPos) * fTimeDelta * 20;

		m_pTransformCom->Set_Scaled(_float3(m_fSizeX, m_fSizeY, 1.f));
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, Target);


		Safe_Release(pGameInstance);
	}

}

void CPlayer_Skill::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CPlayer_Skill::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_OnGraphicDev()))
		return E_FAIL;

	//_float4x4		ViewMatrix;
	//D3DXMatrixIdentity(&ViewMatrix);

	//m_pGraphic_Device->SetTransform(D3DTS_VIEW, &ViewMatrix);
	//m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	if (FAILED(m_pTextureCom->Bind_OnGraphicDev(m_fSkill_Frame)))
		return E_FAIL;

	if (FAILED(SetUp_RenderState()))
		return E_FAIL;

	m_pVIBufferCom->Render();

	if (FAILED(Release_RenderState()))
		return E_FAIL;



	return S_OK;
}

HRESULT CPlayer_Skill::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Components(TEXT("Com_Texture"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Skill_Litening"), (CComponent**)&m_pTextureCom)))
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

HRESULT CPlayer_Skill::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 250);
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	//m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	return S_OK;
}

HRESULT CPlayer_Skill::Release_RenderState()
{
	//m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	return S_OK;
}

void CPlayer_Skill::LiteNing_Skill(_float _Player_Skill, _float fTimeDelta)
{
}

void CPlayer_Skill::Fireball_Skill(_float _Player_Skill, _float fTimeDelta)
{
}

CPlayer_Skill * CPlayer_Skill::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CPlayer_Skill*	pInstance = new CPlayer_Skill(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CPlayer_Skill"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPlayer_Skill::Clone(void* pArg)
{
	CPlayer_Skill*	pInstance = new CPlayer_Skill(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CPlayer_Skill"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPlayer_Skill::Free()
{
	__super::Free();

	//Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
}
