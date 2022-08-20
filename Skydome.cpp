#include "Skydome.h"

void Skydome::Initialize(Model* model){
	// NULLポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;



	//プレイヤーのワールド行列に必要な要素の宣言
	worldTransform_.scale_ = {30.0f, 30.0f, 30.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};

	worldTransform_.Initialize();
}

void Skydome::Update() {

	TransferWorldMatrix(
	  worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_,
	  worldTransform_);

	worldTransform_.TransferMatrix();
}

void Skydome::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection);
}