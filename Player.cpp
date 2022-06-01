#include "Player.h"



void Player::Initialize(Model* model, uint32_t textureHandle) {

	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();

}

void Player::Update() {

	Vector3 move = {0, 0, 0};

	if (input_->PushKey(DIK_UP)) {
		worldTransform_.translation_ = {0.0f, 5.0f, 0.0f};

		Matrix4 matTrans = MathUtility::Matrix4Identity();

		matTrans = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 5.0f, 0.0f, 1.0f
		};

		worldTransform_.matWorld_ = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		worldTransform_.matWorld_ *= matTrans;

		worldTransform_.TransferMatrix();
		debugText_->SetPos(50, 70);
}
}

void Player::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);

}