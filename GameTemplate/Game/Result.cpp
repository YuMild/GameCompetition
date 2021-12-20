#include "stdafx.h"
#include "Result.h"

#include "FontNumber.h"
#include "Score.h"
#include "Title.h"
#include "sound/SoundEngine.h"

Result::Result()
{

}

Result::~Result()
{

}

bool Result::Start()
{
	
	m_render.Init("Assets/sprite/GameOver.dds", 1920.0f, 1080.0f);

	m_score = FindGO<Score>("score");
	
	m_resultScore = m_score->GetScore();

	m_fontNumber = NewGO<FontNumber>(0, "fontNumber");
	m_fontNumber->Init(m_resultScore);
	m_fontNumber->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	m_fontNumber->SetScale(Vector3(1.0f, 1.0f, 1.0f));

	return true;
}

void Result::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}

void Result::Render(RenderContext& rc)
{
	m_render.Draw(rc);
}