#pragma once
#include "EnemyBullet.h"

class BulletFactory;

class StraightBullet : public EnemyBullet
{
public:

	enum class USER {

		None,
		ZakoBox,
		ZakoDome,
		ZakoCylinder
	};


	StraightBullet();
	StraightBullet(const tnl::Vector3& spawn_pos, const tnl::Vector3& move_dir) {}
	StraightBullet(const tnl::Vector3& spawn_pos, const tnl::Vector3& move_dir, const Shared<Player>& player, const float& speed);

	void CheckLifeTimeDistance(const Shared<StraightBullet>& straightBullet);



	void Render(Shared<dxe::Camera> _mainCamera) override;
	void Update(float deltaTime) override;

public:

	Shared<dxe::Mesh> _mesh = nullptr;

};