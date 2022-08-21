#pragma once
#include "WorldTransform.h"
#include "TransferWorldMatrix.h"
#include "DebugText.h"
#include <cassert>

using namespace MathUtility;

class RailCamera {

  public:
	//������
	void Initialize(Vector3 translate,Vector3 rotate);

	//�X�V
	void Update();

	const ViewProjection& GetViewProjection() { return viewProjection_; }

	const Matrix4& GetMatrixWorld() { return worldTransform_.matWorld_; }

  private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	DebugText* debugText_ = nullptr;

};

