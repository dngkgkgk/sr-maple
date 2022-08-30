#pragma once

#include "Client_Defines.h"
#include "GameObject.h"
#include "GameInstance.h"

BEGIN(Engine)
class CTexture;
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CMonster abstract : public CGameObject
{
public:
	enum STATE {STATE_IDLE, STATE_LEFT, STATE_RIGHT, STATE_ATTACK, STATE_END };

protected:
	CMonster(LPDIRECT3DDEVICE9 pGraphic_Device);
	CMonster(const CMonster& rhs);
	virtual ~CMonster() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta)override;
	virtual void Late_Tick(_float fTimeDelta)override;
	virtual HRESULT Render() override;

protected: /* For.Components */
	CTexture*				m_pTextureCom = nullptr;
	CRenderer*				m_pRendererCom = nullptr;
	CVIBuffer_Rect*			m_pVIBufferCom = nullptr;
	


protected:
	STATE m_eState = STATE_IDLE;
	STATE m_ePrevState = STATE_IDLE;
	_float m_iTextureCount = 0.f;
	_float m_iTextureMaxCount = 10.f;
	_bool m_bChase = false;
	CGameObject* pPlayer = nullptr;
	_bool m_bMotionCheck = false;

protected:
	virtual void MonsterMove();
	virtual HRESULT SetUp_Components();
	virtual HRESULT SetUp_RenderState();
	virtual HRESULT Release_RenderState();

public:
	virtual CGameObject* Clone(void* pArg = nullptr) = 0;
	virtual void Free() override;
};

END