#include "stdafx.h"
#include "Map.h"

#include "Enemy.h"
#include "Game.h"
#include "MagicPoint.h"
#include "Player.h"
#include "Pudding.h"

Map::Map() 
{
}

Map::~Map() 
{
}

bool Map::Start() 
{
	m_mapCenterPosition = { 740.0f, 330.0f, 0.0f };

	m_mapBackGround.Init("Assets/sprite/Map/MapBackGround.DDS", 300.0f, 300.0f);
	m_mapBackGround.SetPosition(m_mapCenterPosition);
	m_mapBackGround.Update();
	m_mapFrame.Init("Assets/sprite/Map/MapFrame.DDS", 300.0f, 300.0f);
	m_mapFrame.SetPosition(m_mapCenterPosition);
	m_mapFrame.Update();
	m_mapFrameGray.Init("Assets/sprite/Map/MapFrameGray.DDS", 300.0f, 300.0f);
	m_mapFrameGray.SetPosition(m_mapCenterPosition);
	m_mapFrameGray.Update();
	m_playerMap.Init("Assets/sprite/Map/PlayerMap.DDS", 200.0f, 200.0f);
	m_playerMapGray.Init("Assets/sprite/Map/PlayerMapGray.DDS", 200.0f, 200.0f);

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

	//エネミー
	const auto& enemys = FindGOs<Enemy>("enemy");
	const int enemySize = enemys.size();

	for (int i = 0; i < enemySize; i++)
	{
		enemys[i]->EnemyMapGray(rc);
	}

	if (m_game->GetManageState() == 0)
	{
		for (int i = 0; i < enemySize; i++)
		{
			enemys[i]->EnemyMap(rc);
		}
	}

	//マジックポイント
	const auto& magicPoints = FindGOs<MagicPoint>("magicPoint");
	const int magicSize = magicPoints.size();

	for (int i = 0; i < magicSize; i++)
	{
		magicPoints[i]->MagicPointMapGray(rc);
	}

	if (m_game->GetManageState() == 0)
	{
		for (int i = 0; i < magicSize; i++)
		{
			magicPoints[i]->MagicPointMap(rc);
		}
	}

	//プリン
	const auto& puddings = FindGOs<Pudding>("pudding");
	const int puddingSize = puddings.size();

	for (int i = 0; i < puddingSize; i++)
	{
		puddings[i]->PuddingMapGray(rc);
	}

	if (m_game->GetManageState() == 0)
	{
		for (int i = 0; i < puddingSize; i++)
		{
			puddings[i]->PuddingMap(rc);
		}
	}

	m_mapFrameGray.Draw(rc);

	m_playerMapGray.Draw(rc);

	if (m_game->GetManageState() == 0)
	{
		m_playerMap.Draw(rc);
		m_mapFrame.Draw(rc);
	}
}