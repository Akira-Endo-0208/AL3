#pragma once
#include "WorldTransform.h"
#include "TransferWorldMatrix.h"
#include "DebugText.h"
#include <cassert>

class RailCamera {

  public:
	//������
	void Initialize(ViewProjection& viewProjection);

	//�X�V
	void Update();

  private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	DebugText* debugText_ = nullptr;
};
