#pragma once

/*!
* @brief	�e�N�X�`���B
*/
class CTexture{
public:
	CTexture() :
		m_tex(nullptr)
	{
	}
	~CTexture()
	{
		if (m_tex) {
			m_tex->Release();
			m_tex = nullptr;
		}
		if (m_cubeTex) {
			m_cubeTex->Release();
			m_cubeTex = nullptr;
		}
	}
	void SetTextureDX(LPDIRECT3DTEXTURE9 tex)
	{
		m_tex = tex;
	}
	LPDIRECT3DTEXTURE9 GetTextureDX() const
	{
		return m_tex;
	}
	LPDIRECT3DCUBETEXTURE9 GetCubeMapDX() const
	{
		return m_cubeTex;
	}
	/*!
	* @brief	�e�N�X�`�������[�h�B
	*/
	void Load(const char* fileName, bool isCubeMap);
private:
	LPDIRECT3DTEXTURE9	m_tex = nullptr;		//!<�e�N�X�`���B
	LPDIRECT3DCUBETEXTURE9 m_cubeTex = nullptr;	//!<�L���[�u�e�N�X�`���B
};