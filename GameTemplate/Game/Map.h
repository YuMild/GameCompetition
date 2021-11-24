#pragma once

class Player;

class Map :public IGameObject
{
public:
	Vector3 GetMapCenterPosition() const {
		return m_mapCenterPosition;
	}
	Map();
	~Map();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender m_mapBackGround;
	SpriteRender m_mapGradation;
	SpriteRender m_mapFrame;
	SpriteRender m_playerMap;

	Vector3 m_mapCenterPosition;
	Vector3 m_playerMapPosition;

	Player* m_player;
};

