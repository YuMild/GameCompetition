#include "stdafx.h"
#include "BackGround.h"

bool BackGround::Start() {
	render.Init("Assets/modelData/stage.tkm");
	render.SetScale({ 1.0f,1.0f,1.0f });

	position.x = 0.0f;
	position.y = -500.0f;
	position.z = 0.0f;

	render.SetPosition(position);
	render.Update();

	physicsStaticObject.CreateFromModel(render.GetModel(), render.GetModel().GetWorldMatrix());

	return true;
}

void BackGround::Update() {

}

void BackGround::Render(RenderContext& rc) {
	render.Draw(rc);
}