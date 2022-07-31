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

	InitializeApproach();

	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update();
	}
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

	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::Fire() {

	const float kbulletSpeed = 1.0f;
	Vector3 velocity(0, 0, -kbulletSpeed);

	velocity = VectorMatrix(velocity, worldTransform_);

	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();

	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	bullets_.push_back(std::move(newBullet));
}

void Enemy::InitializeApproach() { 
	shotTimer--;

	if (shotTimer < 0) {

		Fire();
		shotTimer = kFIreInterval;
	}
}