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
	Vector3 m_position;
	Vector3 m_target;
	Player* m_player;
	Vector3 m_toCameraPos = Vector3::One;
	SpringCamera m_springCamera;
};