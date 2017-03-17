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
	const LPDIRECT3DSURFACE9& GetRenderTarget() const
	{
		return surface;
	}
	/*!
	*@brief	�f�v�X�X�e���V���o�b�t�@���擾�B
	*/
	const LPDIRECT3DSURFACE9& GetDepthStencilBuffer() const
	{
		return depthSurface;
	}
	/*!
	*@brief	�e�N�X�`�����擾�B
	*/
	const LPDIRECT3DTEXTURE9& GetTexture() const
	{
		return texture;
	}
	/*!
	*@brief	�����擾�B
	*/
	const int& GetWidth() const
	{
		return width;
	}
	/*!
	*@brief	�������擾�B
	*/
	const int& GetHeight() const
	{
		return height;
	}
private:
	LPDIRECT3DSURFACE9		depthSurface;		//!<�[�x�o�b�t�@�p�̃T�[�t�F�C�X
	LPDIRECT3DTEXTURE9		texture;			//!<�������ݐ�̃e�N�X�`���B
	LPDIRECT3DSURFACE9		surface;			//!<�T�[�t�F�C�X
	int						width = 0;		//!<��
	int						height = 0;		//!<����
};