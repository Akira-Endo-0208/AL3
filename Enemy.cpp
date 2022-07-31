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


	//�L�����N�^�[�̈ړ�����
	const float kCharacterSpeed = 0.2f;

	worldTransform_.translation_.z -= kCharacterSpeed;
	
}

void Enemy::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}