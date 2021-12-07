#include "k2EngineLowPreCompile.h"

#include "EffectEngine.h"

namespace nsK2EngineLow {
	EffectEngine* EffectEngine::m_instance = nullptr;	//唯一のインスタンス。

	EffectEngine::EffectEngine()
	{
		K2_ASSERT(
			m_instance == nullptr,
			"EffectEngineのインスタンスを複数作ることはできません。"
		);
		//auto format = DXGI_FORMAT_R8G8B8A8_UNORM;
		auto format = DXGI_FORMAT_R16G16B16A16_FLOAT;
		auto d3dDevice = g_graphicsEngine->GetD3DDevice();
		auto commandQueue = g_graphicsEngine->GetCommandQueue();
		// レンダラーを作成。
		m_renderer = ::EffekseerRendererDX12::Create(
			d3dDevice,
			commandQueue,
			3,
			&format,
			1,
			DXGI_FORMAT_D32_FLOAT,
			false,
			8000
		);
		//メモリプールの作成。
		m_memoryPool = EffekseerRenderer::CreateSingleFrameMemoryPool(m_renderer->GetGraphicsDevice());
		// コマンドリストの作成
		m_commandList = EffekseerRenderer::CreateCommandList(m_renderer->GetGraphicsDevice(), m_memoryPool);
		// エフェクトマネージャーの作成。
		m_manager = ::Effekseer::Manager::Create(8000);

		// 描画モジュールの設定。
		m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
		m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
		m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
		m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
		m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

		// ローダーの設定。
		m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
		m_manager->SetModelLoader(m_renderer->CreateModelLoader());
		m_manager->SetMaterialLoader(m_renderer->CreateMaterialLoader());
		m_manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

		//2D用でも同じことをする。
		//メモリプールの作成。
		m_memoryPool2D = EffekseerRenderer::CreateSingleFrameMemoryPool(m_renderer->GetGraphicsDevice());
		// コマンドリストの作成
		m_commandList2D = EffekseerRenderer::CreateCommandList(m_renderer->GetGraphicsDevice(), m_memoryPool2D);
		// エフェクトマネージャーの作成。
		m_manager2D = ::Effekseer::Manager::Create(8000);

		// 描画モジュールの設定。
		m_manager2D->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
		m_manager2D->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
		m_manager2D->SetRingRenderer(m_renderer->CreateRingRenderer());
		m_manager2D->SetTrackRenderer(m_renderer->CreateTrackRenderer());
		m_manager2D->SetModelRenderer(m_renderer->CreateModelRenderer());

		// ローダーの設定。
		m_manager2D->SetTextureLoader(m_renderer->CreateTextureLoader());
		m_manager2D->SetModelLoader(m_renderer->CreateModelLoader());
		m_manager2D->SetMaterialLoader(m_renderer->CreateMaterialLoader());
		m_manager2D->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

	}
	Effekseer::EffectRef EffectEngine::LoadEffect(const int number)
	{
		Effekseer::EffectRef effect;
		auto it = m_effectMap.find(number);
		if (it != m_effectMap.end()) {
			//ロード済み。
			effect = it->second;
		}
		else {
			//ロードできない。
			//ResistEffectでエフェクト読み込んでね！
			std::abort();
		}
		return effect;
	}

	Effekseer::EffectRef EffectEngine::LoadEffect2D(const int number)
	{
		Effekseer::EffectRef effect;
		auto it = m_effectMap2D.find(number);
		if (it != m_effectMap2D.end()) {
			//ロード済み。
			effect = it->second;
		}
		else {
			//ロードできない。
			//ResistEffectでエフェクト読み込んでね！
			std::abort();
		}
		return effect;
	}

	EffectEngine::~EffectEngine()
	{

	}
	int EffectEngine::Play(Effekseer::EffectRef effect)
	{
		return m_manager->Play(effect, 0, 0, 0);
	}
	int EffectEngine::Play2D(Effekseer::EffectRef effect)
	{
		int handle = m_manager2D->Play(effect, 0, 0, 0);

		//m_manager2D->SetLocation(handle, ef.GetPosition().x, ef.GetPosition().y, ef.GetPosition().y);
		//m_manager2D->SetRotation(handle, ef.GetRotation());
		//m_manager2D->SetScale(handle, ef.GetScale().x, ef.GetScale().y, ef.GetScale().y);
		
		return handle;
	}
	void EffectEngine::Stop(int effectHandle)
	{
		m_manager->StopEffect(effectHandle);
	}
	void EffectEngine::Stop2D(int effectHandle)
	{
		m_manager2D->StopEffect(effectHandle);
	}

	void EffectEngine::Update(float deltaTime)
	{

		m_memoryPool->NewFrame();

		// Begin a command list
		// コマンドリストを開始する。
		EffekseerRendererDX12::BeginCommandList(m_commandList, g_graphicsEngine->GetCommandList());
		m_renderer->SetCommandList(m_commandList);

		m_manager->Update();

		//レンダラーにカメラ行列を設定。
		m_renderer->SetCameraMatrix(*(const Effekseer::Matrix44*)&g_camera3D->GetViewMatrix());
		//レンダラーにプロジェクション行列を設定。
		m_renderer->SetProjectionMatrix(*(const Effekseer::Matrix44*)&g_camera3D->GetProjectionMatrix());

		m_renderer->SetTime(deltaTime);
	}

	void EffectEngine::Update2D(float deltaTime)
	{

		m_memoryPool2D->NewFrame();

		// Begin a command list
		// コマンドリストを開始する。
		EffekseerRendererDX12::BeginCommandList(m_commandList2D, g_graphicsEngine->GetCommandList());
		m_renderer->SetCommandList(m_commandList2D);

		m_manager2D->Update();

		//レンダラーにカメラ行列を設定。
		m_renderer->SetCameraMatrix(*(const Effekseer::Matrix44*)&g_camera2D->GetViewMatrix());
		//レンダラーにプロジェクション行列を設定。
		m_renderer->SetProjectionMatrix(*(const Effekseer::Matrix44*)&g_camera2D->GetProjectionMatrix());

		m_renderer->SetTime(deltaTime);
	}

	void EffectEngine::Draw()
	{
		// Begin to rendering effects
				// エフェクトの描画開始処理を行う。
		m_renderer->BeginRendering();

		// Render effects
		// エフェクトの描画を行う。
		m_manager->Draw();

		// Finish to rendering effects
		// エフェクトの描画終了処理を行う。
		m_renderer->EndRendering();

		// Finish a command list
		// コマンドリストを終了する。
		m_renderer->SetCommandList(nullptr);
		EffekseerRendererDX12::EndCommandList(m_commandList);
	}

	void EffectEngine::Draw2D()
	{
		// Begin to rendering effects
				// エフェクトの描画開始処理を行う。
		m_renderer->BeginRendering();

		// Render effects
		// エフェクトの描画を行う。
		m_manager2D->Draw();

		// Finish to rendering effects
		// エフェクトの描画終了処理を行う。
		m_renderer->EndRendering();

		// Finish a command list
		// コマンドリストを終了する。
		m_renderer->SetCommandList(nullptr);
		EffekseerRendererDX12::EndCommandList(m_commandList2D);
	}


	void EffectEngine::ResistEffect(const int number, const char16_t* filePath)
	{
		Effekseer::EffectRef effect;
		auto it = m_effectMap.find(number);
		if (it == m_effectMap.end()) {
			//新規。
			effect = Effekseer::Effect::Create(m_manager, filePath);
			m_effectMap.insert({ number, effect });
		}
	}

	void EffectEngine::ResistEffect2D(const int number, const char16_t* filePath)
	{
		Effekseer::EffectRef effect;
		auto it = m_effectMap2D.find(number);
		if (it == m_effectMap2D.end()) {
			//新規。
			effect = Effekseer::Effect::Create(m_manager2D, filePath);
			m_effectMap2D.insert({ number, effect });
		}
	}
}