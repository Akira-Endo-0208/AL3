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

	//初期化
	void Initialize(Model* model,uint32_t textureHandle);

	//更新
	void Update();

	//描画
	void Draw(ViewProjection viewProjection);

	void Move();

	void Rotate();

	void Attack();

	private:

	//キャラクターの移動ベクトル
	Vector3 move;

	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
		//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	PlayerBullet* bullet_ = nullptr;
};
