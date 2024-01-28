#include "BulletHell.h"
#include "BulletHellFactory.h"
#include "../../../Manager/Enemy/EnemyManager.h"
#include "../../../DxLibEngine.h"
#include <random>

BulletHellFactory::BulletHellFactory(const Shared<EnemyManager>& enemyManager) : _enemyManager(enemyManager) {


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


std::list<Shared<EnemyBullet>> BulletHellFactory::CreateBulletHell_Normal_Patchouli() {

	std::list<Shared<EnemyBullet>> enemyBullet;

	// âÒì]ópÇÃíeê∂ê¨ (ç∂âÒì]Ç∆âEâÒì]ÇÃÇQéÌóﬁÇ™Ç†ÇÈÇ™ÅAÇ±Ç±Ç≈ÇÕëSÇƒÇìØéûÇ…ê∂ê¨Ç∑ÇÈÅj
	int round_shot_bulletNum = 8;
	for (int i = 0; i < round_shot_bulletNum; i++) {

		// ãÖëÃ--------------------------------------------------------------------------------------------------------------------------
		Shared<EnemyBullet> round_bullet = std::make_shared<EnemyBullet>(EnemyBullet::SHAPE::Sphere, EnemyBullet::COLOR::Blue, 30.0f);

		round_bullet->_angle = (2.0f * tnl::PI / round_shot_bulletNum) * i;
		round_bullet->_radius = 90.0f;

		round_bullet->_mesh->pos_.x = _enemyManager->GetEnemyBossPosition().x + round_bullet->_radius * cos(round_bullet->_angle);
		round_bullet->_mesh->pos_.y = _enemyManager->GetEnemyBossPosition().y;
		round_bullet->_mesh->pos_.z = _enemyManager->GetEnemyBossPosition().z + round_bullet->_radius * sin(round_bullet->_angle);

		round_bullet->_id = i;
		round_bullet->_allBulletCountByType = round_shot_bulletNum;
		round_bullet->_speed = 150.0f;
		round_bullet->color = EnemyBullet::COLOR::Blue;
		round_bullet->_isActive = true;
		round_bullet->_movementsType = "Sphere.Round";

		enemyBullet.push_back(round_bullet);

		// ãÖëÃÇ∆àÍèèÇ…ìÆÇ≠åıê¸------------------------------------------------------------------------------------------------------------
		Shared<EnemyBullet> round_bullet_beam = std::make_shared<EnemyBullet>(EnemyBullet::SHAPE::Cylinder, EnemyBullet::COLOR::White, 500.f);
		round_bullet_beam->_angle = (2.0f * tnl::PI / round_shot_bulletNum) * i;
		round_bullet_beam->_radius = 90.0f;
		
		round_bullet_beam->_mesh->pos_.x = round_bullet->_mesh->pos_.x + round_bullet_beam->_radius * cos(round_bullet_beam->_angle);
		round_bullet_beam->_mesh->pos_.y = round_bullet->_mesh->pos_.y;
		round_bullet_beam->_mesh->pos_.z = (round_bullet->_mesh->pos_.z + 100) + round_bullet_beam->_radius * sin(round_bullet_beam->_angle);
		
		float pitch = tnl::PI / 2.0f;

		float angle = atan2(round_bullet->_mesh->pos_.z - _enemyManager->GetEnemyBossPosition().z, round_bullet->_mesh->pos_.x - _enemyManager->GetEnemyBossPosition().x);
		float yaw = angle;

		float roll = 0.f;

		tnl::Quaternion rotation = tnl::Quaternion::RotationRollPitchYawFromVector({ pitch, yaw, roll });

		round_bullet_beam->_mesh->rot_ = rotation;

		round_bullet_beam->_id = i;
		round_bullet_beam->_allBulletCountByType = round_shot_bulletNum;
		round_bullet_beam->_speed = 150.0f;
		round_bullet_beam->color = EnemyBullet::COLOR::White;
		round_bullet_beam->_isActive = true;
		round_bullet_beam->_movementsType = "Cylinder.Round";


		enemyBullet.push_back(round_bullet_beam);		
	}


	// ëSï˚å¸òAéÀíe--------------------------------------------------------------------------------------------------------------------------
	int every_direction_shot_bulletNum = 96;
	for (int i = 0; i < every_direction_shot_bulletNum; i++) {

		Shared<EnemyBullet> every_direction_bullet = std::make_shared<EnemyBullet>(EnemyBullet::SHAPE::Sphere, EnemyBullet::COLOR::EmeraldGreen, 12.0f);

		every_direction_bullet->_radius = 65.0f;
		every_direction_bullet->_angle = (2.0f * tnl::PI / every_direction_shot_bulletNum) * i;

		every_direction_bullet->_mesh->pos_.x = every_direction_bullet->_radius * cos(every_direction_bullet->_angle);
		every_direction_bullet->_mesh->pos_.y = every_direction_bullet->_mesh->pos_.y;
		every_direction_bullet->_mesh->pos_.z = every_direction_bullet->_radius * sin(every_direction_bullet->_angle);
		
		every_direction_bullet->_id = i;
		every_direction_bullet->_allBulletCountByType = every_direction_shot_bulletNum;
		every_direction_bullet->color = EnemyBullet::COLOR::EmeraldGreen;
		every_direction_bullet->_isActive = true;
		every_direction_bullet->_movementsType = "Sphere.Straight";


		enemyBullet.push_back(every_direction_bullet);
	}


	return enemyBullet;
}


std::list<Shared<EnemyBullet>> BulletHellFactory::CreateBulletHell_MetalFatigue_Patchouli() {

	std::list<Shared<EnemyBullet>> enemyBullet;

	int every_direction_shot_bulletNum = 8;
	for (int i = 0; i < every_direction_shot_bulletNum; i++) {

		Shared<EnemyBullet> every_direction_bullet = std::make_shared<EnemyBullet>(EnemyBullet::SHAPE::Sphere, EnemyBullet::COLOR::Yellow, 15.0f);

		every_direction_bullet->_radius = 25.0f;
		every_direction_bullet->_angle = (2.0f * tnl::PI / every_direction_shot_bulletNum) * i;

		every_direction_bullet->_mesh->pos_.x = _enemyManager->GetEnemyBossPosition().x;
		every_direction_bullet->_mesh->pos_.y = _enemyManager->GetEnemyBossPosition().y;
		every_direction_bullet->_mesh->pos_.z = _enemyManager->GetEnemyBossPosition().z;

		every_direction_bullet->_id = i;
		every_direction_bullet->_allBulletCountByType = every_direction_shot_bulletNum;
		every_direction_bullet->color = EnemyBullet::COLOR::Yellow;
		every_direction_bullet->_isActive = true;
		every_direction_bullet->_movementsType = "Sphere.Round.Origin";

		enemyBullet.push_back(every_direction_bullet);
	}


	int split_one_into_eight_count = 64;
	Shared<EnemyBullet> split_one_into_eight_bullet_wave1;
	Shared<EnemyBullet> split_one_into_eight_bullet_wave2;
	Shared<EnemyBullet> split_one_into_eight_bullet_wave3;

	InitSplitOneIntoEightBullet(split_one_into_eight_count, split_one_into_eight_bullet_wave1, enemyBullet, "Sphere.Round.Wave1");
	InitSplitOneIntoEightBullet(split_one_into_eight_count, split_one_into_eight_bullet_wave2, enemyBullet, "Sphere.Round.Wave2");
	InitSplitOneIntoEightBullet(split_one_into_eight_count, split_one_into_eight_bullet_wave3, enemyBullet, "Sphere.Round.Wave3");


	return enemyBullet;
}


void BulletHellFactory::InitSplitOneIntoEightBullet(
	int split_one_into_eight_wave, Shared<EnemyBullet>& split_one_into_eight_bullet, std::list<Shared<EnemyBullet>>& enemyBullet, const std::string& wave)
{
	for (int i = 0; i < split_one_into_eight_wave; i++) {

		split_one_into_eight_bullet = std::make_shared<EnemyBullet>(EnemyBullet::SHAPE::Sphere, EnemyBullet::COLOR::Yellow, 12.0f);

		split_one_into_eight_bullet->_radius = 65.0f;
		split_one_into_eight_bullet->_angle = (2.0f * tnl::PI / 8) * i;
		
		split_one_into_eight_bullet->_mesh->pos_.x = _enemyManager->GetEnemyBossPosition().x + split_one_into_eight_bullet->_radius * cos(split_one_into_eight_bullet->_angle);
		split_one_into_eight_bullet->_mesh->pos_.y = _enemyManager->GetEnemyBossPosition().y + split_one_into_eight_bullet->_mesh->pos_.y;;
		split_one_into_eight_bullet->_mesh->pos_.z = _enemyManager->GetEnemyBossPosition().z + split_one_into_eight_bullet->_radius * sin(split_one_into_eight_bullet->_angle);
		
		split_one_into_eight_bullet->_id = i;
		split_one_into_eight_bullet->_allBulletCountByType = split_one_into_eight_wave;
		split_one_into_eight_bullet->color = EnemyBullet::COLOR::Yellow;
		split_one_into_eight_bullet->_isActive = true;
		split_one_into_eight_bullet->_movementsType = wave;

		enemyBullet.push_back(split_one_into_eight_bullet);
	}
}



std::list<Shared<EnemyBullet>> BulletHellFactory::CreateBulletHell_SilentSerena_Patchouli() {

	std::list<Shared<EnemyBullet>> enemyBullet;


	// ëSï˚å¸òAéÀíe--------------------------------------------------------------------------------------------------------------------------
	int circle_contiguous_bulletNum = 320;
	for (int i = 0; i < circle_contiguous_bulletNum; i++) {

		Shared<EnemyBullet> circle_contiguous_bullet = std::make_shared<EnemyBullet>(EnemyBullet::SHAPE::Sphere, EnemyBullet::COLOR::EmeraldGreen, 15.0f);

		circle_contiguous_bullet->_mesh->pos_.x = circle_contiguous_bullet->_mesh->pos_.x;
		circle_contiguous_bullet->_mesh->pos_.y = circle_contiguous_bullet->_mesh->pos_.y;
		circle_contiguous_bullet->_mesh->pos_.z = circle_contiguous_bullet->_mesh->pos_.z;

		circle_contiguous_bullet->_id = i;
		circle_contiguous_bullet->color = EnemyBullet::COLOR::EmeraldGreen;
		circle_contiguous_bullet->_isActive = true;

		enemyBullet.push_back(circle_contiguous_bullet);
	}


	// ÉXÉçÅ[Ç≈ìÆÇ≠ÉâÉìÉ_ÉÄíe--------------------------------------------------------------------------------------------------------------------------
	int slowly_coming_bulletNum = 50;
	for (int i = 0; i < slowly_coming_bulletNum; i++) {

		Shared<EnemyBullet> slowly_coming_bullet = std::make_shared<EnemyBullet>(EnemyBullet::SHAPE::Sphere, EnemyBullet::COLOR::Blue,10.0f);

		std::random_device rd;
		std::mt19937 mt(rd());


		std::uniform_real_distribution<float> dist_x(-180.0, 180.0);
		std::uniform_real_distribution<float> dist_y(-50.0, 100.0);
		std::uniform_real_distribution<float> dist_z(-180.0, 180.0);

		slowly_coming_bullet->_mesh->pos_.x = slowly_coming_bullet->_mesh->pos_.x + dist_x(mt);
		slowly_coming_bullet->_mesh->pos_.y = slowly_coming_bullet->_mesh->pos_.y + dist_y(mt);
		slowly_coming_bullet->_mesh->pos_.z = slowly_coming_bullet->_mesh->pos_.z + dist_z(mt);

		slowly_coming_bullet->_id = i;
		slowly_coming_bullet->color = EnemyBullet::COLOR::Blue;
		slowly_coming_bullet->_isActive = true;

		enemyBullet.push_back(slowly_coming_bullet);
	}

	return enemyBullet;
}





Shared<EnemyBullet> BulletHellFactory::ReuseBulletHellsBullet_SilentSerena(std::map<int, Shared<EnemyBullet>> bltHellsBlt_map, int id) {

	// bulletHellBulletMapì‡Ç…ÉLÅ[Ç™idÇ≈Ç†ÇÈóvëfÇ™å©Ç¬Ç©ÇÁÇ»Ç©Ç¡ÇΩèÍçá
	if (bltHellsBlt_map.find(id) == bltHellsBlt_map.end()) {

		//Shared<EnemyBullet> bulletHell = std::make_shared<EnemyBullet>(id);
		//bltHellsBlt_map[id] = bulletHell;
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
	case BulletHell::TYPE::Normal_Patchouli:
		return CreateBulletHell_Normal_Patchouli();
		break;
	case BulletHell::TYPE::MetalFatigue_Patchouli:
		return CreateBulletHell_MetalFatigue_Patchouli();
		break;
	case BulletHell::TYPE::SilentSerena_Patchouli:
		return CreateBulletHell_SilentSerena_Patchouli();
		break;
	case BulletHell::TYPE::Perfect_Freeze:
		return CreateBulletHell_PerfectFreeze();
		break;
	case BulletHell::TYPE::KeroChan_StandsFirm_AgainstTheStorm:
		return CreateBulletHell_KeroChanStandsFirm_AgainstTheStorm();
		break;
	}
	return std::list<Shared<EnemyBullet>>();
}