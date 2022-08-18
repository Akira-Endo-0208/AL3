#include "RailCamera.h"

void RailCamera::Initialize(ViewProjection& viewProjection_) {
	worldTransform_.translation_ = viewProjection_.eye;
	worldTransform_.rotation_ = viewProjection_.target;

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

	Vector3 up(0, 1, 0);

	viewProjection_.up = worldTransform_.rotation_;

	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();
}