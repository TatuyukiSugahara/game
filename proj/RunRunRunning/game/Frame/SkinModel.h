/*!
*@brief	�X�L�����f��
*/
#pragma once

#include "Animation.h"
#include "Texture.h"

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
			viewMatrix
			projMatrix
			isDrawToShadowMap
	*/
	void Render(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawToShadowMap);
	
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
	//�e���󂯂�t���O�Z�b�g
	void SetShadowReceiverFlag(const bool flag)
	{
		ShadowReceiverFlag = flag;
	}
	//�e��`�悷��t���O�Z�b�g
	void SetDrawToShadowMap(const bool flag)
	{
		isDrawToShadowMap = flag;
	}
	/*!
	*@brief �@���}�b�v�t���O��ݒ�B
	*/
	void SetNormalMap(const bool flag)
	{
		isNormalMap = flag;
	}
	//���؂����}�b�v�t���O���Z�b�g
	void SetSpecularMap(const bool flag)
	{
		isSpecularMap = flag;
	}
	//�G�t�F�N�g���Q�b�g
	ID3DXEffect* GetEffect() const
	{
		return pEffect;
	}
	//�G�t�F�N�g���Z�b�g����
	void SetEffect(ID3DXEffect* effect)
	{
		pEffect = effect;
	}
	/*!
	* @brief	�I���W�i�����b�V�����擾�B
	*/
	LPD3DXMESH GetOrgMesh(LPD3DXFRAME frame) const;
	/*!
	* @brief	�擪�̃��b�V�����擾�B
	*/
	LPD3DXMESH GetOrgMeshFirst() const;

	//���[�t�B���O�����̎��s�B
	//morphTargetA	���[�t�^�[�Q�b�g�Ί�
	//morphTargetB�@���[�Ӄ^�[�Q�b�g�^��
	//rate ���[�t�B���O���[�g�B
	void Morphing(SkinModel* morphTargetA, SkinModel* morphTargetB, float rate);

	/*!
	* @brief	�m�[�}���}�b�v�Z�b�g�B
	*/
	void SetNormalMap(const LPDIRECT3DTEXTURE9& normal)
	{
		normalMap = normal;
	}
	/*!
	*@brief �X�y�L�����}�b�v��ݒ�B
	*/
	void SetSpecularMap(const LPDIRECT3DTEXTURE9& specMap)
	{
		specularMap = specMap;
	}
	/*!
	*@brief �t���l����ݒ�B
	*/
	void SetHureneruflg(const bool flag)
	{
		hureneruflg = flag;
	}
	/*!
	*@brief �n�ʂ��ǂ����ݒ�B
	*/
	void SetGround(const bool flag)
	{
		Ground = flag;
	}
	//�Z�b�g�e�N�X�`���B
	void SetTexture(const char* tex,const bool isCube)
	{
		texture.Load(tex, isCube);
	}
	//�Z�b�g�X�J�C�L���[�u�H
	void SetSkyCube(const bool flag)
	{
		SkyCube = flag;
	}
	//���b�V�����c���[�\���Œ��ׂč쐬����
	void CreateMeshList(LPD3DXFRAME pFrame);
	//���b�V�����Q�b�g
	const LPD3DXMESH& GetMesh(const LPD3DXMESHCONTAINER& pMeshContainerBase) const;
	//���b�V�����X�g���Q�b�g
	const std::vector<LPD3DXMESH>& GetMeshList() const
	{
		return meshList;
	}

private:
	D3DXMATRIX			worldMatrix;				//!<���[���h�s��B
	D3DXMATRIX			rotationMatrix;				//!<��]�s��B
	SkinModelData*		skinModelData;				//!<�X�L�����f���f�[�^�B
	ID3DXEffect*		pEffect;					//!<�G�t�F�N�g�B
	Animation			animation;					//!<�A�j���[�V�����B
	CLight*				light;						//!<���C�g�B
	bool				ShadowReceiverFlag;			//!<�e���󂯂�H
	bool				isDrawToShadowMap;			//!<�e��`�悷��H
	bool				isNormalMap;				//<!�m�[�}���}�b�v�t���O
	bool				isSpecularMap;				//<!�X�y�L�����}�b�v�t���O
	bool				Ground;						//<!�n�ʂł����H
	LPDIRECT3DTEXTURE9	normalMap;					//<!�m�[�}���}�b�v�B
	LPDIRECT3DTEXTURE9  specularMap;				//<!�X�y�L�����}�b�v�B
	bool				hureneruflg = false;		//<!�ӂ������点��B
	CTexture			texture;					//�e�N�X�`��
	bool				SkyCube = false;			//�X�J�C�L���[�u��?
	std::vector<LPD3DXMESH>			meshList;		//���b�V�����X�g
};
