#pragma once
/*!
*@brief	�����_�����O�^�[�Q�b�g�B
*/
class CRenderTarget {
public:
	/*!
	*@brief	�R���X�g���N�^�B
	*/
	CRenderTarget();
	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~CRenderTarget();
	/*!
	*@brief	����B
	*/
	void Release();
	/*!
	*@brief	�����_�����O�^�[�Q�b�g�̍쐬�B
	*@param[in]	w					�����_�����O�^�[�Q�b�g�̕��B
	*@param[in]	h					�����_�����O�^�[�Q�b�g�̍����B
	*@param[in]	mipLevel			�~�b�v�}�b�v���x���B
	*@param[in]	colorFormat			�J���[�o�b�t�@�̃t�H�[�}�b�g�B
	*@param[in]	depthStencilFormat	�f�v�X�X�e���V���o�b�t�@�̃t�H�[�}�b�g�B
	*@param[in]	multiSampleType		�}���`�T���v�����O�̎�ށB
	*@param[in]	multiSampleQuality	�}���`�T���v�����O�̕i���B
	*/
	void Create(
		int w,
		int h,
		int mipLevel,
		D3DFORMAT colorFormat,
		D3DFORMAT depthStencilFormat,
		D3DMULTISAMPLE_TYPE multiSampleType,
		int multiSampleQuality);
	/*!
	*@brief	�����_�����O�^�[�Q�b�g���擾�B
	*/
	LPDIRECT3DSURFACE9 GetRenderTarget()
	{
		return m_surface;
	}
	/*!
	*@brief	�f�v�X�X�e���V���o�b�t�@���擾�B
	*/
	LPDIRECT3DSURFACE9 GetDepthStencilBuffer()
	{
		return m_depthSurface;
	}
	/*!
	*@brief	�e�N�X�`�����擾�B
	*/
	LPDIRECT3DTEXTURE9 GetTexture()
	{
		return m_texture;
	}
private:
	LPDIRECT3DSURFACE9		m_depthSurface;		//!<�[�x�o�b�t�@�p�̃T�[�t�F�C�X
	LPDIRECT3DTEXTURE9		m_texture;			//!<�������ݐ�̃e�N�X�`���B
	LPDIRECT3DSURFACE9		m_surface;			//!<�T�[�t�F�C�X
};