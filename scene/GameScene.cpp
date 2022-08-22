#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>
#include <random>
#include <fstream>

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

	for (int i = 0; i < 30; i++) {

		std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
		newEnemy->Initialize(model_, textureHandle_);
		enemy_.push_back(std::move(newEnemy));

	}
	for (std::unique_ptr<Enemy>& enemy : enemy_) {
		
		enemy->SetPlayer(player_.get());
		enemy->SetGameScene(this);
	}
	
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	Skydome* newSkydome = new Skydome();
	newSkydome->Initialize(modelSkydome_);
	skydome_.reset(newSkydome);

	RailCamera* newRailCamera = new RailCamera();
	newRailCamera->Initialize(cameraTranslate, cameraRotate);
	railCamera_.reset(newRailCamera);
	player_->SetCameraWorldTransform(railCamera_->GetMatrixWorld());

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	viewProjection_.Initialize();
}

void GameScene::Update() {
	debugCamera_->Update();
	CheckAllColisions();
	//自キャラの更新
	player_->Update();

	for (std::unique_ptr<Enemy>& enemy : enemy_) {
		enemy->Update();
	}
	EnemyBulletUpdate();
	
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

void GameScene::AddEnemyBullet(std::unique_ptr<EnemyBullet>enemyBullet) {

	enemybullets_.push_back(std::move(enemyBullet));

}

void GameScene::EnemyBulletUpdate() {

	for (std::unique_ptr<EnemyBullet>& bullet : enemybullets_) {
		bullet->Update();
	}

	enemybullets_.remove_if([](std::unique_ptr<EnemyBullet>& enemybullets) { return enemybullets->IsDead(); });
}

void GameScene::EnemyBulletDraw() {

	for (std::unique_ptr<EnemyBullet>& bullet : enemybullets_) {
		bullet->Draw(viewProjection_);
	}

}

void GameScene::EnemyUpdate() {

	enemy_.remove_if([](std::unique_ptr<Enemy>& enemy) { return enemy->IsDead(); });
}
void GameScene::CheckAllColisions() {
	Vector3 posA, posB,posC,posD;
	float posResult;
	const float circleA = 20;
	const float circleB = 20;
	const float circleC = 20;
	const float circleD = 20;
	float circleResult;

	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();
	const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = GetBullets();

	posA = player_->GetWorldPosition();

	for (const std::unique_ptr<EnemyBullet>& enemybullet : enemyBullets) {

		posD = enemybullet->GetWorldPosition();

		posResult = (posD.x - posA.x) * (posD.x - posA.x) + 
					(posD.y - posA.y) * (posD.y - posA.y) +
		            (posD.z - posA.z) * (posD.z - posA.z);

		circleResult = (circleA + circleD) * (circleA + circleD);

		if (posResult <= circleResult) {

			player_->OnColision();
			enemybullet->OnColision();
		}
	}

	for (const std::unique_ptr<Enemy>& enemy : enemy_) {
		for (const std::unique_ptr<PlayerBullet>& playerbullet : playerBullets) {

			
 			posB = playerbullet->GetWorldPosition();
 			posC = enemy->GetWorldPosition();

			posResult = (posC.x - posB.x) * (posC.x - posB.x) +
			            (posC.y - posB.y) * (posC.y - posB.y) +
			            (posC.z - posB.z) * (posC.z - posB.z);

			circleResult = (circleB + circleC) * (circleB + circleC);

			if (posResult <= circleResult) {

				enemy->OnColision();

				playerbullet->OnColision();
			}
		}
	}

	for (const std::unique_ptr<EnemyBullet>& enemybullet : enemyBullets) {
		for (const std::unique_ptr<PlayerBullet>& playerbullet : playerBullets) {

			posB = playerbullet->GetWorldPosition();
			posD = enemybullet->GetWorldPosition();

			posResult = (posD.x - posB.x) * (posD.x - posB.x) +
			            (posD.y - posB.y) * (posD.y - posB.y) +
			            (posD.z - posB.z) * (posD.z - posB.z);

			circleResult = (circleB + circleD) * (circleB + circleD);

			if (posResult <= circleResult) {
				enemybullet->OnColision();

				playerbullet->OnColision();
			}
		}
	}
}

void GameScene::LoadEnemyPopData() {

	std::ifstream file;
	file.open("enemyPop.csv");
	assert(file.is_open());

	enemyPopCommands << file.rdbuf();

	file.close();
}

void GameScene::UpdateEnemyPopCommands() {

	std::string line;

	while (getline(enemyPopCommands, line)) {
	
		std::istringstream line_stream(line);

		std::string word;

		getline(line_stream, word, ',');

		if (word.find("//") == 0) {

			continue;
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
	EnemyBulletDraw();
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

void GameScene::EnemyPop(Vector3 vector) {


}