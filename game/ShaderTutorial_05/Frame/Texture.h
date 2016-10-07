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
	/*!
	* @brief	�e�N�X�`�������[�h�B
	*/
	void Load(const char* fileName);
private:
	LPDIRECT3DTEXTURE9	m_tex;		//!<�e�N�X�`���B
};