#pragma once
#include "TransferWorldMatrix.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"


	Vector3 VectorMatrix(Vector3 vector, WorldTransform worldTransform);

	Matrix4 ScaleMatrix(Vector3 scale, WorldTransform worldTransform);

	Matrix4 RotationX(Vector3 rotate, WorldTransform worldTransform);

	Matrix4 RotationY(Vector3 rotate, WorldTransform worldTransform);

	Matrix4 RotationZ(Vector3 rotate, WorldTransform worldTransform);

	Matrix4 TransferMatrix(Vector3 trans, WorldTransform worldTransform);

	Matrix4 TransferWorldMatrix(
      Vector3 scale, Vector3 rotate, Vector3 trans, WorldTransform& worldTransform);
