#include "stdafx.h"
#include "..\Public\LupangMonster.h"
#include "LupangSkill.h"

CLupangMonster::CLupangMonster(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CMonster(pGraphic_Device)
{
}

CLupangMonster::CLupangMonster(const CLupangMonster & rhs)
	:CMonster(rhs)
{
}

HRESULT CLupangMonster::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CLupangMonster::Initialize(void * pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

void CLupangMonster::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	MonsterMove();

	if (!m_bMotionCheck)
	{
		if (m_eState == STATE_LEFT)
		{
			m_pTransformCom->Go_Left(fTimeDelta);
		}
		else if (m_eState = STATE_IDLE)
		{
			m_pTransformCom->Go_Left(fTimeDelta);
		}
	}
}

void CLupangMonster::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CLupangMonster::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_OnGraphicDev()))
		return E_FAIL;

	m_pTextureCom->Bind_FrameMove();

	if (FAILED(SetUp_RenderState()))
		return E_FAIL;

	m_pVIBufferCom->Render();

	if (FAILED(Release_RenderState()))
		return E_FAIL;

	return S_OK;
}

HRESULT CLupangMonster::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components()))
		return E_FAIL;


	CGameInstance* m_pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(m_pGameInstance);

	pPlayer = m_pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Player"));
	 
	Safe_Release(m_pGameInstance);

	CTexture::FRAMETEXTURE		FrameTexture;
	ZeroMemory(&FrameTexture, sizeof(CTexture::FRAMETEXTURE));
	FrameTexture.FirstFrame = 1;
	FrameTexture.OriginFrame = 1;
	FrameTexture.EndFrame = 3;
	FrameTexture.FrameSpeed = 0.05f;

	/* For.Com_Renderer */
	if (FAILED(__super::Add_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Components(TEXT("Com_Texture"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_MonkeyMonster"), (CComponent**)&m_pTextureCom, &FrameTexture)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::Add_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Transform */
	CTransform::TRANSFORMDESC      TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 3.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	if (FAILED(__super::Add_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(10.0f, 2.3f, 1.0f));

	m_pTransformCom->Set_Scaled(_float3(-2.f, 2.f, 2.f));

	return S_OK;
}

HRESULT CLupangMonster::SetUp_RenderState()
{
	if (FAILED(__super::SetUp_RenderState()))
		return E_FAIL;

	return S_OK;
}

HRESULT CLupangMonster::Release_RenderState()
{
	if (FAILED(__super::Release_RenderState()))
		return E_FAIL;

	return S_OK;
}

void CLupangMonster::MonsterMove()
{
	if (m_bMotionCheck)
	{
		m_iTextureCount = 0.f;
		m_eState = STATE_ATTACK;

		_float fCurrentFrame = m_pTextureCom->m_FrameTexture.FirstFrame;

		if (fCurrentFrame >= 9 && fCurrentFrame < 9+0.05f)
		{
			CGameInstance* m_pGameInstance = CGameInstance::Get_Instance();
			Safe_AddRef(m_pGameInstance);

			_float3 vPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

			if (FAILED(m_pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_MonkeySkill"), LEVEL_GAMEPLAY, TEXT("Monkey_Skill"), &vPosition)))
				return;
			
			Safe_Release(m_pGameInstance);
		}

		if (m_pTextureCom->m_FrameTexture.FirstFrame == m_pTextureCom->m_FrameTexture.OriginFrame)
			m_bMotionCheck = false;
	}

	if (!m_bMotionCheck)
	{
		_float3 vMyPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
		_float3 vPlayerPosition = pPlayer->Get_Transform()->Get_State(CTransform::STATE_POSITION);

		_float3 vLook = vPlayerPosition - vMyPosition;
		_float vLength = D3DXVec3Length(&vLook);


		if (vLength <= 3.f)
		{
			m_iTextureCount = 0.f;
			if (vMyPosition.x > vPlayerPosition.x)
			{
				if (m_pTransformCom->Get_ScaleX() < 0)
				{
					m_pTransformCom->Set_Scaled(_float3(-2.f, 2.f, 2.f));
				}
			}
			else if (vMyPosition.x < vPlayerPosition.x)
			{
				if (m_pTransformCom->Get_ScaleX() > 0)
				{
					m_pTransformCom->Set_Scaled(_float3(-2.f, 2.f, 2.f));
				}
			}

			m_pTextureCom->m_FrameTexture.FrameSpeed = 0.05f;
			m_pTextureCom->m_FrameTexture.FirstFrame = 4;
			m_pTextureCom->m_FrameTexture.OriginFrame = 4;
			m_pTextureCom->m_FrameTexture.EndFrame = 10;
			m_bMotionCheck = true;
		}

		else if (vLength <= 6.f)
		{
			m_iTextureCount = 0.f;
			if (vMyPosition.x > vPlayerPosition.x)
			{
				if (m_pTransformCom->Get_ScaleX() < 0)
				{
					m_pTransformCom->Set_Scaled(_float3(-2.f, 2.f, 2.f));
				}
			}
			else if (vMyPosition.x < vPlayerPosition.x)
			{
				if (m_pTransformCom->Get_ScaleX() > 0)
				{
					m_pTransformCom->Set_Scaled(_float3(-2.f, 2.f, 2.f));
				}
			}

			m_pTextureCom->m_FrameTexture.OriginFrame = 0;
			m_pTextureCom->m_FrameTexture.EndFrame = 3;
			m_pTextureCom->m_FrameTexture.FrameSpeed = 0.1f;

			D3DXVec3Normalize(&vLook, &vLook);

			vMyPosition = vMyPosition + vLook * 0.1f;

			m_pTransformCom->Set_State(CTransform::STATE_POSITION, vMyPosition);
		}
		else
		{
			m_iTextureCount += 0.1f;

			if (m_eState == STATE_ATTACK)
			{
				m_eState = STATE_IDLE;
				m_pTextureCom->m_FrameTexture.FirstFrame = 0;
				m_pTextureCom->m_FrameTexture.OriginFrame = 0;
				m_pTextureCom->m_FrameTexture.EndFrame = 0;
			}

			if (m_iTextureCount >= m_iTextureMaxCount)
			{
				m_iTextureCount = 0.f;
				m_iTextureMaxCount = rand() % 10 + 5;

				if (m_eState == STATE_LEFT)
				{
					m_pTextureCom->m_FrameTexture.FirstFrame = 0;
					m_pTextureCom->m_FrameTexture.OriginFrame = 0;
					m_pTextureCom->m_FrameTexture.EndFrame = 0;
					m_eState = STATE_IDLE;
				}

				else if (m_eState == STATE_IDLE)
				{
					m_pTextureCom->m_FrameTexture.FirstFrame = 0;
					m_pTextureCom->m_FrameTexture.OriginFrame = 0;
					m_pTextureCom->m_FrameTexture.EndFrame = 3;
					m_eState = STATE_LEFT;
					m_pTransformCom->Set_Scaled(_float3(-2.f, 2.f, 2.f));
				}
			}
		}
	}
}

CLupangMonster * CLupangMonster::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLupangMonster*	pInstance = new CLupangMonster(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CLupangMonster"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CLupangMonster::Clone(void * pArg)
{
	CLupangMonster*	pInstance = new CLupangMonster(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CLupangMonster"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLupangMonster::Free()
{
	__super::Free();
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
}