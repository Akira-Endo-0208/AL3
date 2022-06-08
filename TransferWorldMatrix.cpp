#include "TransferWorldMatrix.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

using namespace MathUtility;

namespace WorldMat {

void ScaleMatrix(Vector3 scale, WorldTransform worldTransform) {

	Matrix4 matScale = {

	  scale.x,		 0,		  0, 0,
			0, scale.y,		  0, 0,
			0,		 0, scale.z, 0,
			0,		 0,		  0, 1};

	worldTransform.matWorld_ = {
		1, 0, 0, 0,
		0, 1, 0, 0, 
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	worldTransform.matWorld_ *= matScale;

	worldTransform.TransferMatrix();
}

void RotationX(Vector3 rotate, WorldTransform worldTransform) {

	Matrix4 matRotX = {

	  1,
	  0,
	  0,
	  0,

	  0,
	  cosf(PI / rotate.x),
	  sinf(PI / rotate.x),
	  0,

	  0,
	  -sinf(PI / rotate.x),
	  cosf(PI / rotate.x),
	  0,

	  0,
	  0,
	  0,
	  1

	};

	worldTransform.matWorld_ = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	worldTransform.matWorld_ *= matRotX;

	worldTransform.TransferMatrix();
}

void RotationY(Vector3 rotate, WorldTransform worldTransform) {

	Matrix4 matRotY = {

	  cosf(PI / rotate.y),
	  0,
	  -sinf(PI / rotate.y),
	  0,

	  0,
	  1,
	  0,
	  0,

	  sinf(PI / rotate.y),
	  0,
	  cosf(PI / rotate.y),
	  0,

	  0,
	  0,
	  0,
	  1

	};
	worldTransform.matWorld_ = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	worldTransform.matWorld_ *= matRotY;

	worldTransform.TransferMatrix();
}

void RotationZ(Vector3 rotate, WorldTransform worldTransform) {
	Matrix4 matRotZ = {

	  cosf(PI / rotate.z),
	  sinf(PI / rotate.z),
	  0,
	  0,

	  -sinf(PI / rotate.z),
	  cosf(PI / rotate.z),
	  0,
	  0,

	  0,
	  0,
	  1,
	  0,

	  0,
	  0,
	  0,
	  1};

	worldTransform.matWorld_ = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	worldTransform.matWorld_ *= matRotZ;

	worldTransform.TransferMatrix();
}

void TransferMatrix(Vector3 trans, WorldTransform worldTransform) {

	Matrix4 matTrans = MathUtility::Matrix4Identity();

	matTrans = {1,       0,       0,       0,

	            0,       1,       0,       0,

	            0,       0,       1,       0,

	            trans.x, trans.y, trans.z, 1};

	worldTransform.matWorld_ = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	worldTransform.matWorld_ *= matTrans;

	worldTransform.TransferMatrix();
}

void TransferWorldMatrix(
  Vector3 scale, Vector3 rotate, Vector3 trans, WorldTransform worldTransform) {

	Matrix4 matScale = {scale.x, 0,       0,       0,

	                    0,       scale.y, 0,       0,

	                    0,       0,       scale.z, 0,

	                    0,       0,       0,       1};

	Matrix4 matRot, matRotX, matRotY, matRotZ;

	matRotZ = {

	  cosf(PI / rotate.z),
	  sinf(PI / rotate.z),
	  0,
	  0,

	  -sinf(PI / rotate.z),
	  cosf(PI / rotate.z),
	  0,
	  0,

	  0,
	  0,
	  1,
	  0,

	  0,
	  0,
	  0,
	  1};

	matRotX = {

	  1,
	  0,
	  0,
	  0,

	  0,
	  cosf(PI / rotate.x),
	  sinf(PI / rotate.x),
	  0,

	  0,
	  -sinf(PI / rotate.x),
	  cosf(PI / rotate.x),
	  0,

	  0,
	  0,
	  0,
	  1

	};

	matRotY = {

	  cosf(PI / rotate.y),
	  0,
	  -sinf(PI / rotate.y),
	  0,

	  0,
	  1,
	  0,
	  0,

	  sinf(PI / rotate.y),
	  0,
	  cosf(PI / rotate.y),
	  0,

	  0,
	  0,
	  0,
	  1

	};

	matRot = matRotZ * matRotX * matRotY;

	Matrix4 matTrans = MathUtility::Matrix4Identity();

	matTrans = {1,       0,       0,       0,

	            0,       1,       0,       0,

	            0,       0,       1,       0,

	            trans.x, trans.y, trans.z, 1};

	worldTransform.matWorld_ = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	worldTransform.matWorld_ *= matScale * matRot * matTrans;

	worldTransform.TransferMatrix();
}

} // namespace WorldMat