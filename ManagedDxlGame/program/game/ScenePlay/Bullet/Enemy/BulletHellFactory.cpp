#include <random>
#include "BulletHell.h"
#include "BulletHellFactory.h"
#include "../../../Manager/Enemy/EnemyManager.h"
#include "../../ScenePlay.h"
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


std::vector<Shared<EnemyBullet>> BulletHellFactory::CreateBulletHell_Normal_Patchouli() {

	std::vector<Shared<EnemyBullet>> enemyBullet;

	// âÒì]ópÇÃíeê∂ê¨ (ç∂âÒì]Ç∆âEâÒì]ÇÃÇQéÌóﬁÇ™Ç†ÇÈÇ™ÅAÇ±Ç±Ç≈ÇÕëSÇƒÇìØéûÇ…ê∂ê¨Ç∑ÇÈÅj
	for (int i = 0; i < _ROUND_BULLETCOUNT_T_NORMAL_PATCHOULI; i++) {

		// ãÖëÃ--------------------------------------------------------------------------------------------------------------------------
		Shared<EnemyBullet> round_bullet = std::make_shared<EnemyBullet>(EnemyBullet::SHAPE::Sphere, EnemyBullet::COLOR::Blue, 30.0f);

		round_bullet->_angle = (2.0f * tnl::PI / _ROUND_BULLETCOUNT_T_NORMAL_PATCHOULI) * i;
		round_bullet->_radius = 90.0f;

		round_bullet->_mesh->pos_.x = _firstBossSpawnPosition.x + round_bullet->_radius * cos(round_bullet->_angle);
		round_bullet->_mesh->pos_.y = _firstBossSpawnPosition.y;
		round_bullet->_mesh->pos_.z = _firstBossSpawnPosition.z + round_bullet->_radius * sin(round_bullet->_angle);

		round_bullet->_id = ScenePlay::_bulletUniqueID_normal_patchouli++;
		round_bullet->_speed = 150.0f;
		round_bullet->color = EnemyBullet::COLOR::Blue;
		round_bullet->_isActive = true;
		round_bullet->_movementsType = "Sphere.Round";

		enemyBullet.push_back(round_bullet);

		// ãÖëÃÇ∆àÍèèÇ…ìÆÇ≠åıê¸------------------------------------------------------------------------------------------------------------
		Shared<EnemyBullet> round_bullet_beam = std::make_shared<EnemyBullet>(EnemyBullet::SHAPE::Cylinder, EnemyBullet::COLOR::White, 500.f);
		round_bullet_beam->_angle = (2.0f * tnl::PI / _ROUND_BULLETCOUNT_T_NORMAL_PATCHOULI) * i;
		round_bullet_beam->_radius = 90.0f;
		
		round_bullet_beam->_mesh->pos_.x = round_bullet->_mesh->pos_.x + round_bullet_beam->_radius * cos(round_bullet_beam->_angle);
		round_bullet_beam->_mesh->pos_.y = round_bullet->_mesh->pos_.y;
		round_bullet_beam->_mesh->pos_.z = (round_bullet->_mesh->pos_.z + 100) + round_bullet_beam->_radius * sin(round_bullet_beam->_angle);
		
		float pitch = tnl::PI / 2.0f;

		float angle = atan2(round_bullet->_mesh->pos_.z - _firstBossSpawnPosition.z, round_bullet->_mesh->pos_.x - _firstBossSpawnPosition.x);
		float yaw = angle;

		float roll = 0.f;

		tnl::Quaternion rotation = tnl::Quaternion::RotationRollPitchYawFromVector({ pitch, yaw, roll });

		round_bullet_beam->_mesh->rot_ = rotation;

		round_bullet->_id = ScenePlay::_bulletUniqueID_normal_patchouli++;
		round_bullet_beam->_speed = 150.0f;
		round_bullet_beam->color = EnemyBullet::COLOR::White;
		round_bullet_beam->_isActive = true;
		round_bullet_beam->_movementsType = "Cylinder.Round";


		enemyBullet.push_back(round_bullet_beam);		
	}


	// ëSï˚å¸òAéÀíe--------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < _EVERYDIRECTION_BULLETCOUNT_T_NORMAL_PATCHOULI; i++) {

		Shared<EnemyBullet> every_direction_bullet = std::make_shared<EnemyBullet>(EnemyBullet::SHAPE::Sphere, EnemyBullet::COLOR::EmeraldGreen, 12.0f);

		every_direction_bullet->_radius = 65.0f;
		every_direction_bullet->_angle = (2.0f * tnl::PI / 16) * i;

		every_direction_bullet->_mesh->pos_.x = every_direction_bullet->_radius * cos(every_direction_bullet->_angle);
		every_direction_bullet->_mesh->pos_.y = every_direction_bullet->_mesh->pos_.y;
		every_direction_bullet->_mesh->pos_.z = every_direction_bullet->_radius * sin(every_direction_bullet->_angle);
		
		every_direction_bullet->_id = ScenePlay::_bulletUniqueID_normal_patchouli++;
		every_direction_bullet->color = EnemyBullet::COLOR::EmeraldGreen;
		every_direction_bullet->_isActive = true;
		every_direction_bullet->_movementsType = "Sphere.Straight";


		enemyBullet.push_back(every_direction_bullet);
	}


	return enemyBullet;
}


std::vector<Shared<EnemyBullet>> BulletHellFactory::CreateBulletHell_MetalFatigue_Patchouli() {

	std::vector<Shared<EnemyBullet>> enemyBullet;

	for (int i = 0; i < _EVERYDIRECTION_BULLETCOUNT_T_METALFATIGUE_PATCHOULI; i++) {

		Shared<EnemyBullet> every_direction_bullet = std::make_shared<EnemyBullet>(EnemyBullet::SHAPE::Sphere, EnemyBullet::COLOR::Yellow, 15.0f);

		every_direction_bullet->_radius = 150.0f;
		every_direction_bullet->_angle = (2.0f * tnl::PI / _EVERYDIRECTION_BULLETCOUNT_T_METALFATIGUE_PATCHOULI) * i;

		every_direction_bullet->_mesh->pos_.x = _firstBossSpawnPosition.x;
		every_direction_bullet->_mesh->pos_.y = _firstBossSpawnPosition.y;
		every_direction_bullet->_mesh->pos_.z = _firstBossSpawnPosition.z;

		every_direction_bullet->_id = ScenePlay::_bulletUniqueID_metalFatigue_patchouli++;
		every_direction_bullet->_mesh->pos_;
		every_direction_bullet->color = EnemyBullet::COLOR::Yellow;
		every_direction_bullet->_isActive = true;
		every_direction_bullet->_movementsType = "Sphere.Round.Origin";

		enemyBullet.push_back(every_direction_bullet);
	}


	Shared<EnemyBullet> split_one_into_eight_bullet_wave1;
	//Shared<EnemyBullet> split_one_into_eight_bullet_wave2;
	//Shared<EnemyBullet> split_one_into_eight_bullet_wave3;

	InitSplitOneIntoEightBullet(_SPLITONE_INTOEIGHT_BULLETCOUNT_T_METALFATIGUE_PATCHOULI, split_one_into_eight_bullet_wave1, enemyBullet, "Sphere.Round.Wave1");
	//InitSplitOneIntoEightBullet(split_one_into_eight_count, split_one_into_eight_bullet_wave2, enemyBullet, "Sphere.Round.Wave2");
	//InitSplitOneIntoEightBullet(split_one_into_eight_count, split_one_into_eight_bullet_wave3, enemyBullet, "Sphere.Round.Wave3");


	return enemyBullet;
}


void BulletHellFactory::InitSplitOneIntoEightBullet(
	int split_one_into_eight_wave, Shared<EnemyBullet>& split_one_into_eight_bullet, std::vector<Shared<EnemyBullet>>& enemyBullet, const std::string& wave)
{
	for (int i = 0; i < split_one_into_eight_wave; i++) {

		split_one_into_eight_bullet = std::make_shared<EnemyBullet>(EnemyBullet::SHAPE::Sphere, EnemyBullet::COLOR::Yellow, 12.0f);

		split_one_into_eight_bullet->_radius = 65.0f;
		split_one_into_eight_bullet->_angle = (2.0f * tnl::PI / 8) * i;
		
		split_one_into_eight_bullet->_mesh->pos_.x = _firstBossSpawnPosition.x + split_one_into_eight_bullet->_radius * cos(split_one_into_eight_bullet->_angle);
		split_one_into_eight_bullet->_mesh->pos_.y = _firstBossSpawnPosition.y + split_one_into_eight_bullet->_mesh->pos_.y;;
		split_one_into_eight_bullet->_mesh->pos_.z = _firstBossSpawnPosition.z + split_one_into_eight_bullet->_radius * sin(split_one_into_eight_bullet->_angle);
		
		split_one_into_eight_bullet->_id = i;
		split_one_into_eight_bullet->color = EnemyBullet::COLOR::Yellow;
		split_one_into_eight_bullet->_isActive = true;
		split_one_into_eight_bullet->_movementsType = wave;

		enemyBullet.push_back(split_one_into_eight_bullet);
	}
}




std::vector<Shared<EnemyBullet>> BulletHellFactory::CreateBulletHell_SilentSerena_Patchouli() {

	std::vector<Shared<EnemyBullet>> enemyBullet;

	// ëSï˚å¸òAéÀíe--------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < _CIRCLECONTIGUOUS_BULLETCOUNT_T_SILENTSERENA_PATCHOULI; i++) {

		Shared<EnemyBullet> circle_contiguous_bullet = std::make_shared<EnemyBullet>(EnemyBullet::SHAPE::Sphere, EnemyBullet::COLOR::EmeraldGreen, 15.0f);

		circle_contiguous_bullet->_radius = 150.0f;
		circle_contiguous_bullet->_angle = (2.0f * tnl::PI / _CIRCLECONTIGUOUS_BULLETCOUNT_T_SILENTSERENA_PATCHOULI) * i;
		
		circle_contiguous_bullet->_mesh->pos_.x = _firstBossSpawnPosition.x;
		circle_contiguous_bullet->_mesh->pos_.y = _firstBossSpawnPosition.y;
		circle_contiguous_bullet->_mesh->pos_.z = _firstBossSpawnPosition.z;
		
		circle_contiguous_bullet->_id = ScenePlay::_bulletUniqueID_silentSerena_patchouli++;
		circle_contiguous_bullet->color = EnemyBullet::COLOR::Yellow;
		circle_contiguous_bullet->_isActive = true;
		circle_contiguous_bullet->_movementsType = "Sphere.Round";

		enemyBullet.push_back(circle_contiguous_bullet);
	}


	// ÉXÉçÅ[Ç≈ìÆÇ≠ÉâÉìÉ_ÉÄíe--------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < _SLOWLYCOMING_BULLETCOUNT_T_SILENTSERENA_PATCHOULI; i++) {

		Shared<EnemyBullet> slowly_coming_bullet = std::make_shared<EnemyBullet>(EnemyBullet::SHAPE::Sphere, EnemyBullet::COLOR::Blue,10.0f);

		std::random_device rd;
		std::mt19937 mt(rd());

		std::uniform_real_distribution<float> dist_x(-180.0, 180.0);
		std::uniform_real_distribution<float> dist_y(-50.0, 100.0);
		std::uniform_real_distribution<float> dist_z(-180.0, 180.0);

		slowly_coming_bullet->_mesh->pos_.x = _firstBossSpawnPosition.x + dist_x(mt);
		slowly_coming_bullet->_mesh->pos_.y = _firstBossSpawnPosition.y + dist_y(mt);
		slowly_coming_bullet->_mesh->pos_.z = _firstBossSpawnPosition.z + dist_z(mt);

		slowly_coming_bullet->_id = ScenePlay::_bulletUniqueID_silentSerena_patchouli++;
		slowly_coming_bullet->color = EnemyBullet::COLOR::Blue;
		slowly_coming_bullet->_isActive = true;
		slowly_coming_bullet->_movementsType = "Sphere.RandomStraight";

		enemyBullet.push_back(slowly_coming_bullet);
	}

	return enemyBullet;
}



std::vector<Shared<EnemyBullet>> BulletHellFactory::CreateBulletHell_Normal_Cirno() {

	std::vector<Shared<EnemyBullet>> enemyBullet;

	for (int i = 0; i < _STRAIGHTAPPROACH_BULLETCOUNT_T_NORMAL_CIRNO; i++) {

		Shared<EnemyBullet> straight_approach_bullet = std::make_shared<EnemyBullet>(EnemyBullet::SHAPE::Sphere, EnemyBullet::COLOR::EmeraldGreen, 15.0f);

		straight_approach_bullet->_radius = 150.0f;
		straight_approach_bullet->_angle = (2.0f * tnl::PI / _STRAIGHTAPPROACH_BULLETCOUNT_T_NORMAL_CIRNO) * i;
		
		straight_approach_bullet->_mesh->pos_.x = _firstBossSpawnPosition.x;
		straight_approach_bullet->_mesh->pos_.y = _firstBossSpawnPosition.y;
		straight_approach_bullet->_mesh->pos_.z = _firstBossSpawnPosition.z;
		
		straight_approach_bullet->_id = ScenePlay::_bulletUniqueID_silentSerena_patchouli++;
		straight_approach_bullet->color = EnemyBullet::COLOR::Yellow;
		straight_approach_bullet->_isActive = true;
		straight_approach_bullet->_movementsType = "Sphere.Round";

		enemyBullet.push_back(straight_approach_bullet);
	}

	for (int i = 0; i < _EVERYDIRECTION_BULLETCOUNT_T_Normal_CIRNO; i++) {

		Shared<EnemyBullet> every_direction_bullet = std::make_shared<EnemyBullet>(EnemyBullet::SHAPE::Sphere, EnemyBullet::COLOR::Yellow, 15.0f);

		every_direction_bullet->_radius = 150.0f;
		every_direction_bullet->_angle = (2.0f * tnl::PI / _EVERYDIRECTION_BULLETCOUNT_T_Normal_CIRNO) * i;

		every_direction_bullet->_mesh->pos_.x = _firstBossSpawnPosition.x;
		every_direction_bullet->_mesh->pos_.y = _firstBossSpawnPosition.y;
		every_direction_bullet->_mesh->pos_.z = _firstBossSpawnPosition.z;

		every_direction_bullet->_id = ScenePlay::_bulletUniqueID_metalFatigue_patchouli++;
		every_direction_bullet->_mesh->pos_;
		every_direction_bullet->color = EnemyBullet::COLOR::Yellow;
		every_direction_bullet->_isActive = true;
		every_direction_bullet->_movementsType = "Sphere.Round.Origin";

		enemyBullet.push_back(every_direction_bullet);
	}


	return enemyBullet;

}


std::vector<Shared<EnemyBullet>> BulletHellFactory::CreateBulletHell_IcicleFall_Cirno() {

	std::vector<Shared<EnemyBullet>> enemyBullet;
	return enemyBullet;

}



std::vector<Shared<EnemyBullet>> BulletHellFactory::CreateBulletHell_PerfectFreeze() {
	std::vector<Shared<EnemyBullet>> enemyBullet;
	return enemyBullet;
}


std::vector<Shared<EnemyBullet>> BulletHellFactory::CreateBulletHell_KeroChanStandsFirm_AgainstTheStorm() {

	std::vector<Shared<EnemyBullet>> enemyBullet;

	return enemyBullet;

}



std::vector<Shared<EnemyBullet>> BulletHellFactory::CreateBulletHell(const BulletHell::TYPE type) {

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
	case BulletHell::TYPE::Normal_Cirno:
		return CreateBulletHell_Normal_Cirno();
		break;
	case BulletHell::TYPE::IcicleFall_Cirno:
		return CreateBulletHell_IcicleFall_Cirno();
		break;
	case BulletHell::TYPE::Perfect_Freeze_Cirno:
		return CreateBulletHell_PerfectFreeze();
		break;
	case BulletHell::TYPE::KeroChan_StandsFirm_AgainstTheStorm_Suwako:
		return CreateBulletHell_KeroChanStandsFirm_AgainstTheStorm();
		break;
	}
	return std::vector<Shared<EnemyBullet>>();
}