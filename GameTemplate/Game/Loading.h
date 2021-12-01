#pragma once
class Loading : public IGameObject
{
public:
	void FadeIn(){
		m_state = en_In;
	}
	void FadeOut() {
		m_state = en_Out;
	}
	bool FadeNow() {
		return m_state != en_Idle;
	}
	Loading();
	~Loading();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
private:
	enum EnState {
		en_In,
		en_Out,
		en_Idle,
	};
	SpriteRender m_render;
	EnState m_state = en_Idle;
	float m_alpha = 1.0;
};

