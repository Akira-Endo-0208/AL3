#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position) { 
	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("mario.jpg");

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {1.0f, 1.0f, 1.0f};
}

void PlayerBullet::Update() {

	WorldMat::TransferWorldMatrix(
	  worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_,
	  worldTransform_);

	worldTransform_.TransferMatrix();
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}