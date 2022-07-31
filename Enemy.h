#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DebugText.h"
#include "TransferWorldMatrix.h"
#include <cassert>
#include "PlayerBullet.h"
#include <memory>
#include <list>

class Enemy {

  public:
	//初期化
	void Initialize(Model* model, uint32_t textureHandle);

	//更新
	void Update();

	//描画
	void Draw(ViewProjection viewProjection);

	void Move();

  private:

	Vector3 move;

	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	enum class Phase {
		Approach,
		Leave,
	};

	Phase phase_ = Phase::Approach;
};
