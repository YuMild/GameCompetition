#pragma once

class Map;
class Mp;
class Player;

/// <summary>
///	�}�W�b�N�|�C���g�񕜃|�C���g
/// </summary>
class MagicPoint :public IGameObject
{
public:

	/// <summary>
	///	���W���w�肷��
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(Vector3& position) {
		m_position = position;
	}

	/// <summary>
	/// �}�b�v��ɉ摜�𐶐�����
	/// </summary>
	/// <param name="rc"></param>
	void MagicPointMap(RenderContext& rc)
	{
		if (m_isStart == false)
		{
			return;
		}
		m_magicPointMap.Draw(rc);
	}

	/// <summary>
	/// �}�b�v��ɃO���[�摜�𐶐�����
	/// </summary>
	/// <param name="rc"></param>
	void MagicPointMapGray(RenderContext& rc)
	{
		if (m_isStart == false)
		{
			return;
		}
		m_magicPointMapGray.Draw(rc);
	}

	MagicPoint();
	~MagicPoint();
	bool Start()override;
	void Update()override;

private:

	/// <summary>
	/// �}�b�v��̓�����Ǘ�
	/// </summary>
	void MapMove();

	/// <summary>
	/// �������Đ�
	/// </summary>
	void PlayMagicPointDeleteEffect();

	//�摜
	SpriteRender		m_magicPointMap;
	SpriteRender		m_magicPointMapGray;

	//�x�N�g��
	Vector3				m_position;
	Vector3				m_diff;

	//�G�t�F�N�g
	EffectEmitter*		m_magicPointEF			= nullptr;
	EffectEmitter*		m_magicPointDeleteEF	= nullptr;

	//�T�E���h
	SoundSource*		m_magicPointSE			= nullptr;

	//�Q��
	Map*				m_map					= nullptr;
	Mp*					m_mp					= nullptr;
	Player*				m_player				= nullptr;

	float				m_aliveTimer			= 0;
};

