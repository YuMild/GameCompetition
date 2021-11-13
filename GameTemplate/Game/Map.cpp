#include "stdafx.h"
#include "Map.h"

#include "Player.h"

namespace
{
	const Vector3 MAP_ORIGIN  = Vector3(640.0f, 220.0f, 0.0f);

	const float MAP_RADIUS = 300.0f;
	const float LIMITED_RANGE_IMAGE = 600.0f;
}

Map::Map() {

}
Map::~Map() {

}
bool Map::Start() {

	m_map.Init("Assets/sprite/Map.dds", 300.0f, 300.0f);
	m_map.SetPosition({ 790.0f,370.0f,0.0f });
	m_map.Update();
	m_mapFrame.Init("Assets/sprite/MapFrame.dds", 300.0f, 300.0f);
	m_mapFrame.SetPosition({ 790.0f,370.0f,0.0f });
	m_mapFrame.Update();
	m_enemyMap.Init("Assets/sprite/EnemyMap.dds", 300.0f, 300.0f);
	m_enemyMap.SetPosition({ 790.0f,370.0f,0.0f });
	m_enemyMap.Update();
	m_playerMap.Init("Assets/sprite/PlayerMap.dds", 300.0f, 300.0f);
	m_playerMap.SetPosition({ 790.0f,370.0f,0.0f });
	m_playerMap.Update();
	
	return true;
}
void Map::Update() {
	Vector3 playerMapPosition = m_player->GetPosition();
	Vector3 enemyMapPosition = m_enemy->GetPosition();
}
const bool Map::WorldPositionConvertToMapPosition(Vector3 worldCenterPosition, Vector3 worldPosition, Vector3& mapPosition)
{
	//Y座標はマップの座標とは関係ないので、0にする。
	worldCenterPosition.y = 0.0f;
	worldPosition.y = 0.0f;
	Vector3 diff = worldPosition - worldCenterPosition;
	//マップの中心とするオブジェクトとの距離が一定以上離れていたら。

	if (diff.LengthSq() >= LIMITED_RANGE_IMAGE * LIMITED_RANGE_IMAGE)
	{
		//表示しないようにする。
		return false;
	}

	//ベクトルの長さを取得。
	float length = diff.Length();

	//カメラの前方向ベクトルから。
	//クォータニオンを生成。
	Vector3 forward = g_camera3D->GetForward();
	Quaternion rot;
	rot.SetRotationY(atan2(-forward.x, forward.z));

	//ベクトルにカメラの回転を適用。
	rot.Apply(diff);

	//ベクトルを正規化。
	diff.Normalize();

	//マップの大きさ/距離制限で。
	//ベクトルをマップ座標系に変換する。
	diff *= length * MAP_RADIUS / LIMITED_RANGE_IMAGE;

	//マップの中央座標と上記ベクトルを加算する。
	mapPosition = Vector3(MAP_ORIGIN.x + diff.x, MAP_ORIGIN.y + diff.z, 0.0f);
	return true;
}
void Map::Render(RenderContext& rc) {
	m_map.Draw(rc);
	m_mapFrame.Draw(rc);
	m_enemyMap.Draw(rc);
	m_playerMap.Draw(rc);
}