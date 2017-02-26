#include "stdafx.h"
#include "Texture.h"

/*!
* @brief	テクスチャをロード。
*/
void CTexture::Load(const char* fileName, bool isCubeMap)
{
	LPDIRECT3DDEVICE9 device = g_pd3dDevice;
	if (!isCubeMap) {
		if (FAILED(D3DXCreateTextureFromFile(
			device,
			fileName,
			&m_tex))) {
		}
	}
	else {
		if (FAILED(D3DXCreateCubeTextureFromFile(
			device,
			fileName,
			&m_cubeTex))) {
		}
	}
}