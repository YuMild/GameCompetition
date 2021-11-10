#include "stdafx.h"
#include "Background.h"
#include "Bullet.h"

bool BackGround::Start() {
	stagerender.Init("Assets/modelData/stage/stage.tkm");//描画
	stagerender.SetScale({ 1.0f,1.0f,1.0f });//サイズ

	stageposition.x = 0.0f;
	stageposition.y = -50.0f;
	stageposition.z = 0.0f;

	stagerender.SetPosition(stageposition);
	stagerender.Update();//情報の更新

	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	physicsStaticObject.CreateFromModel(stagerender.GetModel(), stagerender.GetModel().GetWorldMatrix());

	return true;
}

void BackGround::Update() {

}

void BackGround::Render(RenderContext& rc) {
	stagerender.Draw(rc);
}