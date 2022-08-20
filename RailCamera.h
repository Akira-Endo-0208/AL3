#pragma once
#include "WorldTransform.h"
#include "TransferWorldMatrix.h"
#include "DebugText.h"
#include <cassert>

using namespace MathUtility;

class RailCamera {

  public:
	//初期化
	void Initialize(Vector3 translate,Vector3 rotate);

	//更新
	void Update();

	const ViewProjection& GetViewProjection() { return viewProjection_; }

	const Matrix4& GetMatrixWorld() { return worldTransform_.matWorld_; }

  private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	DebugText* debugText_ = nullptr;

};

