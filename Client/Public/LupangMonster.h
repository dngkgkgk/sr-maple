#pragma once

#include "Monster.h"

BEGIN(Client)

class CLupangMonster final : public CMonster
{

private:
	CLupangMonster(LPDIRECT3DDEVICE9 pGraphic_Device);
	CLupangMonster(const CLupangMonster& rhs);
	virtual ~CLupangMonster() = default;
	
public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta)override;
	virtual void Late_Tick(_float fTimeDelta)override;
	virtual HRESULT Render() override;

protected:
	virtual HRESULT SetUp_Components();
	virtual HRESULT SetUp_RenderState();
	virtual HRESULT Release_RenderState();
	virtual void MonsterMove();


public:
	static CLupangMonster* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg = nullptr);
	virtual void Free() override;
};

END