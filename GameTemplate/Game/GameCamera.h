#pragma once

#include "camera/SpringCamera.h"

class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

private:
	Player* player;
	Vector3 toCameraPos = Vector3::One;
	SpringCamera springCamera;
};