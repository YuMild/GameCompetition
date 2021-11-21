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
	m_mapBackGround.Init("Assets/sprite/MapGround.DDS", 300.0f, 300.0f);
	m_mapBackGround.SetPosition(MAP_CENTER_POSITION);
	m_mapBackGround.Update();

	m_mapGradation.Init("Assets/sprite/MapGradation.DDS", 300.0f, 300.0f);
	m_mapGradation.SetPosition(MAP_CENTER_POSITION);
	m_mapGradation.Update();

	m_mapFrame.Init("Assets/sprite/MapFrame.DDS", 300.0f, 300.0f);
	m_mapFrame.SetPosition(MAP_CENTER_POSITION);
	m_mapFrame.Update();

	m_typeFire.Init("Assets/sprite/TypeFire.DDS", 140.0f, 140.0f);
	m_typeFire.SetPosition(Vector3(840.0f, -260.0f, 0.0f));
	m_typeFire.Update();

	m_typeWater.Init("Assets/sprite/TypeWater.DDS", 140.0f, 140.0f);
	m_typeWater.SetPosition(Vector3(640.0f, -260.0f, 0.0f));
	m_typeWater.Update();

	m_typeWind.Init("Assets/sprite/TypeWind.DDS", 140.0f, 140.0f);
	m_typeWind.SetPosition(Vector3(740.0f, -360.0f, 0.0f));
	m_typeWind.Update();

	m_typeShine.Init("Assets/sprite/TypeShine.DDS", 140.0f, 140.0f);
	m_typeShine.SetPosition(Vector3(740.0f, -160.0f, 0.0f));
	m_typeShine.Update();

	m_hpBar.Init("Assets/sprite/HPbar.DDS", 500.0f, 200.0f);
	m_hpBar.SetPosition(Vector3(540.0f, 300.0f, 0.0f));
	m_hpBar.Update();


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
	m_hpBar.SetIsDisplayRestrictionRightSide(true);
	m_hpBar.SetLimitedX(x);

	m_playerMapPosition = m_player->GetPosition();
	m_playerMap.SetPosition({ m_playerMapPosition.x * -0.085f + MAP_CENTER_POSITION.x,m_playerMapPosition.z * -0.085f + MAP_CENTER_POSITION.y,0.0f });

	//Vector3 m_playerMapDirection = m_player->GetDirection()

	m_mapBackGround.Update();
	m_playerMap.Update();
	m_mapGradation.Update();
	m_mapFrame.Update();
	m_typeFire.Update();
	m_typeWater.Update();
	m_typeWind.Update();
	m_typeShine.Update();
	m_hpBar.Update();
}
void Ui::Render(RenderContext& rc)
{
	m_mapBackGround.Draw(rc);//èáî‘ëÂéñ
	//m_enemyMap.Draw(rc);
	m_playerMap.Draw(rc);
	m_mapGradation.Draw(rc);
	m_mapFrame.Draw(rc);
	m_typeFire.Draw(rc);
	m_typeWater.Draw(rc);
	m_typeWind.Draw(rc);
	m_typeShine.Draw(rc);
	m_hpBar.Draw(rc);
}