#pragma once

class Bullet;

class Player:public IGameObject
{
public:
	Vector3 GetPosition() const
	{
		return position;
	}
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

private:
	AnimationClip animationClips[enAnimationClip_Num];
	CharacterController characterController;
	Quaternion rotation;
	ModelRender render;
	Vector3 position;
	Vector3 cameraPosition;
	Vector3 bulletDirection;
	Vector3 moveSpeed;
	Vector3 forward;
	Bullet* bullet;
	SoundSource* gunShotSE;
	SoundSource* dryFireSE;
	SoundSource* enemyDeathSE;
	bool magazine = true;
	float cooltimer = 0;
	int playerState = 0;
};

