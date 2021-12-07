#include "k2EngineLowPreCompile.h"
#include "EffectEmitter.h"

namespace nsK2EngineLow {
	EffectEmitter::EffectEmitter()
	{

	}

	EffectEmitter::~EffectEmitter()
	{

	}

	void EffectEmitter::Init(const int number)
	{
		m_effect.Init(number);
	}
	void EffectEmitter::Init2D(const int number)
	{
		m_effect.Init2D(number);
		m_flag2D = true;	//このエフェクトを2Dにする。
	}

	void EffectEmitter::Update()
	{
		if (m_flag2D == false) {
			m_effect.Update();

			if (!IsPlay())
			{
				DeleteGO(this);
			}
		}
		else {
			m_effect.Update2D();

			if (!IsPlay())
			{
				DeleteGO(this);
			}

		}

	}
}