#pragma once
class Player:public IGameObject
{
private:
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
	Quaternion rotation;
	ModelRender render;
	Vector3 position;
	Vector3 bulletDirection;
	Vector3 moveSpeed;
	Vector3 forward;
	int playerState = 0;
};

