#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "TransferWorldMatrix.h"
#include <DirectXMath.h>
#include "Player.h"
#include "Enemy.h"
#include "Skydome.h"
#include "RailCamera.h"

using namespace DirectX;

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

		enum PartId {
		kRoot,
		kSpine,
		kChest,
		kHead,
		kArmL,
		kArmR,
		kHip,
		kLegL,
		kLegR,

		kNumPartId
	};

	void CheckAllColisions();

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	uint32_t textureHandle_ = 0;
	Model* model_ = nullptr;
	DebugCamera* debugCamera_ = nullptr;

	ViewProjection viewProjection_;
	std::unique_ptr <Player>player_;
	std::unique_ptr <Enemy>enemy_;
	std::unique_ptr <Skydome> skydome_;
	std::unique_ptr<RailCamera> railCamera_;
	Model* modelSkydome_ = nullptr;
	
	bool isDebugCameraActive_ = false;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
