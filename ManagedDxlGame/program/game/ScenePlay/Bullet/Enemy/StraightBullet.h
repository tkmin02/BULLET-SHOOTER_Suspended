#pragma once
#include "EnemyBullet.h"



class StraightBullet : public EnemyBullet
{
public:

	StraightBullet(){}
	StraightBullet(Shared<StraightBullet> straighBullet);
	StraightBullet(const tnl::Vector3& spawn_pos, const tnl::Vector3& move_dir) {}
	StraightBullet(const tnl::Vector3& spawn_pos, const tnl::Vector3& move_dir, const Shared<Player>& player, const float& speed);


	void Render(Shared<dxe::Camera> _mainCamera) override;
	void Update(float deltaTime) override;


	Shared<dxe::Mesh> _mesh = nullptr;

};