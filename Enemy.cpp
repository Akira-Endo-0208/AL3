#include "Enemy.h"
#include "Player.h"
void Enemy::Initialize(Model* model, uint32_t textureHandle) {

	// NULLポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;

	

	//プレイヤーのワールド行列に必要な要素の宣言
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 100.0f};

	worldTransform_.Initialize();
}


void Enemy::Update() {


	TransferWorldMatrix(
	  worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_,
	  worldTransform_);

	

	worldTransform_.TransferMatrix();

	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) { return bullet->IsDead(); });

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

	assert(player_);

	const float kbulletSpeed = 10.0f;

	player_->GetWorldPosition();
	GetWorldPosition();
	
	
	Vector3 velocity = {
	  player_->GetWorldPosition().x - GetWorldPosition().x,
	  player_->GetWorldPosition().y - GetWorldPosition().y,
	  player_->GetWorldPosition().z - GetWorldPosition().z
	};

	float length =
	  sqrt(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z);

	velocity = { velocity.x / length, velocity.y / length, velocity.z / length};
	

	velocity.x * kbulletSpeed;
	velocity.y * kbulletSpeed;
	velocity.z * kbulletSpeed;

	

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


Vector3 Enemy::GetWorldPosition() {

	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::OnColision() {}