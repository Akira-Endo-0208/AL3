#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "TransferWorldMatrix.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <DirectXMath.h>

using namespace WorldMat;
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

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	uint32_t textureHandle_ = 0;
	Model* model_ = nullptr;
	DebugCamera* debugCamera_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	Vector3 zLine[20] = {
	  {-20.0f, 0.0f, -20.0f},
      {-20.0f, 0.0f, 20.0f },
      {-15.0f, 0.0f, -20.0f},
      {-15.0f, 0.0f, 20.0f },
	  {-10.0f, 0.0f, -20.0f},
      {-10.0f, 0.0f, 20.0f },
      {-5.0f,  0.0f, -20.0f},
      {-5.0f,  0.0f, 20.0f },
	  {0.0f,   0.0f, -20.0f},
      {0.0f,   0.0f, 20.0f },
      {5.0f,   0.0f, -20.0f},
      {5.0f,   0.0f, 20.0f },
	  {10.0f,  0.0f, -20.0f},
      {10.0f,  0.0f, 20.0f },
      {15.0f,  0.0f, -20.0f},
      {15.0f,  0.0f, 20.0f },
	  {20.0f,  0.0f, -20.0f},
      {20.0f,  0.0f, 20.0f }
    };

	Vector3 xLine[20] = {
	  {-20.0f, 0.0f, -20.0f},
      {20.0f,  0.0f, -20.0f},
      {-20.0f, 0.0f, -15.0f},
      {20.0f,  0.0f, -15.0f},
	  {-20.0f, 0.0f, -10.0f},
      {20.0f,  0.0f, -10.0f},
      {-20.0f, 0.0f, -5.0f },
      {20.0f,  0.0f, -5.0f },
	  {-20.0f, 0.0f, 0.0f  },
      {20.0f,  0.0f, 0.0f  },
      {-20.0f, 0.0f, 5.0f  },
      {20.0f,  0.0f, 5.0f  },
	  {-20.0f, 0.0f, 10.0f },
      {20.0f,  0.0f, 10.0f },
      {-20.0f, 0.0f, 15.0f },
      {20.0f,  0.0f, 15.0f },
	  {-20.0f, 0.0f, 20.0f },
      {20.0f,  0.0f, 20.0f }
    };

	int edgeList[18][2] = {
	  {0,  1 },
      {2,  3 },
      {4,  5 },
      {6,  7 },
      {8,  9 },
      {10, 11},
      {12, 13},
      {14, 15},
      {16, 17},
	};
	Vector4 blue;
	Vector4 red;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
