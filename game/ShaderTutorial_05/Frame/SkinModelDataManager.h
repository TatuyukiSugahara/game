/*!
* @brief	エフェクトマネージャー
*/

#pragma once
#include <map>
#include "SkinModelData.h"
#include "Animation.h"

class CSkinModelDataManager{
public:
	/*!
	* @brief	コンストラクタ。
	*/
	CSkinModelDataManager();
	/*!
	* @brief	デストラクタ。
	*/
	~CSkinModelDataManager();

	SkinModelData LoadSkinModelData(const char* filePath, Animation* anim);
private:
	std::map<int, SkinModelData*>		skinmodeldata;
};
