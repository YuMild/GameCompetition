#include "stdafx.h"
#include "Map.h"

#include "Player.h"
#include "Enemy.h"

Map::Map() {
}

Map::~Map() {
}

bool Map::Start() {

	m_mapCenterPosition = { 740.0f, 330.0f, 0.0f };

	m_mapBackGround.Init("Assets/sprite/MapBackGround.DDS", 300.0f, 300.0f);
	m_mapBackGround.SetPosition(m_mapCenterPosition);
	m_mapBackGround.Update();
	m_mapFrame.Init("Assets/sprite/MapFrame.DDS", 300.0f, 300.0f);
	m_mapFrame.SetPosition(m_mapCenterPosition);
	m_mapFrame.Update();

	m_playerMap.Init("Assets/sprite/PlayerMap.DDS", 200.0f, 200.0f);
	m_player = FindGO<Player>("player");

	return true;
}

void Map::Update() {

	m_playerMapPosition = m_player->GetPosition();
	m_playerMap.SetPosition({ m_playerMapPosition.x * -0.15f + m_mapCenterPosition.x,m_playerMapPosition.z * -0.15f + m_mapCenterPosition.y,0.0f });

	m_mapBackGround.Update();
	m_playerMap.Update();
	m_mapFrame.Update();
}

void Map::Render(RenderContext& rc) {

	m_mapBackGround.Draw(rc);

	const auto& enemys = FindGOs<Enemy>("Enemy");
	const int size = enemys.size();

	for (int i = 0; i < size; i++)
	{
		enemys[i]->DrawMap(rc);
	}

	m_playerMap.Draw(rc);
	m_mapFrame.Draw(rc);
}