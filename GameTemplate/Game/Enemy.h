#pragma once
#include "sound/SoundSource.h"

class Player;
class Hougan;
class Enemy :public IGameObject
{
public:
	Enemy();
	~Enemy();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();
	void PlayAnimation();
	enum EnAnimationClip {
		enAnimationClip_Walk,
		enAnimationClip_Num,
	};
	SpriteRender enemymaprender;
	AnimationClip animationClips[enAnimationClip_Num];
	Quaternion enemyrotation;
	ModelRender enemyrender;
	Vector3 enemyposition;
	Vector3 enemyMoveSpeed;
	Vector3 enemytarget;
	Vector3 m_forward;
	Player* m_player;
	int enemyState = 1;
};