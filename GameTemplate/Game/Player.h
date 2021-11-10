#pragma once
#include "sound/SoundSource.h"

class Enemy;
class Background;
class Hougan;
class Player :public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();
	void ManageState();
	void PlayAnimation();
	enum EnAnimationClip {
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};
	AnimationClip animationClips[enAnimationClip_Num];
	CharacterController characterController;
	Quaternion playerRotation;
	ModelRender playerRender;
	ModelRender houganRender;
	Vector3 playerPosition;
	Vector3 houganPosition;
	Vector3 cameraPosition;
	Vector3 playerMoveSpeed;
	Vector3 m_forward;
	Hougan* m_hougan;
	Background* m_background;
	Enemy* m_enemy;
	SoundSource* gunshotSE;
	SoundSource* dryfireSE;
	SoundSource* enemydeathSE;
	float cooltimer = 0;
	bool cooltime = true;
	bool hougantime = true;
	int playerState = 0;
	int houganState = 0;
};