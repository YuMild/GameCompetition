#include "stdafx.h"
#include "Background.h"
#include "Bullet.h"

bool BackGround::Start() {
	stagerender.Init("Assets/modelData/stage/stage.tkm");//�`��
	stagerender.SetScale({ 1.0f,1.0f,1.0f });//�T�C�Y

	stageposition.x = 0.0f;
	stageposition.y = -50.0f;
	stageposition.z = 0.0f;

	stagerender.SetPosition(stageposition);
	stagerender.Update();//���̍X�V

	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	physicsStaticObject.CreateFromModel(stagerender.GetModel(), stagerender.GetModel().GetWorldMatrix());

	return true;
}

void BackGround::Update() {

}

void BackGround::Render(RenderContext& rc) {
	stagerender.Draw(rc);
}