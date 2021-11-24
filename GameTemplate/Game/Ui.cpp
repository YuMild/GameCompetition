#include "stdafx.h"
#include "Ui.h"

#include "Enemy.h"
#include "Player.h"

Ui::Ui() {

}

Ui::~Ui() {

}

bool Ui::Start()
{
	m_mapCenterPosition = { 740.0f, 330.0f, 0.0f };
	m_clockCenterPosition = { -740.0f, 330.0f, 0.0f };

	//マップ
	m_mapBackGround.Init("Assets/sprite/MapBackGround.DDS", 300.0f, 300.0f);
	m_mapBackGround.SetPosition(m_mapCenterPosition);
	m_mapBackGround.Update();
	m_mapFrame.Init("Assets/sprite/MapFrame.DDS", 300.0f, 300.0f);
	m_mapFrame.SetPosition(m_mapCenterPosition);
	m_mapFrame.Update();

	//時計
	m_clockBackGround.Init("Assets/sprite/ClockBackGround.DDS", 300.0f, 300.0f);
	m_clockBackGround.SetPosition(m_clockCenterPosition);
	m_clockBackGround.Update();
	m_clockMinuteHund.Init("Assets/sprite/ClockMinuteHund.DDS", 300.0f, 300.0f);
	m_clockMinuteHund.SetPosition(m_clockCenterPosition);
	m_clockMinuteHund.Update();
	m_clockSecondHund.Init("Assets/sprite/ClockSecondHund.DDS", 300.0f, 300.0f);
	m_clockSecondHund.SetPosition(m_clockCenterPosition);
	m_clockSecondHund.Update();
	m_clockFrame.Init("Assets/sprite/ClockFrame.DDS", 300.0f, 300.0f);
	m_clockFrame.SetPosition(m_clockCenterPosition);
	m_clockFrame.Update();

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

	m_playerMap.Init("Assets/sprite/PlayerMap.DDS", 200.0f, 200.0f);
	m_player = FindGO<Player>("player");

	return true;
}

void Ui::Update()
{
	float x = 1.0f / 3.0f * m_player->GetHP();
	m_mpBar.SetIsDisplayRestrictionRightSide(true);
	m_mpBar.SetLimitedX(x);

	m_playerMapPosition = m_player->GetPosition();
	m_playerMap.SetPosition({ m_playerMapPosition.x * -0.085f + m_mapCenterPosition.x,m_playerMapPosition.z * -0.085f + m_mapCenterPosition.y,0.0f });

	const auto& enemyList = FindGOs<Enemy>("Enemy");
	int enemySize = enemyList.size();
	for (m_enemyUnit = 0; m_enemyUnit < enemySize; m_enemyUnit++) {
		
		//m_enemyMapPosition = enemyList[m_enemyUnit]->GetPosition();
		//m_enemyMap.SetPosition({ m_enemyMapPosition.x * -0.085f + MAP_CENTER_POSITION.x,m_enemyMapPosition.z * -0.085f + MAP_CENTER_POSITION.y,0.0f });
		//m_enemyMap.Update();
	}
	
	//マップ
	m_mapBackGround.Update();
	m_playerMap.Update();
	m_mapFrame.Update();
	//時計
	m_clockBackGround.Update();
	m_clockMinuteHund.Update();
	m_clockSecondHund.Update();
	m_clockFrame.Update();
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
	//マップ
	m_mapBackGround.Draw(rc);//順番大事
	//m_enemyMap.Draw(rc);
	m_playerMap.Draw(rc);
	m_mapFrame.Draw(rc);
	//時計
	m_clockBackGround.Draw(rc);
	m_clockMinuteHund.Draw(rc);
	m_clockSecondHund.Draw(rc);
	m_clockFrame.Draw(rc);
	//クールタイム
	m_typeFireCoolTime.Draw(rc);
	m_typeWaterCoolTime.Draw(rc);
	m_typeWindCoolTime.Draw(rc);
	m_typeShineCoolTime.Draw(rc);
	//魔法
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
	//MP
	m_mpBar.Draw(rc);
	m_mpFrame.Draw(rc);
}