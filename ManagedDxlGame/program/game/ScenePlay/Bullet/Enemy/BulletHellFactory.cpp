#include "BulletHell.h"
#include "BulletHellFactory.h"
#include "../../../DxLibEngine.h"

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


Shared<BulletHell> BulletHellFactory::CreateBulletHell_SilentSerena(const Shared<dxe::Mesh>& bossMesh_ref) {

	Shared<BulletHell> bulletHell = std::make_shared<BulletHell>();

	int bulletNum = 180;

	for (int i = 0; i < bulletNum; i++) {

		float theta = i * (2.f * tnl::PI / bulletNum);
		float pi = tnl::PI / 4;


		tnl::Vector3 bulletPos;
		bulletPos.x = bossMesh_ref->pos_.x + cos(theta) * sin(pi);
		bulletPos.y = bossMesh_ref->pos_.y + sin(theta) * sin(pi);
		bulletPos.z = bossMesh_ref->pos_.z + cos(pi);

		Shared<EnemyBullet> bullet = std::make_shared<EnemyBullet>(EnemyBullet::COLOR::EmeraldGreen);

		bullet->SetPosition(bulletPos);
		bulletHell->AddBullet(bullet);
	}


	return bulletHell;
}


Shared<BulletHell> BulletHellFactory::CreateBulletHell_PerfectFreeze(const Shared<dxe::Mesh>& bossMesh_ref) {
	Shared<BulletHell> bulletHell = std::make_shared<BulletHell>();

	Shared<EnemyBullet> bullet = std::make_shared<EnemyBullet>();
	return bulletHell;

}


Shared<BulletHell> BulletHellFactory::CreateBulletHell_KeroChanStandsFirm_AgainstTheStorm(const Shared<dxe::Mesh>& bossMesh_ref) {
	Shared<BulletHell> bulletHell = std::make_shared<BulletHell>();

	Shared<EnemyBullet> bullet = std::make_shared<EnemyBullet>();
	return bulletHell;

}


//Shared<BulletHell> BulletHellFactory::ReuseBulletHell_SilentSerena(int id) {
//
//	// bulletHellMapì‡Ç…ÉLÅ[Ç™idÇ≈Ç†ÇÈóvëfÇ™å©Ç¬Ç©ÇÁÇ»Ç©Ç¡ÇΩèÍçá
//	if (bulletHellMap.find(id) == bulletHellMap.end()) {
//
//		Shared<BulletHell> bulletHell = std::make_shared<BulletHell>(id);
//		bulletHellMap[id] = bulletHell;
//	}
//
//	return bulletHellMap[id];
//}



Shared<BulletHell> BulletHellFactory::CreateBulletHell(const BulletHell::TYPE type, const Shared<dxe::Mesh>& bossMesh_ref) {

	switch (type)
	{
	case BulletHell::TYPE::Silent_Serena:
		return CreateBulletHell_SilentSerena(bossMesh_ref);

		break;
	case BulletHell::TYPE::Perfect_Freeze:
		return CreateBulletHell_PerfectFreeze(bossMesh_ref);

		break;
	case BulletHell::TYPE::KeroChan_StandsFirm_AgainstTheStorm:
		return CreateBulletHell_KeroChanStandsFirm_AgainstTheStorm(bossMesh_ref);

		break;
	default:
		break;
	}
}



//Shared<BulletHell> BulletHellFactory::GetBulletHell(int id) {
//
//	// íeÇ™ãÛÇÃÇ∆Ç´ÇÃÇ›ê∂ê¨Ç∑ÇÈ
//	//if (bulletHellMap.find(id) != bulletHellMap.end()) {
//	//	return bulletHellMap[id];
//	//}
//	//return nullptr;
//}