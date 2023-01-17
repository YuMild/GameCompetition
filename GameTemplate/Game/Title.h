#pragma once

class Fade;
class TitleUi;

/// <summary>
/// �^�C�g��
/// </summary>
class Title : public IGameObject
{
public:

	Title();
	~Title();

	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

	/// <summary>
	/// �X�e�[�g
	/// </summary>
	void State();

	/// <summary>
	/// �^�C�}�[
	/// </summary>
	void Timer();

private:

	//�w�i
	SpriteRender		m_titleRender;

	//PressStart
	SpriteRender		m_pressStartRender;

	//�A�C�R��
	//����������������O��
	SpriteRender		m_heart1;						//�n�[�g
	SpriteRender		m_heart2;				
	SpriteRender		m_heart3;				
	SpriteRender		m_fire1;						//��
	SpriteRender		m_fire2;
	SpriteRender		m_water1;						//��
	SpriteRender		m_water2;
	SpriteRender		m_wind1;						//��
	SpriteRender		m_wind2;
	SpriteRender		m_shine1;						//��
	SpriteRender		m_shine2;

	//�|�W�V����
	Vector3				m_heart1Position;				//�n�[�g
	Vector3				m_heart2Position;
	Vector3				m_heart3Position;
	Vector3				m_fire1Position;				//��
	Vector3				m_fire2Position;
	Vector3				m_water1Position;				//��
	Vector3				m_water2Position;
	Vector3				m_wind1Position;				//��
	Vector3				m_wind2Position;
	Vector3				m_shine1Position;				//��
	Vector3				m_shine2Position;

	//����
	SoundSource*		m_titleBGM		= nullptr;		//�w�i
	SoundSource*		m_buttonSE;						//�{�^���������ꂽ��

	Fade*				m_fade			= nullptr;
	TitleUi*			m_titleUi		= nullptr;

	bool				m_isWaitFadeOut	= false;
	float				m_alpha			= 0.0f;

	//�A�C�R�����㉺�ɓ�������
	float				m_timer1		= 0;
	float				m_upDown1		= 0;
	float				m_timer2		= 0;
	float				m_upDown2		= 0;
	float				m_timer3		= 0;
	float				m_upDown3		= 0;
	float				m_timer4		= 0;
	float				m_upDown4		= 0;
	float				m_timer5		= 0;
	float				m_upDown5		= 0;
};