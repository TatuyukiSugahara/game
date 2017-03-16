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
	for (map<int, SkinModelData*>::iterator it = skinmodeldata.begin();
		it != skinmodeldata.end();)
	{
		skinmodeldata.erase(it++);
	}
}

SkinModelData* CSkinModelDataManager::LoadSkinModelData(const char* filePath)
{

	int hash = MakeHash(filePath);

	auto it = skinmodeldata.find(hash);

	if (it == skinmodeldata.end())
	{
		SkinModelData* modeldata = new SkinModelData;
		modeldata->LoadModelData(filePath, NULL);
		std::pair<int, SkinModelData*> node(hash, modeldata);
		skinmodeldata.insert(node);
		return modeldata;
	}
	else
	{
		//�o�^�ς݁B
		return it->second;
	}

}
