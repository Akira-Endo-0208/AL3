#include "RailCamera.h"

void RailCamera::Initialize(Vector3 translate, Vector3 rotate) {

	worldTransform_.Initialize();

	worldTransform_.scale_ = {1.0, 1.0, 1.0};
	worldTransform_.translation_ = translate;
	worldTransform_.rotation_ = rotate;

	debugText_ = DebugText::GetInstance();

	
	viewProjection_.farZ = 3000;
	viewProjection_.Initialize();
}

void RailCamera::Update() {

	worldTransform_.translation_.z -= 0.05f;

	TransferWorldMatrix(
	  worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_,
	  worldTransform_);

	worldTransform_.TransferMatrix();
	viewProjection_.eye = worldTransform_.translation_;

	Vector3 forward(0, 0, 1);

	forward = VectorMatrix(forward,worldTransform_);

	viewProjection_.target = {
	  viewProjection_.eye.x + forward.x,
	  viewProjection_.eye.y + forward.y,
	  viewProjection_.eye.z + forward.z
	};

	Vector3 up(0, 1, 0);

	viewProjection_.up = VectorMatrix(up,worldTransform_);

	
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();

	debugText_->SetPos(50, 200);
	debugText_->Printf(
	  "Root:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y,viewProjection_.eye.z);
}