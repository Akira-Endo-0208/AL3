#pragma once
#include "WorldTransform.h"
#include "TransferWorldMatrix.h"
#include <cassert>
class RailCamera {

  public:
	//������
	void Initialize(ViewProjection& viewProjection_);

	//�X�V
	void Update();

  private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
};
