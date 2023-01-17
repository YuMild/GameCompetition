#pragma once

class Game;
class Player;

/// <summary>
/// �}�b�v
/// </summary>
class Map :public IGameObject
{
public:

	/// <summary>
	/// �}�b�v�̒����̍��W���擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetMapCenterPosition() const {
		return m_mapCenterPosition;
	}

	Map();
	~Map();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

private:

	SpriteRender		m_mapBackGround;				//	�w�i
	SpriteRender		m_mapGradation;					//	�O���f�[�V����
	SpriteRender		m_mapFrame;						//	�g
	SpriteRender		m_mapFrameGray;					//	�g�̃O���[
	SpriteRender		m_playerMap;					//	�v���C���[
	SpriteRender		m_playerMapGray;				//	�v���C���[�̃O���[

	Vector3				m_mapCenterPosition;
	Vector3				m_playerMapPosition;
	Vector3				m_playerMapGrayPosition;

	Game*				m_game		= nullptr;
	Player*				m_player	= nullptr;
};

