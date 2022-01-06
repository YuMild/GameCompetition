#include "stdafx.h"
#include "FontPurpleNumber.h"

FontPurpleNumber::FontPurpleNumber()
{

}

FontPurpleNumber::~FontPurpleNumber()
{

}

bool FontPurpleNumber::Start()
{
	return true;
}

void FontPurpleNumber::Init(int number)
{
	std::string text;
	text = std::to_string(number);

	int digit = text.length();

	std::string filePath;

	for (int i = 0; i < digit; i++)
	{
		char a = text[i];
		filePath = "Assets/sprite/Result/PurpleNumber/";
		filePath += a;
		filePath += ".DDS";
		std::unique_ptr<SpriteRender> aRender;
		aRender = std::make_unique<SpriteRender>();
		aRender->Init(filePath.c_str(), 1000, 1000);
		m_fontPurpleNumberList.push_back(std::move(aRender));
	}
}

void FontPurpleNumber::Update()
{
	int j = 0;
	for (int i = m_fontPurpleNumberList.size() - 1; i >= 0; i--)
	{
		m_fontPurpleNumberList[i]->SetPosition({ m_position.x - 90.0f * j, m_position.y, m_position.z });
		m_fontPurpleNumberList[i]->SetScale(m_scale);
		m_fontPurpleNumberList[i]->Update();
		j++;
	}
}

void FontPurpleNumber::Render(RenderContext& rc)
{
	for (int i = 0; i < m_fontPurpleNumberList.size(); i++)
	{
		m_fontPurpleNumberList[i]->Draw(rc);
	}
}