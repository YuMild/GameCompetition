#pragma once

class Game;
class Map;
class Player;
class Score;

/// <summary>
/// �v����
/// </summary>
class Pudding :public IGameObject
{
public:

	/// <summary>
	/// �l�������v�����̐����擾
	/// </summary>
	/// <returns></returns>
	int GetGetPudding() const
	{
		return m_getPudding;
	}

	/// <summary>
	/// ���W���w��
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(Vector3& position) {
		m_position = position;
	}

	void PuddingMap(RenderContext& rc)
	{
		if (m_isStart == false)
		{
			return;
		}
		m_puddingMap.Draw(rc);
	}
	void  PuddingMapGray(RenderContext& rc)
	{
		if (m_isStart == false)
		{
			return;
		}
		m_puddingMapGray.Draw(rc);
	}

	Pudding();
	~Pudding();
	bool Start();
	void Update();

private:

	/// <summary>
	/// �}�b�v��̓���
	/// </summary>
	void MapMove();

	//�摜
	SpriteRender m_puddingMap;
	SpriteRender m_puddingMapGray;

	//�x�N�g��
	Vector3 m_position;
	Vector3 m_diff;

	//�G�t�F�N�g
	EffectEmitter* m_puddingEF;

	//�T�E���h
	SoundSource* m_puddingGetSE;

	//�Q��
	Game* m_game;
	Map* m_map;
	Player* m_player;
	Score* m_score;

	int m_getPudding = 0;

	float m_aliveTimer = 0;
};

