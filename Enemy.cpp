#include "Enemy.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle) {

	// NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	textureHandle_ = textureHandle;

	

	//�v���C���[�̃��[���h�s��ɕK�v�ȗv�f�̐錾
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

	//�L�����N�^�[�̈ړ�����
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