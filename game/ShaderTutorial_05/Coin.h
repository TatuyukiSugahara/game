#pragma once

class CCoinChip;

/*!
* @brief	�}�b�v�N���X�B
*/
class CCoin {
public:

	CCoin();
	~CCoin();
	void Init();
	void Update();
	void Release();
	//�`��B
	void Render(
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	int GetSize()
	{
		return tableSize;
	}
private:
	std::vector<CCoinChip*> coinChipList;	//�}�b�v�`�b�v�̃��X�g�B
	int tableSize;
};
