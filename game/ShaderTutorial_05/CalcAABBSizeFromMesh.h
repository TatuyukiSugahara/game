#pragma once 
#include "stdafx.h"

void CalcAABBSizeFromMesh(LPD3DXMESH mesh, D3DXVECTOR3& min, D3DXVECTOR3& max)
{
	D3DXVECTOR3 size;
	min.x = FLT_MAX;
	min.y = FLT_MAX;
	min.z = FLT_MAX;
	max.x = -FLT_MAX;
	max.y = -FLT_MAX;
	max.z = -FLT_MAX;
	LPDIRECT3DVERTEXBUFFER9 vb;
	mesh->GetVertexBuffer(&vb);
	D3DVERTEXBUFFER_DESC desc;
	vb->GetDesc(&desc);
	//int stride = D3DXGetFVFVertexSize(desc.FVF);
	int stride = 80; //@todo ‰¼‰¼‰¼‰¼
	char* pVB = NULL;
	vb->Lock(0, desc.Size, (void**)&pVB, D3DLOCK_DISCARD);
	int numVertex = desc.Size / stride;
	for (int vertNo = 0; vertNo < numVertex; vertNo++) {
		float* pVertexPos = (float*)(pVB);
		min.x = min(min.x, pVertexPos[0]);
		min.y = min(min.y, pVertexPos[1]);
		min.z = min(min.z, pVertexPos[2]);
		max.x = max(max.x, pVertexPos[0]);
		max.y = max(max.y, pVertexPos[1]);
		max.z = max(max.z, pVertexPos[2]);
		pVB += stride;
	}
	vb->Unlock();
}

//extern void CalcAABBSizeFromMesh(LPD3DXMESH mesh, D3DXVECTOR3& min, D3DXVECTOR3& max);