#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CRenderer;
class CTransform;
class CVIBuffer_Cube;
END

BEGIN(Client)

class CTestBox final : public CGameObject
{
public:
	typedef struct tagCubeDesc
	{
		_float3	vPos;
		_int	iIndex;
		_int 	r, g, b;
	}CUBEDESC; // 파일 불러오기할때 위치 타일 iIndex
private:
	CTestBox(LPDIRECT3DDEVICE9 pGraphic_Device);
	CTestBox(const CTestBox& rhs);
	virtual ~CTestBox() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta)override;
	virtual void Late_Tick(_float fTimeDelta)override;
	virtual HRESULT Render() override;
public:
	CTransform* Get_TransformCom() { return m_pTransformCom; }

private: /* For.Components */
	CTexture*				m_pTextureCom = nullptr;
	CRenderer*				m_pRendererCom = nullptr;
	CVIBuffer_Cube*		m_pVIBufferCom = nullptr;

private:
	CUBEDESC	m_CubeDesc;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_RenderState();
	HRESULT Release_RenderState();

public:
	static CTestBox* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;
};

END