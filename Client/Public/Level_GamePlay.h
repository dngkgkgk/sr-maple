#pragma once

#include "Client_Defines.h"
#include "Level.h"
#include "TestBox.h"

BEGIN(Client)

class CLevel_GamePlay final : public CLevel
{
private:
	CLevel_GamePlay(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel_GamePlay() = default;

public:
	virtual HRESULT Initialize();
	virtual void Tick(_float fTimeDelta);
	virtual void Late_Tick(_float fTimeDelta);

public:
	HRESULT Ready_Layer_Player(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Monster(const _tchar* pLayerTag);
	HRESULT Ready_Layer_TestBox(const _tchar* pLayerTag);
	HRESULT Ready_Layer_BackGround(const _tchar* pLayerTag);
	HRESULT Ready_Layer_CubeTerrain(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Camera(const _tchar* pLayerTag);
	HRESULT Ready_Layer_UI(const _tchar* pLayerTag);

	void LoadMapData(); // 맵 불러오기

private:
	class CPlayer* pPlayer = nullptr;
	
private://프레임
	_uint					m_iNumRender = 0;
	_tchar					m_szFPS[MAX_PATH] = TEXT("");
	_float					m_fTimeAcc = 0.f;

private:
	list<CTestBox::CUBEDESC> m_CubeInfoList;

public:
	static CLevel_GamePlay* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void Free() override;
};

END

