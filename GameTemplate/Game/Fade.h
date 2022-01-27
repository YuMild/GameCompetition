#pragma once

/// <summary>
/// �t�F�[�h
/// </summary>
class Fade : public IGameObject
{
public:
	Fade();
	~Fade();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	/// <summary>
	/// �t�F�[�h�C��
	/// </summary>
	void StartFadeIn()
	{
		m_state = enState_FadeIn;
	}

	/// <summary>
	/// �t�F�[�h�A�E�g
	/// </summary>
	void StartFadeOut()
	{
		m_state = enState_FadeOut;
	}

	/// <summary>
	/// �t�F�[�h�����H
	/// </summary>
	/// <returns>�t�F�[�h���Ȃ�true</returns>
	const bool IsFade() const
	{
		return m_state != enState_Idle;
	}

	/// <summary>
	/// ���l���擾
	/// </summary>
	/// <returns>���l</returns>
	const float GetCurrentAlpha() const
	{
		return m_currentAlpha;
	}

private:

	enum EnState {
		enState_FadeIn,			//�t�F�[�h�C����
		enState_FadeOut,		//�t�F�[�h�A�E�g��
		enState_Idle,			//�A�C�h����
	};

	SpriteRender		m_spriteRender;				//�X�v���C�g�����_�\

	EnState				m_state = enState_Idle;		//���

	float				m_currentAlpha = 1.0f;		//���݂̃��l
};


