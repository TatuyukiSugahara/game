/*!
*@brief	�X�L�����f��
*/
#pragma once

#include "Animation.h"


class SkinModelData;
class RenderContext;
class CLight;
/*!
*@brief	�X�L�����f��
*/
class SkinModel {
public:
	SkinModel();
	~SkinModel();
	/*!
	*@brief	������
	*/
	void Init(SkinModelData* modelData);
	/*!
	*@brief	�`��B
	*/
	void Draw(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawToShadowMap);
	
	/*!
	*@brief	���[���h�s����X�V�B
	*@details
	* ���CMotion�N���X�Ɉړ������܂��B
	*@param[in]		trans	���s�ړ��B
	*@param[in]		rot		��]�B
	*@param[in]		scale	�g��B
	*/
	void UpdateWorldMatrix( const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale );

	void DrawMeshContainer(
		IDirect3DDevice9* pd3dDevice,
		LPD3DXMESHCONTAINER pMeshContainerBase,
		LPD3DXFRAME pFrameBase,
		ID3DXEffect* pEffect,
		D3DXMATRIX* worldMatrix,
		D3DXMATRIX* rotationMatrix,
		D3DXMATRIX* viewMatrix,
		D3DXMATRIX* projMatrix,
		CLight* light,
		LPDIRECT3DTEXTURE9	normalMap,
		LPDIRECT3DTEXTURE9 specularMap,
		bool isDrawToShadowMap);

	void DrawFrame(
		IDirect3DDevice9* pd3dDevice,
		LPD3DXFRAME pFrame,
		ID3DXEffect* pEffect,
		D3DXMATRIX* worldMatrix,
		D3DXMATRIX* rotationMatrix,
		D3DXMATRIX* viewMatrix,
		D3DXMATRIX* projMatrix,
		CLight* light,
		LPDIRECT3DTEXTURE9	normalMap,
		LPDIRECT3DTEXTURE9 specularMap,
		bool isDrawToShadowMap
		);
	/*!
	*@brief	���C�g��ݒ�B
	*/
	void SetLight(CLight* light)
	{
		this->light = light;
	}
	void SetShadowReceiverFlag(bool flag)
	{
		ShadowReceiverFlag = flag;
	}
	void SetDrawToShadowMap(bool flag)
	{
		isDrawToShadowMap = flag;
	}
	/*!
	*@brief �@���}�b�v�t���O��ݒ�B
	*/
	void SetNormalMap(bool flag)
	{
		isNormalMap = flag;
	}
	void SetSpecularMap(bool flag)
	{
		isSpecularMap = flag;
	}
	ID3DXEffect* GetEffect()
	{
		return pEffect;
	}
	void SetEffect(ID3DXEffect* effect)
	{
		pEffect = effect;
	}
	/*!
	* @brief	�擪�̃��b�V�����擾�B
	*/
	LPD3DXMESH GetOrgMeshFirst() const;
	/*!
	* @brief	�m�[�}���}�b�v�Z�b�g�B
	*/
	void SetNormalMap(LPDIRECT3DTEXTURE9 normal)
	{
		normalMap = normal;
	}
	/*!
	*@brief �X�y�L�����}�b�v��ݒ�B
	*/
	void SetSpecularMap(LPDIRECT3DTEXTURE9 specMap)
	{
		specularMap = specMap;
	}
private:
	D3DXMATRIX			worldMatrix;			//!<���[���h�s��B
	D3DXMATRIX			rotationMatrix;			//!<��]�s��B
	SkinModelData*		skinModelData;			//!<�X�L�����f���f�[�^�B
	ID3DXEffect*		pEffect;				//!<�G�t�F�N�g�B
	Animation			animation;				//!<�A�j���[�V�����B
	CLight*				light;					//!<���C�g�B
	bool				ShadowReceiverFlag;
	bool				isDrawToShadowMap;
	bool				isNormalMap;			//<!�m�[�}���}�b�v�t���O
	bool				isSpecularMap;		//<!�X�y�L�����}�b�v�t���O
	LPDIRECT3DTEXTURE9	normalMap;				//<!�m�[�}���}�b�v�B
	LPDIRECT3DTEXTURE9  specularMap;				//<!�X�y�L�����}�b�v�B
};
