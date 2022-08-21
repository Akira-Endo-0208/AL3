#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>
#include <random>


GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
	delete modelSkydome_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	textureHandle_ = TextureManager::Load("mario.jpg");
	
	model_ = Model::Create();
	debugCamera_ = new DebugCamera(1280, 720);
	//自キャラの生成
	Player* newPlayer = new Player();
	newPlayer->Initialize(model_, textureHandle_);
	//自キャラの初期化
	player_.reset(newPlayer);

	std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
	newEnemy->Initialize(model_, textureHandle_);
	enemy_.push_back(std::move(newEnemy));

	

	for (std::unique_ptr<Enemy>& enemy : enemy_) {
		enemy.get()->SetPlayer(player_.get());
	}

	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	Skydome* newSkydome = new Skydome();
	newSkydome->Initialize(modelSkydome_);
	skydome_.reset(newSkydome);


	RailCamera* newRailCamera = new RailCamera();
	newRailCamera->Initialize(cameraTranslate,cameraRotate);	
	railCamera_.reset(newRailCamera);
	player_->SetCameraWorldTransform(railCamera_->GetMatrixWorld());


	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);


	viewProjection_.Initialize();


}

void GameScene::Update() { 
	debugCamera_->Update();

	//自キャラの更新
	player_->Update();
	for (std::unique_ptr<Enemy>& enemy : enemy_) {
		enemy->Update();
	}
	
	skydome_->Update();
	railCamera_->Update();

	player_->SetCameraWorldTransform(railCamera_->GetMatrixWorld());

	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_K)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}

	#endif

	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.UpdateMatrix();
		viewProjection_.TransferMatrix();
	}


}



void GameScene::AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet) {
	enemybullets_.push_back(std::move(enemyBullet));
}

void GameScene::EnemyBulletUpdate() {


	for (std::unique_ptr<EnemyBullet>& bullet : enemybullets_) {
		bullet->Update();
	}
}

void GameScene::EnemyBulletDraw() {
	for (std::unique_ptr<EnemyBullet>& bullet : enemybullets_) {
		bullet->Draw(viewProjection_);
	}
}

void GameScene::CheckAllColisions() { 
	Vector3 posA, posB;
	float posResult;
	const float circleA = 1;
	const float circleB = 1;
	float circleResult;

	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();
	const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = GetBullets();

	posA = player_->GetWorldPosition();

	for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets) {
	
		posB = bullet->GetWorldPosition();
	

		posResult =
		  (posB.x - posA.x) * (posB.x - posA.x)
		+ (posB.y - posA.y) * (posB.y - posA.y) 
		+ (posB.z - posA.z) * (posB.z - posA.z);

		circleResult = (circleA + circleB) * (circleA + circleB);

		if (posResult <= circleResult) {
			player_->OnColision();

			bullet->OnColision();
		}
	}

	posA = enemy_.begin()->get()->GetWorldPosition();

	for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) {

		posB = bullet->GetWorldPosition();

		posResult = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
		            (posB.z - posA.z) * (posB.z - posA.z);

		circleResult = (circleA + circleB) * (circleA + circleB);

		if (posResult <= circleResult) {
			enemy_.begin()->get()->OnColision();

			bullet->OnColision();
		}
	}

	for (const std::unique_ptr<EnemyBullet>& enemybullet : enemyBullets) {
		for (const std::unique_ptr<PlayerBullet>& playerbullet : playerBullets) {
			posA = playerbullet->GetWorldPosition();
			posB = enemybullet->GetWorldPosition();

			posResult = (posB.x - posA.x) * (posB.x - posA.x) +
			            (posB.y - posA.y) * (posB.y - posA.y) +
			            (posB.z - posA.z) * (posB.z - posA.z);

			circleResult = (circleA + circleB) * (circleA + circleB);

			if (posResult <= circleResult) {
				enemybullet->OnColision();

				playerbullet->OnColision();
			}
		}
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

	//自キャラの削除
	player_->Draw(railCamera_->GetViewProjection());
	for (std::unique_ptr<Enemy>& enemy : enemy_) {
		enemy->Draw(railCamera_->GetViewProjection());
	}

	skydome_->Draw(railCamera_->GetViewProjection());

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
