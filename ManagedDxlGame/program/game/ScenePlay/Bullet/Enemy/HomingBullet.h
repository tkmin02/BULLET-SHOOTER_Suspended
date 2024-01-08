#pragma once
#include "EnemyBullet.h"


class HomingBullet : public EnemyBullet
{
public:

	HomingBullet() {}
	HomingBullet(Shared<HomingBullet> straighBullet);
	HomingBullet(const tnl::Vector3& spawn_pos, const tnl::Vector3& move_dir) {}
	HomingBullet(const tnl::Vector3& spawn_pos, const tnl::Vector3& move_dir, const Shared<Player>& player, const float& speed);


	void Render(Shared<dxe::Camera> _mainCamera) override;
	void Update(float deltaTime) override;

	Shared<dxe::Mesh> _mesh = nullptr;
};