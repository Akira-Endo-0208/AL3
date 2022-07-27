#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DebugText.h"
#include "TransferWorldMatrix.h"
#include <cassert>
#include "PlayerBullet.h"

using namespace WorldMat;
#pragma once
class Player {

	public:

	//������
	void Initialize(Model* model,uint32_t textureHandle);

	//�X�V
	void Update();

	//�`��
	void Draw(ViewProjection viewProjection);

	void Move();

	void Rotate();

	void Attack();

	private:

	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move;

	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
		//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	PlayerBullet* bullet_ = nullptr;
};
