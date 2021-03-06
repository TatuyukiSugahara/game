#include "SkinModelManager.h"
#include "SkinModelData.h"

map<UINT64, SkinModelData*> SkinModelManager::modelDataMap;

SkinModelData* SkinModelManager::LoadModel(const char* filename)
{
	int hash = Support::MakeHash(filename);
	//登録されてない
	if (modelDataMap[hash] == nullptr)
	{
		//生成
		SkinModelData* Original = new SkinModelData();
		//ファイルパス生成
		char* filepath = new char[64];
		strcpy_s(filepath,strlen("Asset/Xfile/")+1,"Asset/Xfile/");
		strcat_s(filepath, strlen(filepath) + strlen(filename)+1, filename);
		//読み取り
		Original->LoadModelData(filepath);
		//登録
		modelDataMap[hash] = Original;
	}
	//値を引っ張ってくる
	return modelDataMap[hash];
}