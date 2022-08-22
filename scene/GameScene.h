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
#include <sstream>

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

	void EnemyUpdate();

	void EnemyDraw(const ViewProjection& viewProjection);

	void AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet);

	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return enemybullets_; }

	void EnemyBulletUpdate();

	void EnemyBulletDraw();

	void LoadEnemyPopData();

	void UpdateEnemyPopCommands();

	void EnemyPop(Vector3 vector);
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
	std::unique_ptr <Skydome> skydome_;
	std::unique_ptr<RailCamera> railCamera_;
	Model* modelSkydome_ = nullptr;
	
	Vector3 cameraTranslate = {0, 0, -100};
	Vector3 cameraRotate = {0, 0, 0};
	bool isDebugCameraActive_ = false;
	std::list<std::unique_ptr<Enemy>> enemy_;

	std::list<std::unique_ptr<EnemyBullet>> enemybullets_;

	std::stringstream enemyPopCommands;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
