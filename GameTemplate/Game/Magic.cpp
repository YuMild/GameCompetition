#include "stdafx.h"
#include "Magic.h"

#include "Player.h"

Magic::Magic() {
}
Magic::~Magic() {
}

bool Magic::Start() {
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

	m_player = FindGO<Player>("player");

	return true;
}

void Magic::Update() {
	m_typeFire.Update();
	m_typeWater.Update();
	m_typeWind.Update();
	m_typeShine.Update();
	m_typeFireCoolTime.Update();
	m_typeWaterCoolTime.Update();
	m_typeWindCoolTime.Update();
	m_typeShineCoolTime.Update();
}

void Magic::Render(RenderContext& rc) {
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
}