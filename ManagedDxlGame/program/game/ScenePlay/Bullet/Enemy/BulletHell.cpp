#include "BulletHell.h"
#include "BulletHellFactory.h"
#include "EnemyBullet.h"
#include "../../ScenePlay.h"



BulletHell::BulletHell(const Shared<dxe::Mesh>& bossMesh) : _bossMesh_ref(bossMesh) {}



void BulletHell::ShotBulletHell_Normal_Patchouli(const float& delta_time) {

	for (auto& bullet : ScenePlay::_bullet_normal_patchouli) {
		int id = bullet->_id;

		ScenePlay::_EVERYSINGLE_BLTINFO_T_NORMAL_PATCHOULI[id].moveDirection = bullet->_moveDirection;
	}


	for (auto& it_blt_hell_blt : ScenePlay::_bullet_normal_patchouli) {

		if (it_blt_hell_blt->color == EnemyBullet::COLOR::Blue && it_blt_hell_blt->_movementsType == "Sphere.Round") {


			it_blt_hell_blt->_angle = (2.0f * tnl::PI / 8) * it_blt_hell_blt->_id;

			double dx = _bossMesh_ref->pos_.x - it_blt_hell_blt->_mesh->pos_.x;
			double dy = _bossMesh_ref->pos_.y - it_blt_hell_blt->_mesh->pos_.y;
			double dz = _bossMesh_ref->pos_.z - it_blt_hell_blt->_mesh->pos_.z;

			float radius = sqrt(dx * dx + dy * dy + dz * dz);

			// 左回転
			if (it_blt_hell_blt->_id % 2 == 0) {
				it_blt_hell_blt->_angle += delta_time;

			}
			// 右回転
			else {

				it_blt_hell_blt->_angle -= delta_time;
			}


			it_blt_hell_blt->_moveDirection.x = /*_bossMesh_ref->pos_.x +*/ cos(it_blt_hell_blt->_angle) * radius;
			it_blt_hell_blt->_moveDirection.z = /*_bossMesh_ref->pos_.z +*/ sin(it_blt_hell_blt->_angle) * radius;

			it_blt_hell_blt->_moveDirection.normalize();

			//it_blt_hell_blt->_mesh->pos_.x += it_blt_hell_blt->_moveDirection.x * delta_time * 100;
			//it_blt_hell_blt->_mesh->pos_.z += it_blt_hell_blt->_moveDirection.z * delta_time * 100;

			float sin = std::sin(tnl::PI / 180.f);
			float cos = std::sin(tnl::PI / 180.f);

			tnl::Vector3 myPos = ScenePlay::_EVERYSINGLE_BLTINFO_T_NORMAL_PATCHOULI[it_blt_hell_blt->_id].originPos;
			tnl::Vector3 axisVec(0.0f, 0.0f, 1.0f);

			it_blt_hell_blt->_mesh->pos_ = myPos * (cos * cos - sin * sin)
				+ axisVec.cross(myPos) * 2.0f * sin * cos
				+ axisVec * axisVec.dot(myPos) * 2.0f * sin * sin;

			myPos = it_blt_hell_blt->_mesh->pos_;
		}

		if (it_blt_hell_blt->color == EnemyBullet::COLOR::White && it_blt_hell_blt->_movementsType == "Cylinder.Round") {


			it_blt_hell_blt->_angle = (2.0f * tnl::PI / 8) * it_blt_hell_blt->_id;

			double dx = _bossMesh_ref->pos_.x - it_blt_hell_blt->_mesh->pos_.x;
			double dy = _bossMesh_ref->pos_.y - it_blt_hell_blt->_mesh->pos_.y;
			double dz = _bossMesh_ref->pos_.z - it_blt_hell_blt->_mesh->pos_.z;

			float radius = sqrt(dx * dx + dy * dy + dz * dz);

			// 左回転
			if (it_blt_hell_blt->_id % 2 == 0) {
				it_blt_hell_blt->_angle += delta_time;

			}
			// 右回転
			else {

				it_blt_hell_blt->_angle -= delta_time;
			}

			it_blt_hell_blt->_moveDirection.x = /*_bossMesh_ref->pos_.x +*/ cos(it_blt_hell_blt->_angle) * radius;
			it_blt_hell_blt->_moveDirection.z = /*_bossMesh_ref->pos_.z +*/ sin(it_blt_hell_blt->_angle) * radius;

			it_blt_hell_blt->_moveDirection.normalize();

			it_blt_hell_blt->_mesh->pos_.x += it_blt_hell_blt->_moveDirection.x * delta_time * 100;
			it_blt_hell_blt->_mesh->pos_.z += it_blt_hell_blt->_moveDirection.z * delta_time * 100;
		}



		// 全方位
		if (it_blt_hell_blt->color == EnemyBullet::COLOR::EmeraldGreen && it_blt_hell_blt->_movementsType == "Sphere.Straight") {

			std::vector<Shared<EnemyBullet>> group1, group2, group3, group4;
			std::vector<Shared<EnemyBullet>> everyDir_bullets; // 全方位弾の全てのオブジェクトを格納しソートする

			for (int i = 0; i < ScenePlay::_bullet_normal_patchouli.size(); i++) {

				if (ScenePlay::_bullet_normal_patchouli[i]->_movementsType == "Sphere.Round" || ScenePlay::_bullet_normal_patchouli[i]->_movementsType == "Cylinder.Round") {
					continue;
				}
				else {
					everyDir_bullets.push_back(ScenePlay::_bullet_normal_patchouli[i]);
				}
			}

			// 生成位置に基づいてリストをソートしたいが、現状できていない

			int bullets_per_group = _EVERYDIRECTION_BULLETCOUNT_T_NORMAL_PATCHOULI / 4;
			int bullets_per_round = bullets_per_group / 3;

			for (int i = 0; i < bullets_per_group; i++) {

				if (it_blt_hell_blt->_id < _ROUND_BULLETCOUNT_T_NORMAL_PATCHOULI + bullets_per_group) {
					group1.push_back(it_blt_hell_blt);

				}
				if (it_blt_hell_blt->_id < _ROUND_BULLETCOUNT_T_NORMAL_PATCHOULI + bullets_per_group * 2) {
					group2.push_back(it_blt_hell_blt);

				}
				if (it_blt_hell_blt->_id < _ROUND_BULLETCOUNT_T_NORMAL_PATCHOULI + bullets_per_group * 3) {
					group3.push_back(it_blt_hell_blt);

				}
				if (it_blt_hell_blt->_id < _ROUND_BULLETCOUNT_T_NORMAL_PATCHOULI + bullets_per_group * 4) {
					group4.push_back(it_blt_hell_blt);

				}

			}


			//if (it_blt_hell_blt->_id % 16 == 0) {

			//	it_blt_hell_blt->_angle = (2.0f * tnl::PI / 8) * it_blt_hell_blt->_id;

			//	double dx = _bossMesh_ref->pos_.x - it_blt_hell_blt->_mesh->pos_.x;
			//	double dy = _bossMesh_ref->pos_.y - it_blt_hell_blt->_mesh->pos_.y;
			//	double dz = _bossMesh_ref->pos_.z - it_blt_hell_blt->_mesh->pos_.z;

			//	float radius = sqrt(dx * dx + dy * dy + dz * dz);

			//	it_blt_hell_blt->_moveDirection.x = _bossMesh_ref->pos_.x + cos(it_blt_hell_blt->_angle) * radius;
			//	it_blt_hell_blt->_moveDirection.z = _bossMesh_ref->pos_.z + sin(it_blt_hell_blt->_angle) * radius;

			//	it_blt_hell_blt->_moveDirection.normalize();

			//	it_blt_hell_blt->_mesh->pos_.x += it_blt_hell_blt->_moveDirection.x * delta_time * 100;
			//	it_blt_hell_blt->_mesh->pos_.z += it_blt_hell_blt->_moveDirection.z * delta_time * 100;
			//}
			//else if (it_blt_hell_blt->_id > 24 && it_blt_hell_blt->_id < 48) {

			//	it_blt_hell_blt->_angle = (2.0f * tnl::PI / 8) * it_blt_hell_blt->_id;

			//	double dx = _bossMesh_ref->pos_.x - it_blt_hell_blt->_mesh->pos_.x;
			//	double dy = _bossMesh_ref->pos_.y - it_blt_hell_blt->_mesh->pos_.y;
			//	double dz = _bossMesh_ref->pos_.z - it_blt_hell_blt->_mesh->pos_.z;

			//	float radius = sqrt(dx * dx + dy * dy + dz * dz);

			//	it_blt_hell_blt->_moveDirection.x = _bossMesh_ref->pos_.x + cos(it_blt_hell_blt->_angle) * radius;
			//	it_blt_hell_blt->_moveDirection.z = _bossMesh_ref->pos_.z + sin(it_blt_hell_blt->_angle) * radius;

			//	it_blt_hell_blt->_moveDirection.normalize();

			//	it_blt_hell_blt->_mesh->pos_.x += it_blt_hell_blt->_moveDirection.x * delta_time * 100;
			//	it_blt_hell_blt->_mesh->pos_.z += it_blt_hell_blt->_moveDirection.z * delta_time * 100;

			//}
			//else if (it_blt_hell_blt->_id > 48 && it_blt_hell_blt->_id < 72) {

			//	it_blt_hell_blt->_angle = (2.0f * tnl::PI / 8) * it_blt_hell_blt->_id;

			//	double dx = _bossMesh_ref->pos_.x - it_blt_hell_blt->_mesh->pos_.x;
			//	double dy = _bossMesh_ref->pos_.y - it_blt_hell_blt->_mesh->pos_.y;
			//	double dz = _bossMesh_ref->pos_.z - it_blt_hell_blt->_mesh->pos_.z;

			//	float radius = sqrt(dx * dx + dy * dy + dz * dz);

			//	it_blt_hell_blt->_moveDirection.x = _bossMesh_ref->pos_.x + cos(it_blt_hell_blt->_angle) * radius;
			//	it_blt_hell_blt->_moveDirection.z = _bossMesh_ref->pos_.z + sin(it_blt_hell_blt->_angle) * radius;

			//	it_blt_hell_blt->_moveDirection.normalize();

			//	it_blt_hell_blt->_mesh->pos_.x += it_blt_hell_blt->_moveDirection.x * delta_time * 100;
			//	it_blt_hell_blt->_mesh->pos_.z += it_blt_hell_blt->_moveDirection.z * delta_time * 100;

			//}
			//else {
			//	it_blt_hell_blt->_angle = (2.0f * tnl::PI / 8) * it_blt_hell_blt->_id;

			//	double dx = _bossMesh_ref->pos_.x - it_blt_hell_blt->_mesh->pos_.x;
			//	double dy = _bossMesh_ref->pos_.y - it_blt_hell_blt->_mesh->pos_.y;
			//	double dz = _bossMesh_ref->pos_.z - it_blt_hell_blt->_mesh->pos_.z;

			//	float radius = sqrt(dx * dx + dy * dy + dz * dz);

			//	it_blt_hell_blt->_moveDirection.x = _bossMesh_ref->pos_.x + cos(it_blt_hell_blt->_angle) * radius;
			//	it_blt_hell_blt->_moveDirection.z = _bossMesh_ref->pos_.z + sin(it_blt_hell_blt->_angle) * radius;

			//	it_blt_hell_blt->_moveDirection.normalize();

			//	it_blt_hell_blt->_mesh->pos_.x += it_blt_hell_blt->_moveDirection.x * delta_time * 100;
			//	it_blt_hell_blt->_mesh->pos_.z += it_blt_hell_blt->_moveDirection.z * delta_time * 100;

			//}
		}


		CheckLifeTimeDistance(it_blt_hell_blt);
	}
}




void BulletHell::ShotBulletHell_MetalFatigue_Patchouli(const float& delta_time) {

	for (auto& bullet : ScenePlay::_bullet_metalFatigue_patchouli) {
		int id = bullet->_id;

		ScenePlay::_EVERYSINGLE_BLTINFO_T_METALFATIGUE_PATCHOULI[id].moveDirection = bullet->_moveDirection;
	}


	for (auto it_blt_hell_blt : ScenePlay::_bullet_metalFatigue_patchouli) {

		// 遅延処理で使用するタイマー
		std::map<Shared<EnemyBullet>, float> bullet_timers;

		if (it_blt_hell_blt->color == EnemyBullet::COLOR::Yellow) {

			// 各弾自身をキーとしてそれぞれが固有の時間を計測・管理する
			bullet_timers[it_blt_hell_blt] += delta_time;

			float delay_origin = 1.0f;  // Sphere.Round.Origin
			float delay_wave1 = 2.0f;   // Sphere.Round.Wave1
			float delay_wave2 = 3.0f;   // Sphere.Round.Wave2


			tnl::Vector3 bullet_move_orbit_origin;
			float theta = (2.f * tnl::PI / 8) * it_blt_hell_blt->_id;

			// 初弾
			if (it_blt_hell_blt->_movementsType == "Sphere.Round.Origin") {

				float new_x = _bossMesh_ref->pos_.x + sin(theta) * delta_time;
				float new_y = _bossMesh_ref->pos_.y + cos(theta) * delta_time;

				if (abs(new_x) <= it_blt_hell_blt->_radius) {
					bullet_move_orbit_origin.x += new_x;
				}
				if (abs(new_y) <= it_blt_hell_blt->_radius) {
					bullet_move_orbit_origin.y += new_y;
				}

				float current_distance = (_bossMesh_ref->pos_ - it_blt_hell_blt->_mesh->pos_).length();

				// 指定した半径に座標が到達したらリセット
				if (current_distance > it_blt_hell_blt->_radius)
					it_blt_hell_blt->_isActive = false;
				else
					it_blt_hell_blt->_mesh->pos_ += bullet_move_orbit_origin * delta_time * 4000.0f;
			}

			if (it_blt_hell_blt->_movementsType == "Sphere.Round.Origin" && bullet_timers[it_blt_hell_blt] >= delay_origin) {
				bullet_timers[it_blt_hell_blt] = 0.0f;
			}
			else if (it_blt_hell_blt->_movementsType == "Sphere.Round.Wave1" && bullet_timers[it_blt_hell_blt] >= delay_wave1) {
				bullet_timers[it_blt_hell_blt] = 0.0f;  // タイマーのリセット
			}
			else if (it_blt_hell_blt->_movementsType == "Sphere.Round.Wave2" && bullet_timers[it_blt_hell_blt] >= delay_wave2) {
				bullet_timers[it_blt_hell_blt] = 0.0f;  // タイマーのリセット
			}

			tnl::Vector3 bullet_move_orbit_wave;

			bullet_move_orbit_wave.y = cos(theta) * delta_time;
			bullet_move_orbit_wave.z = sin(theta) * delta_time;


			it_blt_hell_blt->_mesh->pos_ += bullet_move_orbit_wave * delta_time * 4000.0f;

		}

		CheckLifeTimeDistance(it_blt_hell_blt);

	}
}


void BulletHell::ShotBulletHell_SilentSerena_Patchouli(const float& delta_time) {


	for (auto& bullet : ScenePlay::_bullet_silentSerena_patchouli) {
		int id = bullet->_id;

		ScenePlay::_EVERYSINGLE_BLTINFO_T_SILENTSERENA_PATCHOULI[id].moveDirection = bullet->_moveDirection;
	}



	for (auto it_blt_hell_blt : ScenePlay::_bullet_silentSerena_patchouli) {


		if (it_blt_hell_blt->color == EnemyBullet::COLOR::EmeraldGreen) {

			float theta = (2.f * tnl::PI / ScenePlay::_bullet_silentSerena_patchouli.size()) * it_blt_hell_blt->_id;
			float pi = tnl::PI / 1.001f;

			tnl::Vector3 bullet_spawn_pos;

			bullet_spawn_pos.x = _bossMesh_ref->pos_.x + cos(theta) * sin(pi);
			bullet_spawn_pos.y = _bossMesh_ref->pos_.y;
			bullet_spawn_pos.z = _bossMesh_ref->pos_.z + sin(theta) * sin(pi);

			tnl::Vector3 move_dir = bullet_spawn_pos.Normalize(bullet_spawn_pos);

			it_blt_hell_blt->_mesh->pos_ += move_dir * delta_time * 200;
		}
		if (it_blt_hell_blt->color == EnemyBullet::COLOR::Blue) {


			float theta = (2.f * tnl::PI / ScenePlay::_bullet_silentSerena_patchouli.size()) * it_blt_hell_blt->_id;
			float pi = tnl::PI;

			tnl::Vector3 bullet_spawn_pos;

			bullet_spawn_pos.x = _bossMesh_ref->pos_.x + cos(theta) * sin(pi);
			bullet_spawn_pos.y = _bossMesh_ref->pos_.y;
			bullet_spawn_pos.z = _bossMesh_ref->pos_.z + sin(theta) * sin(pi);

			tnl::Vector3 move_dir = tnl::Vector3::TransformCoord({ 0,0,1 }, _bossMesh_ref->rot_);

			it_blt_hell_blt->_mesh->pos_ += move_dir * delta_time * 150;
		}

		CheckLifeTimeDistance(it_blt_hell_blt);
	}
}



void BulletHell::ShotBulletHell_Normal_Cirno(const float& delta_time) {

	for (auto& bullet : ScenePlay::_bullet_normal_cirno) {
		int id = bullet->_id;

		ScenePlay::_EVERYSINGLE_BLTINFO_T_NORMAL_CIRNO[id].moveDirection = bullet->_moveDirection;
	}


	for (auto it_blt_hell_blt : ScenePlay::_bullet_normal_cirno) {

		// 遅延処理で使用するタイマー
		std::map<Shared<EnemyBullet>, float> bullet_timers;

		if (it_blt_hell_blt->color == EnemyBullet::COLOR::Yellow) {

			// 各弾自身をキーとしてそれぞれが固有の時間を計測・管理する
			bullet_timers[it_blt_hell_blt] += delta_time;

			float delay_origin = 1.0f;  // Sphere.Round.Origin
			float delay_wave1 = 2.0f;   // Sphere.Round.Wave1
			float delay_wave2 = 3.0f;   // Sphere.Round.Wave2


			tnl::Vector3 bullet_move_orbit_origin;
			float theta = (2.f * tnl::PI / 8) * it_blt_hell_blt->_id;

			// 初弾
			if (it_blt_hell_blt->_movementsType == "Sphere.Round.Origin") {

				float new_x = _bossMesh_ref->pos_.x + sin(theta) * delta_time;
				float new_y = _bossMesh_ref->pos_.y + cos(theta) * delta_time;

				if (abs(new_x) <= it_blt_hell_blt->_radius) {
					bullet_move_orbit_origin.x += new_x;
				}
				if (abs(new_y) <= it_blt_hell_blt->_radius) {
					bullet_move_orbit_origin.y += new_y;
				}

				float current_distance = (_bossMesh_ref->pos_ - it_blt_hell_blt->_mesh->pos_).length();

				// 指定した半径に座標が到達したらリセット
				if (current_distance > it_blt_hell_blt->_radius)
					it_blt_hell_blt->_isActive = false;
				else
					it_blt_hell_blt->_mesh->pos_ += bullet_move_orbit_origin * delta_time * 4000.0f;
			}
		}
		if (it_blt_hell_blt->color == EnemyBullet::COLOR::EmeraldGreen) {

		}
	}
}

void BulletHell::ShotBulletHell_IcicleFall_Cirno(const float& delta_time) {

}
void BulletHell::ShotBulletHell_PerfectFreeze_Cirno(const float& delta_time) {

}


void BulletHell::ShotBulletHell_KeroChanStandsFirm_AgainstTheStorm(const float& delta_time) {

}


void BulletHell::CheckLifeTimeDistance(Shared<EnemyBullet>& it_bltHell)
{
	static tnl::Vector3 start = it_bltHell->_mesh->pos_;

	float dx = it_bltHell->_mesh->pos_.x - start.x;
	float dy = it_bltHell->_mesh->pos_.y - start.y;
	float dz = it_bltHell->_mesh->pos_.z - start.z;

	float current_distance = sqrt(dx * dx + dy * dy + dz * dz);

	if (abs(current_distance) > 1000) it_bltHell->_isActive = false;
}
