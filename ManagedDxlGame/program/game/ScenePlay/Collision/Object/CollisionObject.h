#pragma once
#include "../../../DxLibEngine.h"

class CollisionObject;

using IntersectedCall = std::function<void(CollisionObject* a, CollisionObject* b)>;


class CollisionObject
{
public:

	CollisionObject();

	void SetCollision_MeshAMeshB(Shared<dxe::Mesh> meshA, Shared<dxe::Mesh> meshB, tnl::Vector3 collisionSize, tnl::Vector3 prev_pos);


	float _deltaTime_ref;

	void SetDeltaTimeRef(const float& deltaTime) { _deltaTime_ref = deltaTime; }

	// “–‚½‚è”»’èƒTƒCƒY
	tnl::Vector3 collide_size;

	tnl::Vector3 collide_pos;
	int radius;

};

