#pragma once
#include "TransferWorldMatrix.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

namespace WorldMat {

	

	void ScaleMatrix(Vector3 scale,WorldTransform worldTransform);

	void RotationX(Vector3 rotate, WorldTransform worldTransform);

	void RotationY(Vector3 rotate, WorldTransform worldTransform);

	void RotationZ(Vector3 rotate, WorldTransform worldTransform);

	void TransferMatrix(Vector3 trans, WorldTransform worldTransform);

	void TransferWorldMatrix(Vector3 scale,Vector3 rotate,Vector3 trans,WorldTransform& worldTransform);

}