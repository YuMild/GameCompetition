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

	/// <summary>
	/// �}�b�v��ɉ摜�𐶐�����
	/// </summary>
	/// <param name="rc"></param>
	void PuddingMap(RenderContext& rc)
	{
		if (m_isStart == false)
		{
			return;
		}
		m_puddingMap.Draw(rc);
	}

	/// <summary>
	/// �}�b�v��ɃO���[�摜�𐶐�����
	/// </summary>
	/// <param name="rc"></param>
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
	bool Start()override;
	void Update()override;

private:

	/// <summary>
	/// �}�b�v��̓���
	/// </summary>
	void MapMove();

	//�摜
	SpriteRender	m_puddingMap;
	SpriteRender	m_puddingMapGray;

	//�x�N�g��
	Vector3			m_position;
	Vector3			m_diff;

	//�G�t�F�N�g
	EffectEmitter*	m_puddingEF				= nullptr;

	//�T�E���h
	SoundSource*	m_puddingGetSE			= nullptr;

	//�Q��
	Game*			m_game					= nullptr;
	Map*			m_map					= nullptr;
	Player*			m_player				= nullptr;
	Score*			m_score					= nullptr;

	int				m_getPudding			= 0;

	float			m_aliveTimer			= 0;
};

