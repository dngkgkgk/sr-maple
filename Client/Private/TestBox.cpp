#include "stdafx.h"
#include "..\Public\TestBox.h"
#include "GameInstance.h"

CTestBox::CTestBox(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CTestBox::CTestBox(const CTestBox & rhs)
	: CGameObject(rhs)
{
}

HRESULT CTestBox::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CTestBox::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	memcpy(&m_CubeDesc, pArg, sizeof(CUBEDESC));

	return S_OK;
}

void CTestBox::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);		

	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(1.0f, 1.0f, 1.0f));
	//m_pTransformCom->Set_Scaled(_float3(2.f, 2.f, 2.f));

}

void CTestBox::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);	

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CTestBox::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;
	
	if (FAILED(m_pTransformCom->Bind_OnGraphicDev()))
		return E_FAIL;


	if (FAILED(m_pTextureCom->Bind_OnGraphicDev(m_CubeDesc.iIndex)))
		return E_FAIL;

	if (FAILED(SetUp_RenderState()))
		return E_FAIL;

	m_pVIBufferCom->Render();


	if (FAILED(Release_RenderState()))
		return E_FAIL;

	return S_OK;
}

HRESULT CTestBox::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Components(TEXT("Com_Texture"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Sky2"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::Add_Components(TEXT("Com_VIBuffer"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_VIBuffer_Cube"), (CComponent**)&m_pVIBufferCom)))
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

HRESULT CTestBox::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;	

	//m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	return S_OK;
}

HRESULT CTestBox::Release_RenderState()
{
	//m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	return S_OK;
}

CTestBox * CTestBox::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CTestBox*	pInstance = new CTestBox(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CTestBox"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CTestBox::Clone(void* pArg)
{
	CTestBox*	pInstance = new CTestBox(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CTestBox"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTestBox::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
}
