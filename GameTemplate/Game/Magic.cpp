#include "stdafx.h"
#include "Magic.h"

#include "Mp.h"
#include "Player.h"

Magic::Magic()
{
}

Magic::~Magic()
{
}

bool Magic::Start()
{
	//魔法クールタイム
	m_typeFireCoolTime.Init("Assets/sprite/TypeFireCoolTime.DDS", 110.0f, 110.0f);
	m_typeFireCoolTime.SetPosition(Vector3(840.0f, -270.0f, 0.0f));
	m_typeFireCoolTime.Update();
	m_typeWaterCoolTime.Init("Assets/sprite/TypeWaterCoolTime.DDS", 110.0f, 110.0f);
	m_typeWaterCoolTime.SetPosition(Vector3(640.0f, -270.0f, 0.0f));
	m_typeWaterCoolTime.Update();
	m_typeWindCoolTime.Init("Assets/sprite/TypeWindCoolTime.DDS", 110.0f, 110.0f);
	m_typeWindCoolTime.SetPosition(Vector3(740.0f, -370.0f, 0.0f));
	m_typeWindCoolTime.Update();
	m_typeShineCoolTime.Init("Assets/sprite/TypeShineCoolTime.DDS", 110.0f, 110.0f);
	m_typeShineCoolTime.SetPosition(Vector3(740.0f, -170.0f, 0.0f));
	m_typeShineCoolTime.Update();

	//魔法
	m_typeFire.Init("Assets/sprite/TypeFireInside.DDS", 110.0f, 110.0f);
	m_typeFire.SetPosition(Vector3(840.0f, -270.0f, 0.0f));
	m_typeFire.Update();
	m_typeWater.Init("Assets/sprite/TypeWaterInside.DDS", 110.0f, 110.0f);
	m_typeWater.SetPosition(Vector3(640.0f, -270.0f, 0.0f));
	m_typeWater.Update();
	m_typeWind.Init("Assets/sprite/TypeWindInside.DDS", 110.0f, 110.0f);
	m_typeWind.SetPosition(Vector3(740.0f, -370.0f, 0.0f));
	m_typeWind.Update();
	m_typeShine.Init("Assets/sprite/TypeShineInside.DDS", 110.0f, 110.0f);
	m_typeShine.SetPosition(Vector3(740.0f, -170.0f, 0.0f));
	m_typeShine.Update();

	//鎖
	m_fireChain.Init("Assets/sprite/Chain.DDS", 110.0f, 110.0f);
	m_fireChain.SetPosition(Vector3(840.0f, -270.0f, 0.0f));
	m_fireChain.Update();
	m_waterChain.Init("Assets/sprite/Chain.DDS", 110.0f, 110.0f);
	m_waterChain.SetPosition(Vector3(640.0f, -270.0f, 0.0f));
	m_waterChain.Update();
	m_windChain.Init("Assets/sprite/Chain.DDS", 110.0f, 110.0f);
	m_windChain.SetPosition(Vector3(740.0f, -370.0f, 0.0f));
	m_windChain.Update();
	m_shineChain.Init("Assets/sprite/Chain.DDS", 110.0f, 110.0f);
	m_shineChain.SetPosition(Vector3(740.0f, -170.0f, 0.0f));
	m_shineChain.Update();

	//魔法フレーム
	Vector3 positionList[4];
	positionList[0] = Vector3(840.0f, -270.0f, 0.0f);
	positionList[1] = Vector3(740.0f, -370.0f, 0.0f);
	positionList[2] = Vector3(640.0f, -270.0f, 0.0f);
	positionList[3] = Vector3(740.0f, -170.0f, 0.0f);

	for (int j = 0; j < m_num; j++)
	{
		m_typeFrame[j].Init("Assets/sprite/TypeFrame.DDS", 130.0f, 130.0f);
		m_typeFrame[j].SetPosition(positionList[j]);
		m_typeFrame[j].Update();
	}

	//参照
	m_mp = FindGO<Mp>("mp");
	m_player = FindGO<Player>("player");

	return true;
}

void Magic::Update()
{
	Cut();
}

void Magic::Cut() 
{
	float fire = m_player->GetFireCoolTimer() / m_player->COOLTIME_FIRE;
	float wind = m_player->GetWindCoolTimer() / m_player->COOLTIME_WIND;
	float shine = m_player->GetShineCoolTimer() / m_player->COOLTIME_SHINE;

	m_typeFire.SetIsDisplayRestrictionDownSide(false);
	m_typeFire.SetLimitedY(fire);
	m_typeWind.SetIsDisplayRestrictionDownSide(false);
	m_typeWind.SetLimitedY(wind);
	m_typeShine.SetIsDisplayRestrictionDownSide(false);
	m_typeShine.SetLimitedY(shine);
}

void Magic::Render(RenderContext& rc)
{
	m_typeFireCoolTime.Draw(rc);
	m_typeWaterCoolTime.Draw(rc);
	m_typeWindCoolTime.Draw(rc);
	m_typeShineCoolTime.Draw(rc);

	m_typeFire.Draw(rc);
	m_typeWater.Draw(rc);
	m_typeWind.Draw(rc);
	m_typeShine.Draw(rc);

	if (m_mp->GetMP() < m_player->GetFireMP()) {
		m_fireChain.Draw(rc);
	}
	if (m_mp->GetMP() < m_player->GetWindMP()) {
		m_windChain.Draw(rc);
	}
	if (m_mp->GetMP() < m_player->GetShineMP()) {
		m_shineChain.Draw(rc);
	}

	for (int j = 0; j < m_num; j++)
	{
		m_typeFrame[j].Draw(rc);
	}
}