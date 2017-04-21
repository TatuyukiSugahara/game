#pragma once


class CScene
{
public:
	CScene(){}
	//クラスが破棄される時に継承クラスのデストラクタが動作しない
	//基本クラスのデストラクタにはバーチャルをつける。
	virtual ~CScene(){}
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};
