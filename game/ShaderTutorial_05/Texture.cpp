#include "stdafx.h"
#include "Texture.h"

/*!
* @brief	�e�N�X�`�������[�h�B
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