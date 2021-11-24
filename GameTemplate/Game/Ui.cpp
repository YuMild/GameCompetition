#include "stdafx.h"
#include "Ui.h"

#include "Enemy.h"
#include "Player.h"

namespace
{
	Vector3 MAP_CENTER_POSITION = Vector3(740.0f, 330.0f, 0.0f);
}

Ui::Ui() {

}

Ui::~Ui() {

}

bool Ui::Start()
{
	//マップ
	m_mapBackGround.Init("Assets/sprite/MapGround.DDS", 300.0f, 300.0f);
	m_mapBackGround.SetPosition(MAP_CENTER_POSITION);
	m_mapBackGround.Update();

	m_mapGradation.Init("Assets/sprite/MapGradation.DDS", 300.0f, 300.0f);
	m_mapGradation.SetPosition(MAP_CENTER_POSITION);
	m_mapGradation.Update();

	m_mapFrame.Init("Assets/sprite/MapFrame.DDS", 300.0f, 300.0f);
	m_mapFrame.SetPosition(MAP_CENTER_POSITION);
	m_mapFrame.Update();
	
	//クールタイム
	m_typeFireCoolTime.Init("Assets/sprite/TypeFireCoolTime.DDS", 120.0f, 120.0f);
	m_typeFireCoolTime.SetPosition(Vector3(840.0f, -270.0f, 0.0f));
	m_typeFireCoolTime.Update();

	m_typeWaterCoolTime.Init("Assets/sprite/TypeWaterCoolTime.DDS", 120.0f, 120.0f);
	m_typeWaterCoolTime.SetPosition(Vector3(640.0f, -270.0f, 0.0f));
	m_typeWaterCoolTime.Update();

	m_typeWindCoolTime.Init("Assets/sprite/TypeWindCoolTime.DDS", 120.0f, 120.0f);
	m_typeWindCoolTime.SetPosition(Vector3(740.0f, -370.0f, 0.0f));
	m_typeWindCoolTime.Update();

	m_typeShineCoolTime.Init("Assets/sprite/TypeShineCoolTime.DDS", 120.0f, 120.0f);
	m_typeShineCoolTime.SetPosition(Vector3(740.0f, -170.0f, 0.0f));
	m_typeShineCoolTime.Update();

	//魔法
	m_typeFire.Init("Assets/sprite/TypeFire.DDS", 120.0f, 120.0f);
	m_typeFire.SetPosition(Vector3(840.0f, -270.0f, 0.0f));
	m_typeFire.Update();

	m_typeWater.Init("Assets/sprite/TypeWater.DDS", 120.0f, 120.0f);
	m_typeWater.SetPosition(Vector3(640.0f, -270.0f, 0.0f));
	m_typeWater.Update();

	m_typeWind.Init("Assets/sprite/TypeWind.DDS", 120.0f, 120.0f);
	m_typeWind.SetPosition(Vector3(740.0f, -370.0f, 0.0f));
	m_typeWind.Update();

	m_typeShine.Init("Assets/sprite/TypeShine.DDS", 120.0f, 120.0f);
	m_typeShine.SetPosition(Vector3(740.0f, -170.0f, 0.0f));
	m_typeShine.Update();

	//MPフレーム
	m_mpFrame.Init("Assets/sprite/MPFrame.DDS", 600.0f, 600.0f);
	m_mpFrame.SetPosition(Vector3(-560.0f, -340.0f, 0.0f));
	m_mpFrame.Update();

	//MPバー
	m_mpBar.Init("Assets/sprite/MPbar.DDS", 500.0f, 800.0f);
	m_mpBar.SetPosition(Vector3(-520.0f, -390.0f, 0.0f));
	m_mpBar.Update();

	/*const auto& enemyList = FindGOs<Enemy>("Enemy");
	int size = enemyList.size();
	for (int i = 0; i < size; i++) {
		m_enemysMap[i].Init("Assets/sprite/EnemyMap.DDS");
		m_enemyMapPosition = enemyList[i]->GetPosition();
		m_enemysMap.SetPosition({ m_enemyMapPosition.x * -0.085f + MAP_CENTER_POSITION.x,m_enemyMapPosition.z * -0.085f + MAP_CENTER_POSITION.y,0.0f });
		m_enemysMap.Update();
	}*/
	
	m_playerMap.Init("Assets/sprite/PlayerMap.DDS", 200.0f, 200.0f);

	m_playerMap.SetIsDisplayRestrictionRightSide(true);

	m_player = FindGO<Player>("player");
	
	return true;
}

void Ui::Update()
{
	float x = 1.0f / 3.0f * m_player->GetHP();
	m_mpBar.SetIsDisplayRestrictionRightSide(true);
	m_mpBar.SetLimitedX(x);

	m_playerMapPosition = m_player->GetPosition();
	m_playerMap.SetPosition({ m_playerMapPosition.x * -0.085f + MAP_CENTER_POSITION.x,m_playerMapPosition.z * -0.085f + MAP_CENTER_POSITION.y,0.0f });

	//Vector3 m_playerMapDirection = m_player->GetDirection()

	//マップ
	m_mapBackGround.Update();
	m_playerMap.Update();
	m_mapGradation.Update();
	m_mapFrame.Update();
	//魔法
	m_typeFire.Update();
	m_typeWater.Update();
	m_typeWind.Update();
	m_typeShine.Update();
	//クールタイム
	m_typeFireCoolTime.Update();
	m_typeWaterCoolTime.Update();
	m_typeWindCoolTime.Update();
	m_typeShineCoolTime.Update();
	//MPバー
	m_mpBar.Update();
	m_mpFrame.Update();
}
void Ui::Render(RenderContext& rc)
{
	m_mapBackGround.Draw(rc);//順番大事
	//m_enemyMap.Draw(rc);
	m_playerMap.Draw(rc);
	m_mapGradation.Draw(rc);
	m_mapFrame.Draw(rc);

	m_typeFireCoolTime.Draw(rc);
	m_typeWaterCoolTime.Draw(rc);
	m_typeWindCoolTime.Draw(rc);
	m_typeShineCoolTime.Draw(rc);

	if (m_player->GetFire() == true) {
		m_typeFire.Draw(rc);
	}

	m_typeWater.Draw(rc);

	if (m_player->GetWind() == true) {
		m_typeWind.Draw(rc);
	}
	
	if (m_player->GetShine() == true) {
		m_typeShine.Draw(rc);
	}

	m_mpBar.Draw(rc);
	m_mpFrame.Draw(rc);
}