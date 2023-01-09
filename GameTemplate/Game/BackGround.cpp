#include "stdafx.h"
#include "BackGround.h"

namespace
{
	const float STAGE_SIZE = 1.5f;
}

bool BackGround::Start()
{
	m_stageMR.Init("Assets/modelData/stage.tkm");
	m_stageMR.SetScale(Vector3::One * STAGE_SIZE);

	m_stageMR.SetPosition({ 0.0f,-70.0f,0.0f });
	m_stageMR.Update();

	m_physicsStaticObject.CreateFromModel(m_stageMR.GetModel(), m_stageMR.GetModel().GetWorldMatrix());

	return true;
}

void BackGround::Update()
{
}

void BackGround::Render(RenderContext& rc) 
{
	m_stageMR.Draw(rc);
}