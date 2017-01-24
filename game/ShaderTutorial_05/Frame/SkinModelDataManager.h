/*!
* @brief	�G�t�F�N�g�}�l�[�W���[
*/

#pragma once
#include <map>
#include "SkinModelData.h"
#include "Animation.h"

class CSkinModelDataManager{
public:
	/*!
	* @brief	�R���X�g���N�^�B
	*/
	CSkinModelDataManager();
	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~CSkinModelDataManager();

	SkinModelData LoadSkinModelData(const char* filePath, Animation* anim);
private:
	std::map<int, SkinModelData*>		skinmodeldata;
};
