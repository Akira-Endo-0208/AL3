#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>
#include <random>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	textureHandle_ = TextureManager::Load("mario.jpg");
	model_ = Model::Create();
	debugCamera_ = new DebugCamera(1280, 720);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);


		worldTransforms_[0].Initialize();

		worldTransforms_[1].Initialize();
	    worldTransforms_[1].translation_ = {0, 4.5f, 0};
	    worldTransforms_[1].parent_ = &worldTransforms_[0];


		worldTransforms_[0].scale_ = {1.0f, 1.0f, 1.0f};
	    worldTransforms_[0].rotation_ = {1.0f, 1.0f, 1.0f};
	    worldTransforms_[0].translation_ = {0.0f, 0.0f, 0.0f};

		worldTransforms_[1].scale_ = {1.0f, 1.0f, 1.0f};
	    worldTransforms_[1].rotation_ = {1.0f, 1.0f, 1.0f};

	viewProjection_.Initialize();
}

void GameScene::Update() {

	debugCamera_->Update();

		//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_LEFT)) {
		move = {-kCharacterSpeed, 0, 0};
	} else if (input_->PushKey(DIK_RIGHT)) {
		move = {kCharacterSpeed, 0, 0};
	}

	//注視点移動(ベクトルの加算)
	worldTransforms_[0].translation_ += move;

	WorldMat::TransferWorldMatrix(
	worldTransforms_[0].scale_,
	worldTransforms_[0].rotation_,
	worldTransforms_[0].translation_,
	worldTransforms_[0]
	);

	worldTransforms_[0].TransferMatrix();

	debugText_->SetPos(50, 150);
	debugText_->Printf(
	  "PosX(%f,%f,%f)", worldTransforms_[0].translation_.x, worldTransforms_[0].translation_.y,
	  worldTransforms_[0].translation_.z);

		WorldMat::TransferWorldMatrix(
	worldTransforms_[1].scale_,
	worldTransforms_[1].rotation_,
	worldTransforms_[1].translation_,
	worldTransforms_[1]
		);

		worldTransforms_[1].matWorld_ *= worldTransforms_[0].matWorld_;

		worldTransforms_[1].TransferMatrix();

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	model_->Draw(worldTransforms_[0], viewProjection_, textureHandle_);
	model_->Draw(worldTransforms_[1], viewProjection_, textureHandle_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();

#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
