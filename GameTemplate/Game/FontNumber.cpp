#include "stdafx.h"
#include "FontNumber.h"

FontNumber::FontNumber()
{

}

FontNumber::~FontNumber()
{

}

bool FontNumber::Start()
{
	return true;
}

void FontNumber::Init(int number)
{
	std::string text;
	text = std::to_string(number);

	int digit = text.length();

	std::string filePath;

	for (int i = 0; i < digit; i++)
	{
		char a = text[i];
		filePath = "Assets/sprite/Number/";
		filePath += a;
		filePath += ".DDS";
		std::unique_ptr<SpriteRender> aRender;
		aRender = std::make_unique<SpriteRender>();
		aRender->Init(filePath.c_str(),1000,1000);
		m_fontNumberList.push_back(std::move(aRender));
	}
}

void FontNumber::Update()
{
	for (int i = 0; i < m_fontNumberList.size(); i++)
	{
		m_fontNumberList[i]->SetPosition({ m_position.x + 100.0f * i, m_position.y, m_position.z });
		m_fontNumberList[i]->SetScale(m_scale);
		m_fontNumberList[i]->Update();
	}
}

void FontNumber::Render(RenderContext& rc)
{
	for (int i = 0; i < m_fontNumberList.size(); i++)
	{
		m_fontNumberList[i]->Draw(rc);
	}
}