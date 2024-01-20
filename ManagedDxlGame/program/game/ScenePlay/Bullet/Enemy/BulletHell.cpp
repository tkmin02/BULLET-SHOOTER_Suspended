#include "BulletHell.h"
#include "BulletHellFactory.h"
#include "EnemyBullet.h"


BulletHell::BulletHell(const Shared<dxe::Mesh>& bossMesh, std::list<Shared<EnemyBullet>> bossBullet)
	: _bossMesh_ref(bossMesh), _bulletHell_bullets(bossBullet) {

	_bltHellFactory = std::make_shared<BulletHellFactory>();
}



void BulletHell::AddBullet(const Shared<EnemyBullet>& bullet) {

	_bulletHell_bullets.push_back(bullet);
}



void BulletHell::ShotBulletHell_SilentSerena(const float& delta_time) {

	if (_bulletHell_bullets.size() <= 0)
		_bulletHell_bullets = _bltHellFactory->CreateBulletHell(BulletHell::TYPE::Silent_Serena);


	int i = 0;

	for (auto& it_blt_h_blt : _bulletHell_bullets) {

		_bltHellFactory->ReuseBulletHellsBullet_SilentSerena(_bltHellsBlt_map, it_blt_h_blt->_id);

		if (it_blt_h_blt->color == EnemyBullet::COLOR::EmeraldGreen) {

			float theta = i * (2.f * tnl::PI / _bulletHell_bullets.size());
			float pi = tnl::PI / 1.001f;

			tnl::Vector3 bullet_spawn_pos;

			bullet_spawn_pos.x = _bossMesh_ref->pos_.x + cos(theta) * sin(pi);
			bullet_spawn_pos.y = _bossMesh_ref->pos_.y ;
			bullet_spawn_pos.z = _bossMesh_ref->pos_.z + sin(theta) * sin(pi);

			tnl::Vector3 move_dir = bullet_spawn_pos.Normalize(bullet_spawn_pos);

			it_blt_h_blt->_mesh->pos_ += move_dir * delta_time * 50;
		}
		else if (it_blt_h_blt->color == EnemyBullet::COLOR::Blue) {

			_bltHellFactory->ReuseBulletHellsBullet_SilentSerena(_bltHellsBlt_map, it_blt_h_blt->_id);

			float theta = i * (tnl::PI / _bulletHell_bullets.size());
			float pi = tnl::PI ;

			tnl::Vector3 bullet_spawn_pos;

			bullet_spawn_pos.x = _bossMesh_ref->pos_.x + cos(theta) * sin(pi);
			bullet_spawn_pos.y = _bossMesh_ref->pos_.y;
			bullet_spawn_pos.z = _bossMesh_ref->pos_.z + sin(theta) * sin(pi);

			tnl::Vector3 move_dir = tnl::Vector3::TransformCoord({ 0,0,1 }, _bossMesh_ref->rot_);

			it_blt_h_blt->_mesh->pos_ += move_dir * delta_time * 30;
		}

		CheckLifeTimeDistance(it_blt_h_blt);
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

	if (abs(current_distance) > 100) it_bltHell->_isActive = false;
}



void BulletHell::ShotBulletHell_PerfectFreeze(const float& delta_time) {

	_bulletHell_bullets = _bltHellFactory->CreateBulletHell(BulletHell::TYPE::Perfect_Freeze);
}


void BulletHell::ShotBulletHell_KeroChanStandsFirm_AgainstTheStorm(const float& delta_time) {

	_bulletHell_bullets = _bltHellFactory->CreateBulletHell(BulletHell::TYPE::KeroChan_StandsFirm_AgainstTheStorm);
}



void BulletHell::RemoveBullet(Shared<EnemyBullet> bullet) {


}


void BulletHell::Clear() {
	_bulletHell_bullets.clear();
}




void BulletHell::Render(Shared<dxe::Camera> _mainCamera) {

	for (auto blt : _bulletHell_bullets) {
		blt->Render(_mainCamera);
	}
}



void BulletHell::Update(float delta_time) {

	auto it = _bulletHell_bullets.begin();

	while (it != _bulletHell_bullets.end())
	{
		(*it)->Update(delta_time);

		if (!(*it)->_isActive) {
			//it = _bulletHell_bullets.erase(it);
			//continue;
		}
		it++;
	}
}