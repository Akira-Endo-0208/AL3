#include "TransferWorldMatrix.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"


using namespace MathUtility;



Vector3 VectorMatrix(Vector3 vector, WorldTransform worldTransform) {

	Vector4 matVector = {
		vector.x, vector.y, vector.z,0
	};




	Vector3 result{
	  (matVector.x * worldTransform.matWorld_.m[0][0] + 
	   matVector.y * worldTransform.matWorld_.m[1][0] + 
	   matVector.z * worldTransform.matWorld_.m[2][0] + 
	   matVector.w * worldTransform.matWorld_.m[3][0]),

	  (matVector.x * worldTransform.matWorld_.m[0][1] + 
	   matVector.y * worldTransform.matWorld_.m[1][1] + 
	   matVector.z * worldTransform.matWorld_.m[2][1] + 
	   matVector.w * worldTransform.matWorld_.m[3][1]),

	  (matVector.x * worldTransform.matWorld_.m[0][2] + 
	   matVector.y * worldTransform.matWorld_.m[1][2] + 
	   matVector.z * worldTransform.matWorld_.m[2][2] + 
	   matVector.w * worldTransform.matWorld_.m[3][2]) 
	};

	return result;
}
Matrix4 ScaleMatrix(Vector3 scale, WorldTransform worldTransform) {


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

	return worldTransform.matWorld_;
}

Matrix4 RotationX(Vector3 rotate, WorldTransform worldTransform) {


	Matrix4 matRotX = {

	  1,
	  0,
	  0,
	  0,

	  0,
	  cosf(rotate.x),
	  sinf(rotate.x),
	  0,

	  0,
	  -sinf(rotate.x),
	  cosf(rotate.x),
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

	return worldTransform.matWorld_;
}

Matrix4 RotationY(Vector3 rotate, WorldTransform worldTransform) {


	Matrix4 matRotY = {

	  cosf(rotate.y),
	  0,
	  -sinf(rotate.y),
	  0,

	  0,
	  1,
	  0,
	  0,

	  sinf(rotate.y),
	  0,
	  cosf(rotate.y),
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

	return worldTransform.matWorld_;
}

Matrix4 RotationZ(Vector3 rotate, WorldTransform worldTransform) {

	

	Matrix4 matRotZ = {

	  cosf(rotate.z),
	  sinf(rotate.z),
	  0,
	  0,

	  -sinf(rotate.z),
	  cosf(rotate.z),
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


	return worldTransform.matWorld_;
}


Matrix4 TransferMatrix(Vector3 trans, WorldTransform worldTransform) {

	

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



	return worldTransform.matWorld_;
}

Matrix4 TransferWorldMatrix(
  Vector3 scale, Vector3 rotate, Vector3 trans, WorldTransform& worldTransform) {

	Matrix4 result;

	 Matrix4 matScale;
	 matScale = ScaleMatrix(scale, worldTransform);
	
	Matrix4 matRot, matRotX, matRotY, matRotZ;

	matRotX = RotationX(rotate, worldTransform);
	matRotY = RotationY(rotate, worldTransform);
	matRotZ = RotationZ(rotate, worldTransform);

	matRot = matRotZ * matRotX * matRotY;

	Matrix4 matTrans = TransferMatrix(trans, worldTransform);

	worldTransform.matWorld_ = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	worldTransform.matWorld_ *= matScale * matRot * matTrans;

	return worldTransform.matWorld_;
}

Vector3 ChangeVector(Matrix4 matworld) { 
	
	Vector3 result;

	result = {matworld.m[3][0], matworld.m[3][1], matworld.m[3][2]};

	return result;
}