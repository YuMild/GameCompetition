#include "stdafx.h"
#include "Magic.h"

#include "Game.h"
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
	//���@�N�[���^�C��
	m_typeFireCoolTime.Init("Assets/sprite/Magic/TypeFireGray.DDS", 110.0f, 110.0f);
	m_typeFireCoolTime.SetPosition(Vector3(840.0f, -270.0f, 0.0f));
	m_typeFireCoolTime.Update();
	m_typeWaterCoolTime.Init("Assets/sprite/Magic/TypeWaterGray.DDS", 110.0f, 110.0f);
	m_typeWaterCoolTime.SetPosition(Vector3(640.0f, -270.0f, 0.0f));
	m_typeWaterCoolTime.Update();
	m_typeWindCoolTime.Init("Assets/sprite/Magic/TypeWindGray.DDS", 110.0f, 110.0f);
	m_typeWindCoolTime.SetPosition(Vector3(740.0f, -370.0f, 0.0f));
	m_typeWindCoolTime.Update();
	m_typeShineCoolTime.Init("Assets/sprite/Magic/TypeShineGray.DDS", 110.0f, 110.0f);
	m_typeShineCoolTime.SetPosition(Vector3(740.0f, -170.0f, 0.0f));
	m_typeShineCoolTime.Update();

	//���@
	m_typeFire.Init("Assets/sprite/Magic/TypeFireInside.DDS", 110.0f, 110.0f);
	m_typeFire.SetPosition(Vector3(840.0f, -270.0f, 0.0f));
	m_typeFire.Update();
	m_typeWater.Init("Assets/sprite/Magic/TypeWaterInside.DDS", 110.0f, 110.0f);
	m_typeWater.SetPosition(Vector3(640.0f, -270.0f, 0.0f));
	m_typeWater.Update();
	m_typeWind.Init("Assets/sprite/Magic/TypeWindInside.DDS", 110.0f, 110.0f);
	m_typeWind.SetPosition(Vector3(740.0f, -370.0f, 0.0f));
	m_typeWind.Update();
	m_typeShine.Init("Assets/sprite/Magic/TypeShineInside.DDS", 110.0f, 110.0f);
	m_typeShine.SetPosition(Vector3(740.0f, -170.0f, 0.0f));
	m_typeShine.Update();

	//��
	m_fireChain.Init("Assets/sprite/Magic/Chain.DDS", 110.0f, 110.0f);
	m_fireChain.SetPosition(Vector3(840.0f, -270.0f, 0.0f));
	m_fireChain.Update();
	m_waterChain.Init("Assets/sprite/Magic/Chain.DDS", 110.0f, 110.0f);
	m_waterChain.SetPosition(Vector3(640.0f, -270.0f, 0.0f));
	m_waterChain.Update();
	m_windChain.Init("Assets/sprite/Magic/Chain.DDS", 110.0f, 110.0f);
	m_windChain.SetPosition(Vector3(740.0f, -370.0f, 0.0f));
	m_windChain.Update();
	m_shineChain.Init("Assets/sprite/Magic/Chain.DDS", 110.0f, 110.0f);
	m_shineChain.SetPosition(Vector3(740.0f, -170.0f, 0.0f));
	m_shineChain.Update();

	//���@�t���[��
	Vector3 positionList[4];
	positionList[0] = Vector3(840.0f, -270.0f, 0.0f);
	positionList[1] = Vector3(740.0f, -370.0f, 0.0f);
	positionList[2] = Vector3(640.0f, -270.0f, 0.0f);
	positionList[3] = Vector3(740.0f, -170.0f, 0.0f);

	for (int j = 0; j < m_num; j++)
	{
		m_typeFrameGray[j].Init("Assets/sprite/Magic/TypeFrameGray.DDS", 130.0f, 130.0f);
		m_typeFrameGray[j].SetPosition(positionList[j]);
		m_typeFrameGray[j].Update();
	}

	for (int j = 0; j < m_num; j++)
	{
		m_typeFrame[j].Init("Assets/sprite/Magic/TypeFrame.DDS", 130.0f, 130.0f);
		m_typeFrame[j].SetPosition(positionList[j]);
		m_typeFrame[j].Update();
	}

	//�Q��
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
	if (m_mp->GetMP() < m_player->GetWindMP()) {
		m_windChain.Draw(rc);
	}
	if (m_mp->GetMP() < m_player->GetShineMP()) {
		m_shineChain.Draw(rc);
	}
}