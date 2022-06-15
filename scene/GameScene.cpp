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


		//キャラの大元
		worldTransforms_[PartId::kRoot].Initialize();
		worldTransforms_[PartId::kRoot].translation_ = {0.0f, 0.0f, 0.0f};


		 //脊椎
	    worldTransforms_[PartId::kSpine].Initialize();
	    worldTransforms_[PartId::kSpine].parent_ = &worldTransforms_[PartId::kRoot];
	    worldTransforms_[PartId::kSpine].translation_ = {0, 4.5f, 0};


	    //上半身 胸
	    worldTransforms_[PartId::kChest].Initialize();
	    worldTransforms_[PartId::kChest].parent_ = &worldTransforms_[PartId::kSpine];
	    worldTransforms_[PartId::kChest].translation_ = {0, 4.5f, 0};

	    //上半身　頭
	    worldTransforms_[PartId::kHead].Initialize();
	    worldTransforms_[PartId::kHead].parent_ = &worldTransforms_[PartId::kChest];
	    worldTransforms_[PartId::kHead].translation_ = {0, 3.5f, 0};

	    //上半身　左腕
	    worldTransforms_[PartId::kArmL].Initialize();
	    worldTransforms_[PartId::kArmL].parent_ = &worldTransforms_[PartId::kChest];
	    worldTransforms_[PartId::kArmL].translation_ = {-3.0f, 0.0f, 0};

	    //上半身　右腕
	    worldTransforms_[PartId::kArmR].Initialize();
	    worldTransforms_[PartId::kArmR].parent_ = &worldTransforms_[PartId::kChest];
	    worldTransforms_[PartId::kArmR].translation_ = {3.0f, 0.0f, 0};


	    //下半身　尻
	    worldTransforms_[PartId::kHip].Initialize();
	    worldTransforms_[PartId::kHip].parent_ = &worldTransforms_[PartId::kSpine];
	    worldTransforms_[PartId::kHip].translation_ = {0, 1.0f, 0};


	    //下半身　左脚
	    worldTransforms_[PartId::kLegL].Initialize();
	    worldTransforms_[PartId::kLegL].parent_ = &worldTransforms_[PartId::kHip];
	    worldTransforms_[PartId::kLegL].translation_ = {-3.0f, -2.5f, 0};


	    //下半身　右脚
	    worldTransforms_[PartId::kLegR].Initialize();
	    worldTransforms_[PartId::kLegR].parent_ = &worldTransforms_[PartId::kHip];
	    worldTransforms_[PartId::kLegR].translation_ = {3.0f, -2.5f, 0};

		for (int i = 0; i < kNumPartId; i++) {
		 worldTransforms_[i].rotation_ = {1.0f, 1.0f, 1.0f};
		 worldTransforms_[i].scale_ = {1.0f, 1.0f, 1.0f};
	    }
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
	worldTransforms_[PartId::kRoot].translation_ += move;

	for (int i = 0; i < kNumPartId; i++) {

		WorldMat::TransferWorldMatrix(

		worldTransforms_[i].scale_,
		worldTransforms_[i].rotation_,
		worldTransforms_[i].translation_,
		worldTransforms_[i]
		);

		if (i >= kSpine) 
		{
			worldTransforms_[i].matWorld_ *= worldTransforms_[i].parent_->matWorld_;
		}
		worldTransforms_[i].TransferMatrix();
	}

	debugText_->SetPos(50, 150);
	debugText_->Printf(
	  "kRoot(%f,%f,%f)", worldTransforms_[PartId::kRoot].translation_.x,
	  worldTransforms_[PartId::kRoot].translation_.y,
	  worldTransforms_[PartId::kRoot].translation_.z);


	//上半身回転処理
	//上半身の回転の速さ[ラジアン/flame]
	const float kChestRotSpeed = 0.02f;

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_U)) {
		worldTransforms_[PartId::kChest].rotation_.y -= kChestRotSpeed;
	} else if (input_->PushKey(DIK_I)) {
		worldTransforms_[PartId::kChest].rotation_.y += kChestRotSpeed;
	}

	//下半身の回転の速さ[ラジアン/flame]
	const float kHipRotSpeed = 0.02f;

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_J)) {
		worldTransforms_[PartId::kHip].rotation_.y -= kHipRotSpeed;
	} else if (input_->PushKey(DIK_K)) {
		worldTransforms_[PartId::kHip].rotation_.y += kHipRotSpeed;
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
	for (int i = 0; i < kNumPartId; i++)
	{
		if (i <= kSpine) {
			continue;
		}
		model_->Draw(worldTransforms_[i], viewProjection_, textureHandle_);
	}
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
