#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DebugText.h"
#include "TransferWorldMatrix.h"
#include <cassert>
#include "EnemyBullet.h"
#include <memory>
#include <list>


class Player;

class Enemy {

  public:
	//������
	void Initialize(Model* model, uint32_t textureHandle);

	//�X�V
	void Update();

	//�`��
	void Draw(ViewProjection viewProjection);

	void Move();

	void Fire();

	void InitializeApproach();

	void SetPlayer(Player* player) { player_ = player; }

	Vector3 GetWorldPosition();

  private:

	Vector3 move;

	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	enum class Phase {
		Approach,
		Leave,
	};

	Phase phase_ = Phase::Approach;

	static const int kFIreInterval = 60;

	int32_t shotTimer = 60;

	Player* player_ = nullptr;
};
