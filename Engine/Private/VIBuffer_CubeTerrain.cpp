#include "..\Public\VIBuffer_CubeTerrain.h"

CVIBuffer_CubeTerrain::CVIBuffer_CubeTerrain(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer(pGraphic_Device)
{
}

CVIBuffer_CubeTerrain::CVIBuffer_CubeTerrain(const CVIBuffer_CubeTerrain & rhs)
	: CVIBuffer(rhs)
	, m_iNumVerticesX(rhs.m_iNumVerticesX)
	, m_iNumVerticesZ(rhs.m_iNumVerticesZ)
{
}

HRESULT CVIBuffer_CubeTerrain::Initialize_Prototype(_uint iNumVerticesX, _uint iNumVerticesZ)
{
	m_iNumVerticesX = iNumVerticesX;
	m_iNumVerticesZ = iNumVerticesZ;

	m_iNumVertices = m_iNumVerticesX * m_iNumVerticesZ*2;
	m_iStride = sizeof(VTXCUBETEX);
	m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitive = 100000;
	

	/* 정점들을 할당했다. */
	if (FAILED(__super::Ready_Vertex_Buffer()))
		return E_FAIL;

	VTXCUBETEX*			pVertices = nullptr;

	m_pVB->Lock(0, /*m_iNumVertices * m_iStride*/0, (void**)&pVertices, 0);

	_uint test1 = 0;
	
	for (_int i = 0; i < m_iNumVerticesZ; ++i)
	{
		for (_int j = 0; j < m_iNumVerticesX; ++j)
		{
			_uint	iIndex = i * m_iNumVerticesX + j;

			pVertices[iIndex * 2].vPosition = _float3(j, -0.5f, i);
			pVertices[iIndex * 2].vTexture = pVertices[iIndex * 2].vPosition;

			pVertices[iIndex * 2 + 1].vPosition = _float3(j, 0.5f, i);
			pVertices[iIndex * 2 + 1].vTexture = pVertices[iIndex * 2 + 1].vPosition;

			//pVertices[iIndex].vTexture = _float2(j / (m_iNumVerticesX - 1.0f) * 30.f, i / (m_iNumVerticesZ - 1.0f) * 30.f);
		}
	}
	
	m_pVB->Unlock();

	m_iIndicesByte = sizeof(FACEINDICES32);	
	m_eIndexFormat = D3DFMT_INDEX32;

	if (FAILED(__super::Ready_Index_Buffer()))
		return E_FAIL;

	FACEINDICES32*			pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	_uint		iNumFaces = 0;
	_uint		iCubeIndex = 0;

	for (_uint i = 0; i < m_iNumVerticesZ - 1; ++i)
	{
		for (_uint j = 0; j < m_iNumVerticesX - 1; ++j)
		{
			_uint	iIndex = i * m_iNumVerticesX + j;

			_uint	iIndices[8] = {
				iIndex * 2 + 1,
				iIndex * 2 + 3,
				iIndex * 2 + 2,
				iIndex * 2,
				iIndex * 2 + m_iNumVerticesX * 2 + 1,
				iIndex * 2 + m_iNumVerticesX * 2 + 3,
				iIndex * 2 + m_iNumVerticesX * 2 + 2,
				iIndex * 2 + m_iNumVerticesX * 2,
			};

			/* +X */
			pIndices[iNumFaces]._0 = iIndices[1]; pIndices[iNumFaces]._1 = iIndices[5]; pIndices[iNumFaces]._2 = iIndices[6];
			++iNumFaces;
			pIndices[iNumFaces]._0 = iIndices[1]; pIndices[iNumFaces]._1 = iIndices[6]; pIndices[iNumFaces]._2 = iIndices[2];
			++iNumFaces;

			/* -X */
			pIndices[iNumFaces]._0 = iIndices[4]; pIndices[iNumFaces]._1 = iIndices[0]; pIndices[iNumFaces]._2 =iIndices[3];
			++iNumFaces;
			pIndices[iNumFaces]._0 = iIndices[4]; pIndices[iNumFaces]._1 = iIndices[3]; pIndices[iNumFaces]._2 =iIndices[7];
			++iNumFaces;

			/* +Y */
			pIndices[iNumFaces]._0 = iIndices[4]; pIndices[iNumFaces]._1 = iIndices[5]; pIndices[iNumFaces]._2 = iIndices[1];
			++iNumFaces;
			pIndices[iNumFaces]._0 = iIndices[4]; pIndices[iNumFaces]._1 = iIndices[1]; pIndices[iNumFaces]._2 = iIndices[0];
			++iNumFaces;
									
			/* -Y */			
			pIndices[iNumFaces]._0 = iIndices[3]; pIndices[iNumFaces]._1 = iIndices[2]; pIndices[iNumFaces]._2 = iIndices[6];
			++iNumFaces;
			pIndices[iNumFaces]._0 = iIndices[3]; pIndices[iNumFaces]._1 = iIndices[6]; pIndices[iNumFaces]._2 = iIndices[7];
			++iNumFaces;

			/* +Z */			
			pIndices[iNumFaces]._0 = iIndices[5]; pIndices[iNumFaces]._1 = iIndices[4]; pIndices[iNumFaces]._2 = iIndices[7];
			++iNumFaces;
			pIndices[iNumFaces]._0 = iIndices[5]; pIndices[iNumFaces]._1 = iIndices[7]; pIndices[iNumFaces]._2 = iIndices[6];
			++iNumFaces;

			/* -Z */			   
			pIndices[iNumFaces]._0 =iIndices[0]; pIndices[iNumFaces]._1 = iIndices[1]; pIndices[iNumFaces]._2 = iIndices[2];
			++iNumFaces;
			pIndices[iNumFaces]._0 =iIndices[0]; pIndices[iNumFaces]._1 = iIndices[2]; pIndices[iNumFaces]._2 = iIndices[3];
			++iNumFaces;

		}
	}

	m_pIB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_CubeTerrain::Initialize(void* pArg)
{
	return S_OK;
}

CVIBuffer_CubeTerrain * CVIBuffer_CubeTerrain::Create(LPDIRECT3DDEVICE9 pGraphic_Device, _uint iNumVerticesX, _uint iNumVerticesZ)
{
	CVIBuffer_CubeTerrain*	pInstance = new CVIBuffer_CubeTerrain(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype(iNumVerticesX, iNumVerticesZ)))
	{
		ERR_MSG(TEXT("Failed to Created : CVIBuffer_CubeTerrain"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_CubeTerrain::Clone(void* pArg)
{
	CVIBuffer_CubeTerrain*	pInstance = new CVIBuffer_CubeTerrain(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CVIBuffer_CubeTerrain"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_CubeTerrain::Free()
{
	__super::Free();

}
