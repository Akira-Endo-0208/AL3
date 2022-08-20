#include "RailCamera.h"

void RailCamera::Initialize(ViewProjection& viewProjection) {
	worldTransform_.translation_ = viewProjection.eye;
	worldTransform_.rotation_ = viewProjection.target;

	debugText_ = DebugText::GetInstance();

	viewProjection_.Initialize();
}

void RailCamera::Update() {

	viewProjection_.eye = worldTransform_.translation_;

	Vector3 forward(0, 0, 1);

	forward = worldTransform_.translation_;

	viewProjection_.target = {
	  viewProjection_.eye.x + forward.x,
	  viewProjection_.eye.y + forward.y,
	  viewProjection_.eye.z + forward.z
	};

	//Vector3 up(0, 1, 0);

	//viewProjection_.up = worldTransform_.translation_;

	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();

	debugText_->SetPos(50, 200);
	debugText_->Printf(
	  "Root:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y,viewProjection_.eye.z);
}