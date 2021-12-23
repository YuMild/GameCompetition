#pragma once

class Map;
class Mp;
class Player;
class MagicPoint :public IGameObject
{
public:

	void SetPosition(Vector3& position) {
		m_position = position;
	}
	MagicPoint();
	~MagicPoint();
	bool Start();
	void Update();
	void MapMove();

	void MagicPointMap(RenderContext& rc)
	{
		if (m_isStart == false)
		{
			return;
		}
		m_magicPointMap.Draw(rc);
	}
	void MagicPointMapGray(RenderContext& rc)
	{
		if (m_isStart == false)
		{
			return;
		}
		m_magicPointMapGray.Draw(rc);
	}

private:

	//�摜
	SpriteRender m_magicPointMap;
	SpriteRender m_magicPointMapGray;

	//�x�N�g��
	Vector3 m_position;
	Vector3 m_diff;

	//�G�t�F�N�g
	EffectEmitter* m_magicPointEF;
	EffectEmitter* m_magicPointDeleteEF;

	//�T�E���h
	SoundSource* m_magicPointSE;

	//�Q��
	Map* m_map;
	Mp* m_mp;
	Player* m_player;

	float m_aliveTimer = 0;
};

