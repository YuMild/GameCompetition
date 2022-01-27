#include "stdafx.h"
#include "Magic.h"

#include "Game.h"
#include "Mp.h"
#include "Player.h"

namespace
{
	const float WIDTH = 110.0f;
	const float HEIGHT = 110.0f;

	const float FRAME_WIDTH = 130.0f;
	const float FRAME_HEIGHT = 130.0f;

	const float FIRE_X = 840.0f;
	const float WATER_X = 640.0f;
	const float WIND_X = 740.0f;
	const float SHINE_X = 740.0f;

	const float FIRE_Y = -270.0f;
	const float WATER_Y = -270.0f;
	const float WIND_Y = -370.0f;
	const float SHINE_Y = -170.0f;
}

Magic::Magic()
{

}

Magic::~Magic()
{

}

bool Magic::Start()
{
	//魔法クールタイム
	m_typeFireCoolTime.Init("Assets/sprite/Magic/TypeFireGray.DDS", WIDTH, HEIGHT);
	m_typeFireCoolTime.SetPosition(Vector3(FIRE_X, FIRE_Y, 0.0f));
	m_typeFireCoolTime.Update();
	m_typeWaterCoolTime.Init("Assets/sprite/Magic/TypeWaterGray.DDS", WIDTH, HEIGHT);
	m_typeWaterCoolTime.SetPosition(Vector3(WATER_X, WATER_Y, 0.0f));
	m_typeWaterCoolTime.Update();
	m_typeWindCoolTime.Init("Assets/sprite/Magic/TypeWindGray.DDS", WIDTH, HEIGHT);
	m_typeWindCoolTime.SetPosition(Vector3(WIND_X, WIND_Y, 0.0f));
	m_typeWindCoolTime.Update();
	m_typeShineCoolTime.Init("Assets/sprite/Magic/TypeShineGray.DDS", WIDTH, HEIGHT);
	m_typeShineCoolTime.SetPosition(Vector3(SHINE_X, SHINE_Y, 0.0f));
	m_typeShineCoolTime.Update();

	//魔法
	m_typeFire.Init("Assets/sprite/Magic/TypeFireInside.DDS", WIDTH, HEIGHT);
	m_typeFire.SetPosition(Vector3(FIRE_X, FIRE_Y, 0.0f));
	m_typeFire.Update();
	m_typeWater.Init("Assets/sprite/Magic/TypeWaterInside.DDS", WIDTH, HEIGHT);
	m_typeWater.SetPosition(Vector3(WATER_X, WATER_Y, 0.0f));
	m_typeWater.Update();
	m_typeWind.Init("Assets/sprite/Magic/TypeWindInside.DDS", WIDTH, HEIGHT);
	m_typeWind.SetPosition(Vector3(WIND_X, WIND_Y, 0.0f));
	m_typeWind.Update();
	m_typeShine.Init("Assets/sprite/Magic/TypeShineInside.DDS", WIDTH, HEIGHT);
	m_typeShine.SetPosition(Vector3(SHINE_X, SHINE_Y, 0.0f));
	m_typeShine.Update();

	//鎖
	m_fireChain.Init("Assets/sprite/Magic/Chain.DDS", WIDTH, HEIGHT);
	m_fireChain.SetPosition(Vector3(FIRE_X, FIRE_Y, 0.0f));
	m_fireChain.Update();
	m_waterChain.Init("Assets/sprite/Magic/Chain.DDS", WIDTH, HEIGHT);
	m_waterChain.SetPosition(Vector3(WATER_X, WATER_Y, 0.0f));
	m_waterChain.Update();
	m_windChain.Init("Assets/sprite/Magic/Chain.DDS", WIDTH, HEIGHT);
	m_windChain.SetPosition(Vector3(WIND_X, WIND_Y, 0.0f));
	m_windChain.Update();
	m_shineChain.Init("Assets/sprite/Magic/Chain.DDS", WIDTH, HEIGHT);
	m_shineChain.SetPosition(Vector3(SHINE_X, SHINE_Y, 0.0f));
	m_shineChain.Update();

	//魔法フレーム
	Vector3 positionList[4];
	positionList[0] = Vector3(FIRE_X, FIRE_Y, 0.0f);
	positionList[1] = Vector3(WATER_X, WATER_Y, 0.0f);
	positionList[2] = Vector3(WIND_X, WIND_Y, 0.0f);
	positionList[3] = Vector3(SHINE_X, SHINE_Y, 0.0f);

	for (int j = 0; j < m_num; j++)
	{
		m_typeFrameGray[j].Init("Assets/sprite/Magic/TypeFrameGray.DDS", FRAME_WIDTH, FRAME_HEIGHT);
		m_typeFrameGray[j].SetPosition(positionList[j]);
		m_typeFrameGray[j].Update();
	}

	for (int j = 0; j < m_num; j++)
	{
		m_typeFrame[j].Init("Assets/sprite/Magic/TypeFrame.DDS", FRAME_WIDTH, FRAME_HEIGHT);
		m_typeFrame[j].SetPosition(positionList[j]);
		m_typeFrame[j].Update();
	}

	//参照
	m_game = FindGO<Game>("game");
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
	float water = m_player->GetWaterCoolTimer() / m_player->COOLTIME_WATER;
	float wind = m_player->GetWindCoolTimer() / m_player->COOLTIME_WIND;
	float shine = m_player->GetShineCoolTimer() / m_player->COOLTIME_SHINE;

	m_typeFire.SetIsDisplayRestrictionDownSide(false);
	m_typeFire.SetLimitedY(fire);
	m_typeWater.SetIsDisplayRestrictionDownSide(false);
	m_typeWater.SetLimitedY(water);
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
	for (int j = 0; j < m_num; j++)
	{
		m_typeFrameGray[j].Draw(rc);
	}
	
	if (m_game->GetManageState() == 0)
	{
		m_typeFire.Draw(rc);
		m_typeWater.Draw(rc);
		m_typeWind.Draw(rc);
		m_typeShine.Draw(rc);
		for (int j = 0; j < m_num; j++)
		{
			m_typeFrame[j].Draw(rc);
		}
	}

	if (m_mp->GetMP() < m_player->GetFireMP()) {
		m_fireChain.Draw(rc);
	}
	if (m_mp->GetMP() < m_player->GetWaterMP()) {
		m_waterChain.Draw(rc);
	}
	if (m_mp->GetMP() < m_player->GetWindMP()) {
		m_windChain.Draw(rc);
	}
	if (m_mp->GetMP() < m_player->GetShineMP()) {
		m_shineChain.Draw(rc);
	}
}