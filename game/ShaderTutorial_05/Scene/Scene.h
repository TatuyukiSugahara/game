#pragma once


class CScene
{
public:
	CScene(){}
	virtual ~CScene()	//基本クラスのデストラクタにはバーチャルをつける。
	{
		
	}
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};
