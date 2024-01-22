#include "StraightBullet.h"
#include "BulletFactory.h"



BulletFactory::BulletFactory(const Shared<dxe::Mesh>& enemy_mesh) {

	_enemyMesh_ref = enemy_mesh;
}


std::list<Shared<StraightBullet>> BulletFactory::CreateStraightBullet(const StraightBullet::USER user) {

	switch (user) {

	case StraightBullet::USER::ZakoBox:
		return CreateStraightBullet_ZakoBox();
		break;
	case  StraightBullet::USER::ZakoDome:
		return CreateStraightBullet_ZakoDome();
		break;
	case  StraightBullet::USER::ZakoCylinder:
		return CreateStraightBullet_ZakoCylinder();
		break;
	default:
		break;
	}
}



std::list<Shared<StraightBullet>> BulletFactory::CreateStraightBullet_ZakoBox() {

	std::list<Shared<StraightBullet>> straightBullet;

	int left_round_shot_bulletNum = 4;
	for (int i = 0; i < left_round_shot_bulletNum; i++) {

		Shared<StraightBullet> bullet = std::make_shared<StraightBullet>();

		tnl::Vector3 spawn_pos = _enemyMesh_ref->pos_;

		spawn_pos.x += _enemyMesh_ref->rot_.x;
		spawn_pos.y += _enemyMesh_ref->rot_.y;
		spawn_pos.z -= (i * 10) * (tnl::PI / left_round_shot_bulletNum) +_enemyMesh_ref->rot_.z;

		bullet->_mesh->pos_ = spawn_pos;
		bullet->_isActive = true;

		straightBullet.push_back(bullet);
	}

	return straightBullet;
}


std::list<Shared<StraightBullet>> BulletFactory::CreateStraightBullet_ZakoDome() {

	std::list<Shared<StraightBullet>> straightBullet;

	return straightBullet;

}

std::list<Shared<StraightBullet>> BulletFactory::CreateStraightBullet_ZakoCylinder() {

	std::list<Shared<StraightBullet>> straightBullet;

	return straightBullet;

}
