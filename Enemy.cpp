#include "Enemy.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle) {

	// NULLポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;

	

	//プレイヤーのワールド行列に必要な要素の宣言
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.translation_ = {0.0f, 5.0f, 30.0f};

	worldTransform_.Initialize();
}


void Enemy::Update() {


	TransferWorldMatrix(
	  worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_,
	  worldTransform_);

	

	worldTransform_.TransferMatrix();

	
	Move();

}

void Enemy::Move() {

	move = {0.0f, 0.0f, 0.0f};

	//キャラクターの移動速さ
	const float approachSpeed = 0.2f;
	const float leaveSpeed = 0.3f;

	switch (phase_) {
	case Enemy::Phase::Approach:
	default:
		move = {0.0f, 0.0f, -approachSpeed};
		worldTransform_.translation_ += move;

		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Enemy::Phase::Leave;
		}
		break;
	case Enemy::Phase::Leave:
		move = {-leaveSpeed, leaveSpeed,0.0f};
		worldTransform_.translation_ += move;
		break;
	}
	
}

void Enemy::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}