#include "stdafx.h"
#include "Texture.h"

/*!
* @brief	テクスチャをロード。
*/
void CTexture::Load(const char* fileName)
{
	LPDIRECT3DDEVICE9 device = g_pd3dDevice;
	if (FAILED(D3DXCreateTextureFromFile(
		device,
		fileName,
		&m_tex))) {
	}
}