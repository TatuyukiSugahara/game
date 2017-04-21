#pragma once
#include "fbEngine/GameObject.h"

class Player;
//ゲームで使う影を作るためのカメラ
class GameShadowCamera :public GameObject
{
public:
	GameShadowCamera(const char* name) :GameObject(name) {}
	void Awake()override;
	void Update()override;
private:
	Player* _Player;
};