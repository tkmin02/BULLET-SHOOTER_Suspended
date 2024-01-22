#pragma once

#include "../../../DxLibEngine.h"

class StraightBullet;

class BulletFactory
{
public:

	BulletFactory(){}
	explicit BulletFactory(const Shared<dxe::Mesh>& enemy_mesh);

	std::list<Shared<StraightBullet>> CreateStraightBullet(const StraightBullet::USER user);

private:

	std::list<Shared<StraightBullet>> CreateStraightBullet_ZakoBox();

	std::list<Shared<StraightBullet>> CreateStraightBullet_ZakoDome();

	std::list<Shared<StraightBullet>> CreateStraightBullet_ZakoCylinder();


private:

	Shared<dxe::Mesh> _enemyMesh_ref = nullptr;
};