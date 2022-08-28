#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_CubeTerrain final : public CVIBuffer
{
private:
	CVIBuffer_CubeTerrain(LPDIRECT3DDEVICE9 pGraphic_Device);
	CVIBuffer_CubeTerrain(const CVIBuffer_CubeTerrain& rhs);
	virtual ~CVIBuffer_CubeTerrain() = default;
public:
	virtual HRESULT Initialize_Prototype(_uint iNumVerticesX, _uint iNumVerticesZ);
	virtual HRESULT Initialize(void* pArg) override;

private:
	_uint		m_iNumVerticesX = 0;
	_uint		m_iNumVerticesZ = 0;
public:
	static CVIBuffer_CubeTerrain* Create(LPDIRECT3DDEVICE9 pGraphic_Device, _uint iNumVerticesX, _uint iNumVerticesZ);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END