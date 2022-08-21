#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position,const Vector3& velocity) { 
	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("mario.jpg");

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};

	velocity_ = velocity;

}

void PlayerBullet::Update() {

	TransferWorldMatrix(
	  worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_,
	  worldTransform_);

	worldTransform_.translation_ += velocity_;

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
	worldTransform_.TransferMatrix();
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void PlayerBullet::OnColision() { isDead_ = true; }

Vector3 PlayerBullet::GetWorldPosition() {

	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}