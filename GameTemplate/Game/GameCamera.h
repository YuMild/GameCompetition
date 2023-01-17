#pragma once

#include "camera/SpringCamera.h"

class Game;
class Player;

/// <summary>
/// �J����
/// </summary>
class GameCamera : public IGameObject
{
public:

	GameCamera();
	~GameCamera();
	bool Start()override;
	void Update()override;

private:

	//	�x�N�g��
	Vector3					m_position;
	Vector3					m_target;
	Vector3					m_toCameraPos		= Vector3::One;

	//	�N���X
	Game*					m_game				= nullptr;
	Player*					m_player			= nullptr;
	SpringCamera			m_springCamera;
};