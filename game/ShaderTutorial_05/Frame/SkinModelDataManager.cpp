/*!
* @brief	エフェクトマネージャ
*/

#include "stdafx.h"
#include "SkinModelDataManager.h"

namespace{
	/*!
	* @brief	文字列から32bitのハッシュ値を作成。
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
* @brief	コンストラクタ。
*/
CSkinModelDataManager::CSkinModelDataManager()
{
}
/*!
* @brief	デストラクタ。
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
		//登録済み。
		return it->second;
	}

}
