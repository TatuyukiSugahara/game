#pragma once


class CScene
{
public:
	CScene(){}
	//�N���X���j������鎞�Ɍp���N���X�̃f�X�g���N�^�����삵�Ȃ�
	//��{�N���X�̃f�X�g���N�^�ɂ̓o�[�`����������B
	virtual ~CScene(){}
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};
