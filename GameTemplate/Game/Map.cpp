#include "stdafx.h"
#include "Map.h"

#include "Player.h"

namespace
{
	Vector3 MAP_CENTER_POSITION = Vector3(750.0f, 330.0f, 0.0f);
}

Map::Map() {

}
Map::~Map() {

}
bool Map::Start()
{
	m_mapBackGround.Init("Assets/sprite/MapGround.DDS", 300.0f, 300.0f);
	m_mapBackGround.SetPosition(MAP_CENTER_POSITION);
	m_mapBackGround.Update();

	m_mapFrame.Init("Assets/sprite/MapFrame.DDS", 300.0f, 300.0f);
	m_mapFrame.SetPosition(MAP_CENTER_POSITION);
	m_mapFrame.Update();

	m_playerMap.Init("Assets/sprite/PlayerMap.DDS", 200.0f, 200.0f);

	m_player = FindGO<Player>("player");

	return true;
}
void Map::Update() 
{

	m_playerMapPosition = m_player->GetPosition();
	m_playerMap.SetPosition({m_playerMapPosition.x*-0.09f+MAP_CENTER_POSITION.x,m_playerMapPosition.z*-0.09f+MAP_CENTER_POSITION.y,0.0f});

	m_mapBackGround.Update();
	m_mapFrame.Update();
	m_playerMap.Update();
}
void Map::Render(RenderContext& rc) 
{
	m_mapBackGround.Draw(rc);//èáî‘ëÂéñ
	m_playerMap.Draw(rc);
	m_mapFrame.Draw(rc);
}