#include "stdafx.h"
#include "Map.h"

#include "Enemy.h"
#include "Game.h"
#include "MagicPoint.h"
#include "Player.h"
#include "Pudding.h"

namespace
{
	const float MAP_WIDTH		= 300.0f;
	const float MAP_HEIGHT		= 300.0f;
	const float PLAYER_WIDTH	= 200.0f;
	const float PLAYER_HEIGHT	= 200.0f;
}

Map::Map() 
{

}

Map::~Map() 
{

}

bool Map::Start() 
{
	m_mapCenterPosition = { 740.0f, 330.0f, 0.0f };

	m_mapBackGround.Init("Assets/sprite/Map/MapBackGround.DDS", MAP_WIDTH, MAP_HEIGHT);
	m_mapBackGround.SetPosition(m_mapCenterPosition);
	m_mapBackGround.Update();
	m_mapFrame.Init("Assets/sprite/Map/MapFrame.DDS", MAP_WIDTH, MAP_HEIGHT);
	m_mapFrame.SetPosition(m_mapCenterPosition);
	m_mapFrame.Update();
	m_mapFrameGray.Init("Assets/sprite/Map/MapFrameGray.DDS", MAP_WIDTH, MAP_HEIGHT);
	m_mapFrameGray.SetPosition(m_mapCenterPosition);
	m_mapFrameGray.Update();
	m_playerMap.Init("Assets/sprite/Map/PlayerMap.DDS", PLAYER_WIDTH, PLAYER_HEIGHT);
	m_playerMapGray.Init("Assets/sprite/Map/PlayerMapGray.DDS", PLAYER_WIDTH, PLAYER_HEIGHT);

	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");

	return true;
}

void Map::Update() 
{
	m_playerMapPosition = m_player->GetPosition();
	m_playerMap.SetPosition({ m_playerMapPosition.x * -0.15f + m_mapCenterPosition.x,m_playerMapPosition.z * -0.15f + m_mapCenterPosition.y,0.0f });
	m_playerMapGray.SetPosition({ m_playerMapPosition.x * -0.15f + m_mapCenterPosition.x,m_playerMapPosition.z * -0.15f + m_mapCenterPosition.y,0.0f });

	Quaternion playerRotation;
	playerRotation.SetRotationZ(atan2(g_camera3D->GetForward().x, -g_camera3D->GetForward().z));
	m_playerMap.SetRotation(playerRotation);
	m_playerMapGray.SetRotation(playerRotation);

	m_mapBackGround.Update();
	m_playerMap.Update();
	m_playerMapGray.Update();
	m_mapFrame.Update();
}

void Map::Render(RenderContext& rc) 
{
	m_mapBackGround.Draw(rc);

	//	エネミー
	const auto& enemys = FindGOs<Enemy>("enemy");
	const int enemySize = enemys.size();

	for (auto Enemy : enemys)
	{
		Enemy->EnemyMapGray(rc);
	}

	if (m_game->GetManageState() == enGameState_PlayerAlive)
	{
		for (auto Enemy : enemys)
		{
			Enemy->EnemyMap(rc);
		}
	}

	//	マジックポイント
	const auto& magicPoints = FindGOs<MagicPoint>("magicPoint");
	const int magicSize = magicPoints.size();

	for (auto MagicPoint : magicPoints)
	{
		MagicPoint->MagicPointMapGray(rc);
	}

	if (m_game->GetManageState() == enGameState_PlayerAlive)
	{
		for (auto MagicPoint : magicPoints)
		{
			MagicPoint->MagicPointMap(rc);
		}
	}

	//	プリン
	const auto& puddings = FindGOs<Pudding>("pudding");
	const int puddingSize = puddings.size();

	for (auto Pudding : puddings)
	{
		Pudding->PuddingMapGray(rc);
	}

	if (m_game->GetManageState() == enGameState_PlayerAlive)
	{
		for (auto Pudding : puddings)
		{
			Pudding->PuddingMap(rc);
		}
	}

	m_mapFrameGray.Draw(rc);

	m_playerMapGray.Draw(rc);

	if (m_game->GetManageState() == enGameState_PlayerAlive)
	{
		m_playerMap.Draw(rc);
		m_mapFrame.Draw(rc);
	}
}