/*!
* @brief	�G�t�F�N�g�}�l�[�W��
*/

#include "stdafx.h"
#include "SkinModelDataManager.h"

namespace{
	/*!
	* @brief	�����񂩂�32bit�̃n�b�V���l���쐬�B
	*/
	int MakeHash(const char* string)
	{
		int hash = 0;
		int l = (int)strlen(string);
		for (int i = 0; i < l; i++){
			hash = hash * 37 + string[i];
		}
		return hash;
	}
}

/*!
* @brief	�R���X�g���N�^�B
*/
CSkinModelDataManager::CSkinModelDataManager()
{
}
/*!
* @brief	�f�X�g���N�^�B
*/
CSkinModelDataManager::~CSkinModelDataManager()
{
}

SkinModelData CSkinModelDataManager::LoadSkinModelData(const char* filePath, Animation* anim)
{

	SkinModelData modeldata;
	int hash = MakeHash(filePath);

	auto it = skinmodeldata.find(hash);

	if (it == skinmodeldata.end())
	{
		modeldata.LoadModelData(filePath, anim);
		std::pair<int, SkinModelData*> node(hash, &modeldata);
		skinmodeldata.insert(node);
	}
	else
	{
		//�o�^�ς݁B
		modeldata = *it->second;
	}
	return modeldata;
}
