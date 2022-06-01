﻿#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete player_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	player_ = new Player();
	player_->Initialize(model_,textureHandle_);
	////乱数範囲（座標用）
	// std::uniform_real_distribution<float> posDist(-10.0f, 10.0f);
void GameScene::Update() {

}


	//上半身 胸
	worldTransform_[PartId::Chest].translation_ = {0, 4.5f, 0};
	worldTransform_[PartId::Chest].parent_ = &worldTransform_[PartId::Spine];
	worldTransform_[PartId::Chest].Initialize();

	//上半身　頭
	worldTransform_[PartId::Head].translation_ = {0, 3.5f, 0};
	worldTransform_[PartId::Head].parent_ = &worldTransform_[PartId::Chest];
	worldTransform_[PartId::Head].Initialize();

	//上半身　左腕
	worldTransform_[PartId::ArmL].translation_ = {-3.0f, 0.0f, 0};
	worldTransform_[PartId::ArmL].parent_ = &worldTransform_[PartId::Chest];
	worldTransform_[PartId::ArmL].Initialize();

	//上半身　右腕
	worldTransform_[PartId::ArmR].translation_ = {3.0f, 0.0f, 0};
	worldTransform_[PartId::ArmR].parent_ = &worldTransform_[PartId::Chest];
	worldTransform_[PartId::ArmR].Initialize();

	//下半身　尻
	worldTransform_[PartId::Hip].translation_ = {0, 1.0f, 0};
	worldTransform_[PartId::Hip].parent_ = &worldTransform_[PartId::Spine];
	worldTransform_[PartId::Hip].Initialize();

	//下半身　左脚
	worldTransform_[PartId::LegL].parent_ = &worldTransform_[PartId::Hip];
	worldTransform_[PartId::LegL].Initialize();

	//下半身　右脚
	worldTransform_[PartId::LegR].translation_ = {3.0f, -2.5f, 0};
	worldTransform_[PartId::LegR].parent_ = &worldTransform_[PartId::Hip];
	worldTransform_[PartId::LegR].Initialize();

	// viewProjection_.fovAngleY = XMConvertToRadians(10.0f);

	////アスペクト比を設定
	// viewProjection_.aspectRatio = 1.0f;

	////ニアクリップ距離を設定
	// viewProjection_.nearZ = 52.0f;
	////ファークリップ距離を設定
	// viewProjection_.farZ = 53.0f;

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void GameScene::Update() {
	//視点の移動ベクトル
	// XMFLOAT3 move = {0, 0, 0};

	//視点の移動速さ
	// const float kEyeSpeed = 0.2f;

	//押した方向で移動ベクトルを変更
	// if (input_->PushKey(DIK_W))
	//{
	//	move = {0, 0, kEyeSpeed};
	//} else if (input_->PushKey(DIK_S))
	//{
	//	move = {0, 0, -kEyeSpeed};
	//}

	//視点移動（ベクトルの加算）
	// viewProjection_.eye.x += move.x;
	// viewProjection_.eye.y += move.y;
	// viewProjection_.eye.z += move.z;

	//行列の再計算
	// viewProjection_.UpdateMatrix();

	//デバッグ用表示
	/*debugText_->SetPos(50, 50);
	debugText_->Printf(
	  "eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);*/

	//注視点の移動速さ
	// const float kTargetSpeed = 0.2f;

	//押した方向で移動ベクトルを変更
	// if (input_->PushKey(DIK_LEFT)) {
	//	move = {-kTargetSpeed, 0, 0};
	//} else if (input_->PushKey(DIK_RIGHT)) {
	//	move = {kTargetSpeed, 0, 0};
	//}

	//注視点移動（ベクトルの加算）
	// viewProjection_.target.x += move.x;
	// viewProjection_.target.y += move.y;
	// viewProjection_.target.z += move.z;

	//行列の再計算
	// viewProjection_.UpdateMatrix();

	//デバッグ用表示
	/*debugText_->SetPos(50, 70);
	debugText_->Printf(
	  "target:(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y,
	  viewProjection_.target.z);*/

	// const float kUpRotSpeed = 0.05f;

	//押した方向で移動ベクトルを変更
	// if (input_->PushKey(DIK_SPACE)) {
	//	viewAngle += kUpRotSpeed;

	//	viewAngle = fmodf(viewAngle, XM_2PI);
	//}

	//注視点移動（ベクトルの加算）
	// viewProjection_.up = {cosf(viewAngle), sinf(viewAngle),0.0f};

	//行列の再計算
	// viewProjection_.UpdateMatrix();

	//デバッグ用表示
	/*debugText_->SetPos(50, 90);
	debugText_->Printf(
	  "up:(%f,%f,%f)", viewProjection_.up.x, viewProjection_.up.y,
	  viewProjection_.up.z);*/

	// if (input_->PushKey(DIK_W))
	//{
	// Wキーで視野角が広がる
	//	viewProjection_.fovAngleY += 0.01f;
	//	viewProjection_.fovAngleY = min(viewProjection_.fovAngleY, XM_PI);
	// Sキーで視野角が狭まる
	// } else if (input_->PushKey(DIK_S))
	//{
	//	viewProjection_.fovAngleY -= 0.01f;
	//	viewProjection_.fovAngleY = max(viewProjection_.fovAngleY, 0.01f);
	// }

	//行列の再計算
	// viewProjection_.UpdateMatrix();

	//デバッグ用表示
	// debugText_->SetPos(50, 110);
	// debugText_->Printf("fovAngleY(Degree):%f", XMConvertToDegrees(viewProjection_.fovAngleY));

	//クリップ距離変更処理
	//上下キーでニアクリップ距離を増減
	// if (input_->PushKey(DIK_UP))
	//{
	//	viewProjection_.nearZ += 0.1f;
	//} else if (input_->PushKey(DIK_DOWN))
	//{
	//	viewProjection_.nearZ -= 0.1f;
	//}

	//行列の再計算
	// viewProjection_.UpdateMatrix();

	//デバッグ用表示
	// debugText_->SetPos(50, 130);
	// debugText_->Printf("nearZ:%f", viewProjection_.nearZ);

	//キャラクターの移動ベクトル
	XMFLOAT3 move = {0, 0, 0};

	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_LEFT)) {
		move = {-kCharacterSpeed, 0, 0};
	} else if (input_->PushKey(DIK_RIGHT)) {
		move = {kCharacterSpeed, 0, 0};
	}

	//注視点移動(ベクトルの加算)
	worldTransform_[PartId::Root].translation_.x += move.x;
	worldTransform_[PartId::Root].translation_.y += move.y;
	worldTransform_[PartId::Root].translation_.z += move.z;

	debugText_->SetPos(50, 150);
	debugText_->Printf(
	  "Root:(%f,%f,%f)", worldTransform_[PartId::Root].translation_.x,
	  worldTransform_[PartId::Root].translation_.y, worldTransform_[PartId::Root].translation_.z);

	worldTransform_[PartId::Root].UpdateMatrix();
	worldTransform_[PartId::Spine].UpdateMatrix();
	worldTransform_[PartId::Chest].UpdateMatrix();
	worldTransform_[PartId::Head].UpdateMatrix();
	worldTransform_[PartId::ArmL].UpdateMatrix();
	worldTransform_[PartId::ArmR].UpdateMatrix();
	worldTransform_[PartId::Hip].UpdateMatrix();
	worldTransform_[PartId::LegL].UpdateMatrix();
	worldTransform_[PartId::LegR].UpdateMatrix();

	//上半身回転処理
	//上半身の回転の速さ[ラジアン/flame]
	const float kChestRotSpeed = 0.05f;

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_U)) {
		worldTransform_[PartId::Chest].rotation_.y -= kChestRotSpeed;
	} else if (input_->PushKey(DIK_I)) {
		worldTransform_[PartId::Chest].rotation_.y += kChestRotSpeed;
	}

	//下半身の回転の速さ[ラジアン/flame]
	const float kHipRotSpeed = 0.05f;

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_J)) {
		worldTransform_[PartId::Hip].rotation_.y -= kHipRotSpeed;
	} else if (input_->PushKey(DIK_K)) {
		worldTransform_[PartId::Hip].rotation_.y += kHipRotSpeed;
	}
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

	// model_->Draw(worldTransform_[PartId::Root], viewProjection_, textureHandle_);
	// model_->Draw(worldTransform_[PartId::Spine], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::Chest], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::Head], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::ArmL], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::ArmR], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::Hip], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::LegL], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::LegR], viewProjection_, textureHandle_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	player_->Draw();
	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
