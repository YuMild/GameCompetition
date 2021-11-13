#pragma once

class Player;

class Map : public IGameObject
{
public:
	Map();
	~Map();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	const bool WorldPositionConvertToMapPosition(Vector3 worldCenterPosition, Vector3 worldPosition, Vector3& mapPosition);
	SpriteRender m_map;
	SpriteRender m_mapFrame;
	SpriteRender m_enemyMap;
	SpriteRender m_playerMap;

	Player* m_player;
};

