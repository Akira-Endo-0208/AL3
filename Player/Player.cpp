#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {

	//NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	textureHandle_ = textureHandle;

	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//�v���C���[�̃��[���h�s��ɕK�v�ȗv�f�̐錾
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};

	worldTransform_.Initialize();

}

void Player::Update() {

	//�v���C���[�̍s��v�Z
	worldTransform_.translation_ += move;
	WorldMat::TransferWorldMatrix(
	  worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_,
	  worldTransform_);
	worldTransform_.TransferMatrix();



	//�ړ����E���W
	const float kmoveLimitX = 35;
	const float kmoveLimitY = 20;

	//�͈͂𒴂��Ȃ�����
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

	//�v���C���[�x�N�g��������
	move = {0.0f, 0.0f, 0.0f};

	//�L�����N�^�[�̈ړ�����
	const float kCharacterSpeed = 0.2f;

	//�����������ňړ��x�N�g����ύX
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

	//�����������ňړ��x�N�g����ύX
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