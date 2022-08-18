#pragma once
#include "WorldTransform.h"
#include "TransferWorldMatrix.h"
#include "DebugText.h"
#include <cassert>

class RailCamera {

  public:
	//初期化
	void Initialize(ViewProjection& viewProjection);

	//更新
	void Update();

  private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	DebugText* debugText_ = nullptr;
};
