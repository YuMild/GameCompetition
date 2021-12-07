/*!
 * @brief	�G�t�F�N�g
 */

#include "k2EngineLowPreCompile.h"
#include "Effect.h"

namespace nsK2EngineLow {

	Effect::Effect()
	{
	}
	Effect::~Effect()
	{

	}


	void Effect::Init(const int number)
	{
		m_effect = EffectEngine::GetInstance()->LoadEffect(number);

	}
	void Effect::Init2D(const int number)
	{
		m_effect = EffectEngine::GetInstance()->LoadEffect2D(number);

	}
	void Effect::Play()
	{
		//�Đ����̃G�t�F�N�g���~����B
		EffectEngine::GetInstance()->Stop(m_handle);
		//�V�����Đ��B
		m_handle = EffectEngine::GetInstance()->Play(m_effect);
	}
	void Effect::Play2D()
	{
		//�Đ����̃G�t�F�N�g���~����B
		EffectEngine::GetInstance()->Stop2D(m_handle);
		//�V�����Đ��B
		m_handle = EffectEngine::GetInstance()->Play2D(m_effect);
	}
	void Effect::Update()
	{
		EffectEngine::GetInstance()->UpdateEffectWorldMatrix(
			m_handle,
			m_position,
			m_rotation,
			m_scale
		);
	}
	void Effect::Update2D()
	{
		EffectEngine::GetInstance()->UpdateEffectWorldMatrix2D(
			m_handle,
			m_position,
			m_rotation,
			m_scale
		);
	}
}