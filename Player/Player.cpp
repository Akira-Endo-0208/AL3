#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {

	//NULLポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//プレイヤーのワールド行列に必要な要素の宣言
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};

	worldTransform_.Initialize();

}

void Player::Update() {

	//プレイヤーの行列計算
	worldTransform_.translation_ += move;
	WorldMat::TransferWorldMatrix(
	  worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_,
	  worldTransform_);
	worldTransform_.TransferMatrix();



	//移動限界座標
	const float kmoveLimitX = 35;
	const float kmoveLimitY = 20;

	//範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kmoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kmoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kmoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kmoveLimitY);

	Rotate();
	Move();
	Attack();

	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

	debugText_->SetPos(50, 150);
	debugText_->Printf(
	  "Root:(%f,%f,%f)", worldTransform_.translation_.x,
	  worldTransform_.translation_.y, worldTransform_.translation_.z);

}

void Player::Move() {

	//プレイヤーベクトル初期化
	move = {0.0f, 0.0f, 0.0f};

	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_LEFT)) {
		move = {-kCharacterSpeed, 0, 0};
	} else if (input_->PushKey(DIK_RIGHT)) {
		move = {kCharacterSpeed, 0, 0};
	} else if (input_->PushKey(DIK_UP)) {
		move = {0, kCharacterSpeed, 0};
	} else if (input_->PushKey(DIK_DOWN)) {
		move = {0, -kCharacterSpeed, 0};
	}

}

void Player::Rotate() {

	
	const float kRotSpeed = 0.005f;

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_U)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_I)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}



}

void Player::Draw(ViewProjection viewProjection) {
	
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Player::Attack() { 
	if (input_->TriggerKey(DIK_SPACE)) {

		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_, worldTransform_.translation_);

		bullets_.push_back(std::move(newBullet));
	}
}