#pragma once


class CScene
{
public:
	CScene(){}
	virtual ~CScene()	//��{�N���X�̃f�X�g���N�^�ɂ̓o�[�`����������B
	{
		
	}
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};
