#include "BulletHell.h"
#include "BulletHellFactory.h"
#include "EnemyBullet.h"
#include "../../ScenePlay.h"



BulletHell::BulletHell(const Shared<dxe::Mesh>& bossMesh) : _bossMesh_ref(bossMesh) {}



void BulletHell::ShotBulletHell_Normal_Patchouli(const float& delta_time) {

	for (auto& bullet : ScenePlay::_bullet_normal_patchouli) {
		int id = bullet->_id;

		ScenePlay::_BLTINFO_T_NORMAL_PATCHOULI[id].moveDirection = bullet->_moveDirection;
	}


	for (auto& it_blt_hell_blt : ScenePlay::_bullet_normal_patchouli) {

		if (it_blt_hell_blt->color == EnemyBullet::COLOR::Blue && it_blt_hell_blt->_movementsType == "Sphere.Round") {


			it_blt_hell_blt->_angle = (2.0f * tnl::PI / 8) * it_blt_hell_blt->_id;



			double dx = _bossMesh_ref->pos_.x - it_blt_hell_blt->_mesh->pos_.x;
			double dy = _bossMesh_ref->pos_.y - it_blt_hell_blt->_mesh->pos_.y;
			double dz = _bossMesh_ref->pos_.z - it_blt_hell_blt->_mesh->pos_.z;

			float radius = sqrt(dx * dx + dy * dy + dz * dz);

			// ¶‰ñ“]
			if (it_blt_hell_blt->_id % 2 == 0) {
				it_blt_hell_blt->_angle += delta_time;

			}
			// ‰E‰ñ“]
			else {

				it_blt_hell_blt->_angle -= delta_time;
			}


			it_blt_hell_blt->_moveDirection.x = /*_bossMesh_ref->pos_.x +*/ cos(it_blt_hell_blt->_angle) * radius;
			it_blt_hell_blt->_moveDirection.z = /*_bossMesh_ref->pos_.z +*/ sin(it_blt_hell_blt->_angle) * radius;

			it_blt_hell_blt->_moveDirection.normalize();

			it_blt_hell_blt->_mesh->pos_.x += it_blt_hell_blt->_moveDirection.x * delta_time * 100;
			it_blt_hell_blt->_mesh->pos_.z += it_blt_hell_blt->_moveDirection.z * delta_time * 100;
		}

		if (it_blt_hell_blt->color == EnemyBullet::COLOR::White && it_blt_hell_blt->_movementsType == "Cylinder.Round") {


			it_blt_hell_blt->_angle = (2.0f * tnl::PI / 8) * it_blt_hell_blt->_id;

			double dx = _bossMesh_ref->pos_.x - it_blt_hell_blt->_mesh->pos_.x;
			double dy = _bossMesh_ref->pos_.y - it_blt_hell_blt->_mesh->pos_.y;
			double dz = _bossMesh_ref->pos_.z - it_blt_hell_blt->_mesh->pos_.z;

			float radius = sqrt(dx * dx + dy * dy + dz * dz);

			// ¶‰ñ“]
			if (it_blt_hell_blt->_id % 2 == 0) {
				it_blt_hell_blt->_angle += delta_time;

			}
			// ‰E‰ñ“]
			else {

				it_blt_hell_blt->_angle -= delta_time;
			}

			it_blt_hell_blt->_moveDirection.x = /*_bossMesh_ref->pos_.x +*/ cos(it_blt_hell_blt->_angle) * radius;
			it_blt_hell_blt->_moveDirection.z = /*_bossMesh_ref->pos_.z +*/ sin(it_blt_hell_blt->_angle) * radius;

			it_blt_hell_blt->_moveDirection.normalize();

			it_blt_hell_blt->_mesh->pos_.x += it_blt_hell_blt->_moveDirection.x * delta_time * 100;
			it_blt_hell_blt->_mesh->pos_.z += it_blt_hell_blt->_moveDirection.z * delta_time * 100;
		}



		// ‘S•ûˆÊ
		if (it_blt_hell_blt->color == EnemyBullet::COLOR::EmeraldGreen && it_blt_hell_blt->_movementsType == "Sphere.Straight") {


			if (it_blt_hell_blt->_id < 24) {

				it_blt_hell_blt->_angle = (2.0f * tnl::PI / 8) * it_blt_hell_blt->_id;

				double dx = _bossMesh_ref->pos_.x - it_blt_hell_blt->_mesh->pos_.x;
				double dy = _bossMesh_ref->pos_.y - it_blt_hell_blt->_mesh->pos_.y;
				double dz = _bossMesh_ref->pos_.z - it_blt_hell_blt->_mesh->pos_.z;

				float radius = sqrt(dx * dx + dy * dy + dz * dz);

				it_blt_hell_blt->_moveDirection.x = _bossMesh_ref->pos_.x + cos(it_blt_hell_blt->_angle) * radius;
				it_blt_hell_blt->_moveDirection.z = _bossMesh_ref->pos_.z + sin(it_blt_hell_blt->_angle) * radius;

				it_blt_hell_blt->_moveDirection.normalize();

				it_blt_hell_blt->_mesh->pos_.x += it_blt_hell_blt->_moveDirection.x * delta_time * 100;
				it_blt_hell_blt->_mesh->pos_.z += it_blt_hell_blt->_moveDirection.z * delta_time * 100;
			}
			else if (it_blt_hell_blt->_id > 24 && it_blt_hell_blt->_id < 48) {

				it_blt_hell_blt->_angle = (2.0f * tnl::PI / 8) * it_blt_hell_blt->_id;

				double dx = _bossMesh_ref->pos_.x - it_blt_hell_blt->_mesh->pos_.x;
				double dy = _bossMesh_ref->pos_.y - it_blt_hell_blt->_mesh->pos_.y;
				double dz = _bossMesh_ref->pos_.z - it_blt_hell_blt->_mesh->pos_.z;

				float radius = sqrt(dx * dx + dy * dy + dz * dz);

				it_blt_hell_blt->_moveDirection.x = _bossMesh_ref->pos_.x + cos(it_blt_hell_blt->_angle) * radius;
				it_blt_hell_blt->_moveDirection.z = _bossMesh_ref->pos_.z + sin(it_blt_hell_blt->_angle) * radius;

				it_blt_hell_blt->_moveDirection.normalize();

				it_blt_hell_blt->_mesh->pos_.x += it_blt_hell_blt->_moveDirection.x * delta_time * 100;
				it_blt_hell_blt->_mesh->pos_.z += it_blt_hell_blt->_moveDirection.z * delta_time * 100;

			}
			else if (it_blt_hell_blt->_id > 48 && it_blt_hell_blt->_id < 72) {

				it_blt_hell_blt->_angle = (2.0f * tnl::PI / 8) * it_blt_hell_blt->_id;

				double dx = _bossMesh_ref->pos_.x - it_blt_hell_blt->_mesh->pos_.x;
				double dy = _bossMesh_ref->pos_.y - it_blt_hell_blt->_mesh->pos_.y;
				double dz = _bossMesh_ref->pos_.z - it_blt_hell_blt->_mesh->pos_.z;

				float radius = sqrt(dx * dx + dy * dy + dz * dz);

				it_blt_hell_blt->_moveDirection.x = _bossMesh_ref->pos_.x + cos(it_blt_hell_blt->_angle) * radius;
				it_blt_hell_blt->_moveDirection.z = _bossMesh_ref->pos_.z + sin(it_blt_hell_blt->_angle) * radius;

				it_blt_hell_blt->_moveDirection.normalize();

				it_blt_hell_blt->_mesh->pos_.x += it_blt_hell_blt->_moveDirection.x * delta_time * 100;
				it_blt_hell_blt->_mesh->pos_.z += it_blt_hell_blt->_moveDirection.z * delta_time * 100;

			}
			else {
				it_blt_hell_blt->_angle = (2.0f * tnl::PI / 8) * it_blt_hell_blt->_id;

				double dx = _bossMesh_ref->pos_.x - it_blt_hell_blt->_mesh->pos_.x;
				double dy = _bossMesh_ref->pos_.y - it_blt_hell_blt->_mesh->pos_.y;
				double dz = _bossMesh_ref->pos_.z - it_blt_hell_blt->_mesh->pos_.z;

				float radius = sqrt(dx * dx + dy * dy + dz * dz);

				it_blt_hell_blt->_moveDirection.x = _bossMesh_ref->pos_.x + cos(it_blt_hell_blt->_angle) * radius;
				it_blt_hell_blt->_moveDirection.z = _bossMesh_ref->pos_.z + sin(it_blt_hell_blt->_angle) * radius;

				it_blt_hell_blt->_moveDirection.normalize();

				it_blt_hell_blt->_mesh->pos_.x += it_blt_hell_blt->_moveDirection.x * delta_time * 100;
				it_blt_hell_blt->_mesh->pos_.z += it_blt_hell_blt->_moveDirection.z * delta_time * 100;

			}
		}


		CheckLifeTimeDistance(it_blt_hell_blt);
	}
}




void BulletHell::ShotBulletHell_MetalFatigue_Patchouli(const float& delta_time) {

	for (auto& bullet : ScenePlay::_bullet_metalFatigue_patchouli) {
		int id = bullet->_id;

		ScenePlay::_BLTINFO_T_METALFATIGUE_PATCHOULI[id].moveDirection = bullet->_moveDirection;
	}



	for (auto it_blt_hell_blt : ScenePlay::_bullet_metalFatigue_patchouli) {


		if (it_blt_hell_blt->color == EnemyBullet::COLOR::Yellow) {

			tnl::Vector3 bullet_move_orbit_origin;
			float theta = (2.f * tnl::PI / 8) * it_blt_hell_blt->_id;

			if (it_blt_hell_blt->_movementsType == "Sphere.Round.Origin") {



				bullet_move_orbit_origin.y = _bossMesh_ref->pos_.y + cos(theta) * delta_time;
				bullet_move_orbit_origin.z = _bossMesh_ref->pos_.z + sin(theta) * delta_time;

				if (bullet_move_orbit_origin.y > it_blt_hell_blt->_radius) {
					bullet_move_orbit_origin.y = it_blt_hell_blt->_radius;
				}
				if (bullet_move_orbit_origin.z > it_blt_hell_blt->_radius) {
					bullet_move_orbit_origin.z = it_blt_hell_blt->_radius;
				}

				it_blt_hell_blt->_mesh->pos_ += bullet_move_orbit_origin * delta_time * 200;
			}

			if (it_blt_hell_blt->_movementsType == "Sphere.Round.Wave1") {

				tnl::Vector3 bullet_move_orbit_wave1;

				bullet_move_orbit_wave1.y = cos(theta) * delta_time;
				bullet_move_orbit_wave1.z = sin(theta) * delta_time;

				if (bullet_move_orbit_wave1.y > it_blt_hell_blt->_radius) {
					bullet_move_orbit_wave1.y = it_blt_hell_blt->_radius;
				}
				if (bullet_move_orbit_wave1.z > it_blt_hell_blt->_radius) {
					bullet_move_orbit_wave1.z = it_blt_hell_blt->_radius;
				}

				it_blt_hell_blt->_mesh->pos_ += bullet_move_orbit_wave1 * delta_time * 200;

			}

			if (it_blt_hell_blt->_movementsType == "Sphere.Round.Wave2") {

				tnl::Vector3 bullet_move_orbit_wave2;

				bullet_move_orbit_wave2.y = cos(theta) * delta_time;
				bullet_move_orbit_wave2.z = sin(theta) * delta_time;

				if (bullet_move_orbit_wave2.y > it_blt_hell_blt->_radius) {
					bullet_move_orbit_wave2.y = it_blt_hell_blt->_radius;
				}
				if (bullet_move_orbit_wave2.z > it_blt_hell_blt->_radius) {
					bullet_move_orbit_wave2.z = it_blt_hell_blt->_radius;
				}

				it_blt_hell_blt->_mesh->pos_ += bullet_move_orbit_wave2 * delta_time * 200;

			}

			if (it_blt_hell_blt->_movementsType == "Sphere.Round.Wave3") {

				tnl::Vector3 bullet_move_orbit_wave3;

				bullet_move_orbit_wave3.y = cos(theta) * delta_time;
				bullet_move_orbit_wave3.z = sin(theta) * delta_time;

				if (bullet_move_orbit_wave3.y > it_blt_hell_blt->_radius) {
					bullet_move_orbit_wave3.y = it_blt_hell_blt->_radius;
				}	
				if (bullet_move_orbit_wave3.z > it_blt_hell_blt->_radius) {
					bullet_move_orbit_wave3.z = it_blt_hell_blt->_radius;
				}

				it_blt_hell_blt->_mesh->pos_ += bullet_move_orbit_wave3 * delta_time * 200;

			}
		}

		CheckLifeTimeDistance(it_blt_hell_blt);

	}

}


void BulletHell::ShotBulletHell_SilentSerena_Patchouli(const float& delta_time) {


	for (auto& bullet : ScenePlay::_bullet_silentSerena_patchouli) {
		int id = bullet->_id;

		ScenePlay::_BLTINFO_T_SILENTSERENA_PATCHOULI[id].moveDirection = bullet->_moveDirection;
	}


	int i = 0;

	for (auto it_blt_hell_blt : ScenePlay::_bullet_silentSerena_patchouli) {

		//_bltHellsBlt_map[i] = it_blt_hell_blt;

		if (it_blt_hell_blt->color == EnemyBullet::COLOR::EmeraldGreen) {


			//if (_bltHellFactory->ReuseBulletHellsBullet_SilentSerena(_bltHellsBlt_map, it_blt_hell_blt->_id) != nullptr) {
			//	_bltHellsBlt_map[i] = _bltHellFactory->ReuseBulletHellsBullet_SilentSerena(_bltHellsBlt_map, it_blt_hell_blt->_id);
			//}

			float theta = i * (2.f * tnl::PI / ScenePlay::_bullet_silentSerena_patchouli.size());
			float pi = tnl::PI / 1.001f;

			tnl::Vector3 bullet_spawn_pos;

			bullet_spawn_pos.x = _bossMesh_ref->pos_.x + cos(theta) * sin(pi);
			bullet_spawn_pos.y = _bossMesh_ref->pos_.y;
			bullet_spawn_pos.z = _bossMesh_ref->pos_.z + sin(theta) * sin(pi);

			tnl::Vector3 move_dir = bullet_spawn_pos.Normalize(bullet_spawn_pos);

			it_blt_hell_blt->_mesh->pos_ += move_dir * delta_time * 200;
		}
		else if (it_blt_hell_blt->color == EnemyBullet::COLOR::Blue) {

			//if (_bltHellFactory->ReuseBulletHellsBullet_SilentSerena(_bltHellsBlt_map, it_blt_hell_blt->_id) != nullptr) {
			//	_bltHellsBlt_map[i] = _bltHellFactory->ReuseBulletHellsBullet_SilentSerena(_bltHellsBlt_map, it_blt_hell_blt->_id);
			//}

			float theta = i * (tnl::PI / ScenePlay::_bullet_silentSerena_patchouli.size());
			float pi = tnl::PI;

			tnl::Vector3 bullet_spawn_pos;

			bullet_spawn_pos.x = _bossMesh_ref->pos_.x + cos(theta) * sin(pi);
			bullet_spawn_pos.y = _bossMesh_ref->pos_.y;
			bullet_spawn_pos.z = _bossMesh_ref->pos_.z + sin(theta) * sin(pi);

			tnl::Vector3 move_dir = tnl::Vector3::TransformCoord({ 0,0,1 }, _bossMesh_ref->rot_);

			it_blt_hell_blt->_mesh->pos_ += move_dir * delta_time * 150;
		}

		CheckLifeTimeDistance(it_blt_hell_blt);
		i++;
	}
}



void BulletHell::CheckLifeTimeDistance(Shared<EnemyBullet>& it_bltHell)
{
	static tnl::Vector3 start = it_bltHell->_mesh->pos_;

	float dx = it_bltHell->_mesh->pos_.x - start.x;
	float dy = it_bltHell->_mesh->pos_.y - start.y;
	float dz = it_bltHell->_mesh->pos_.z - start.z;

	float current_distance = sqrt(dx * dx + dy * dy + dz * dz);

	if (abs(current_distance) > 500) it_bltHell->_isActive = false;
}



void BulletHell::ShotBulletHell_PerfectFreeze(const float& delta_time) {

	//_bulletHell_bullets = _bltHellFactory->CreateBulletHell(BulletHell::TYPE::Perfect_Freeze);
}


void BulletHell::ShotBulletHell_KeroChanStandsFirm_AgainstTheStorm(const float& delta_time) {

	//_bulletHell_bullets = _bltHellFactory->CreateBulletHell(BulletHell::TYPE::KeroChan_StandsFirm_AgainstTheStorm);
}



void BulletHell::RemoveBullet(Shared<EnemyBullet> bullet) {


}



void BulletHell::Clear() {
	//_bulletHell_bullets.clear();
}