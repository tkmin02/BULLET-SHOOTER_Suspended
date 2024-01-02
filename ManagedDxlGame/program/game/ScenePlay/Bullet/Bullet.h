#pragma once
#include "../../DxLibEngine.h"
#include "../Collision/Collision.h"


class Bullet : public CollisionObject
{
public:

	Bullet(){}
	Bullet(const tnl::Vector3& spawn_pos, const tnl::Vector3& direction)  {}


	virtual void Update(float delta_time){}
	virtual void Render(Shared<dxe::Camera> _mainCamera){}
};