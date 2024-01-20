#include "BulletHell.h"
#include "BulletHellFactory.h"
#include "../../../DxLibEngine.h"
#include <random>

BulletHellFactory::BulletHellFactory() {

	_bulletHellData_map = _csvLoader->LoadBulletHellTypeInfos("BulletHellType.csv");

	InitBulletHellInfo();
}


void BulletHellFactory::InitBulletHellInfo() {

	for (auto it_bltData = _bulletHellData_map.begin(); it_bltData != _bulletHellData_map.end(); it_bltData++) {

		switch ((*it_bltData).first) // id
		{
		case 1:

			_sBltHell_patchouli_info._typeName = (*it_bltData).second._typeName;
			_sBltHell_patchouli_info._maxBulletSpawnCount = (*it_bltData).second._maxBulletSpawnCount;
			_sBltHell_patchouli_info._bulletSpawnRate = (*it_bltData).second._bulletSpawnRate;
			break;
		case 2:

			_sBltHell_cirno_info._typeName = (*it_bltData).second._typeName;
			_sBltHell_cirno_info._maxBulletSpawnCount = (*it_bltData).second._maxBulletSpawnCount;
			_sBltHell_cirno_info._bulletSpawnRate = (*it_bltData).second._bulletSpawnRate;
			break;
		case 3:

			_sBltHell_suwako_info._typeName = (*it_bltData).second._typeName;
			_sBltHell_suwako_info._maxBulletSpawnCount = (*it_bltData).second._maxBulletSpawnCount;
			_sBltHell_suwako_info._bulletSpawnRate = (*it_bltData).second._bulletSpawnRate;
			break;
		}
	}
}


std::list<Shared<EnemyBullet>> BulletHellFactory::CreateBulletHell_SilentSerena() {

	std::list<Shared<EnemyBullet>> enemyBullet;

	std::random_device rd;
	std::mt19937 mt(rd());

	int circle_contiguous_bulletNum = 180;
	for (int i = 0; i < circle_contiguous_bulletNum; i++) {

		std::uniform_real_distribution<float> dist_x(-180.0, 180.0);
		std::uniform_real_distribution<float> dist_y(-50.0, 200.0);
		std::uniform_real_distribution<float> dist_z(-180.0, 180.0);

		Shared<EnemyBullet> bullet = std::make_shared<EnemyBullet>(EnemyBullet::COLOR::EmeraldGreen);

		bullet->_mesh->pos_.x = bullet->_mesh->pos_.x + dist_x(mt);
		bullet->_mesh->pos_.y = bullet->_mesh->pos_.y + dist_y(mt);
		bullet->_mesh->pos_.z = bullet->_mesh->pos_.z + dist_z(mt);

		bullet->_id = i;
		bullet->color = EnemyBullet::COLOR::EmeraldGreen;

		enemyBullet.push_back(bullet);
	}


	int slowly_coming_bulletNum = 50;
	for (int i = 0; i < slowly_coming_bulletNum; i++) {

		std::uniform_real_distribution<float> dist_x(-180.0, 180.0);
		std::uniform_real_distribution<float> dist_y(-50.0, 100.0);
		std::uniform_real_distribution<float> dist_z(-180.0, 180.0);

		Shared<EnemyBullet> bullet = std::make_shared<EnemyBullet>(EnemyBullet::COLOR::Blue);

		bullet->_mesh->pos_.x = bullet->_mesh->pos_.x + dist_x(mt);
		bullet->_mesh->pos_.y = bullet->_mesh->pos_.y + dist_y(mt);
		bullet->_mesh->pos_.z = bullet->_mesh->pos_.z + dist_z(mt);

		bullet->_id = i;
		bullet->color = EnemyBullet::COLOR::Blue;

		enemyBullet.push_back(bullet);
	}

	return enemyBullet;
}



Shared<EnemyBullet> BulletHellFactory::ReuseBulletHellsBullet_SilentSerena(std::map<int, Shared<EnemyBullet>> bltHellsBlt_map, int id) {

	// bulletHellBulletMapì‡Ç…ÉLÅ[Ç™idÇ≈Ç†ÇÈóvëfÇ™å©Ç¬Ç©ÇÁÇ»Ç©Ç¡ÇΩèÍçá
	if (bltHellsBlt_map.find(id) == bltHellsBlt_map.end()) {

		Shared<EnemyBullet> bulletHell = std::make_shared<EnemyBullet>(id);
		bltHellsBlt_map[id] = bulletHell;
	}

	return bltHellsBlt_map[id];
}



Shared<EnemyBullet> BulletHellFactory::GetBulletHellsBullet(std::map<int, Shared<EnemyBullet>> bltHellsBlt_map, int id) {

	// íeÇ™ãÛÇÃÇ∆Ç´ÇÃÇ›ê∂ê¨Ç∑ÇÈ
	if (bltHellsBlt_map.find(id) != bltHellsBlt_map.end()) {
		return bltHellsBlt_map[id];
	}
	return nullptr;
}



std::list<Shared<EnemyBullet>> BulletHellFactory::CreateBulletHell_PerfectFreeze() {
	std::list<Shared<EnemyBullet>> enemyBullet;
	Shared<EnemyBullet> bullet = std::make_shared<EnemyBullet>();
	return enemyBullet;
}


std::list<Shared<EnemyBullet>> BulletHellFactory::CreateBulletHell_KeroChanStandsFirm_AgainstTheStorm() {

	std::list<Shared<EnemyBullet>> enemyBullet;

	Shared<EnemyBullet> bullet = std::make_shared<EnemyBullet>();
	return enemyBullet;

}



std::list<Shared<EnemyBullet>> BulletHellFactory::CreateBulletHell(const BulletHell::TYPE type) {

	switch (type)
	{
	case BulletHell::TYPE::Silent_Serena:
		return CreateBulletHell_SilentSerena();

		break;
	case BulletHell::TYPE::Perfect_Freeze:
		return CreateBulletHell_PerfectFreeze();

		break;
	case BulletHell::TYPE::KeroChan_StandsFirm_AgainstTheStorm:
		return CreateBulletHell_KeroChanStandsFirm_AgainstTheStorm();

		break;
	default:
		break;
	}
}