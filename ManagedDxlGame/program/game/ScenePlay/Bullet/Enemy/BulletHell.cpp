#include "BulletHell.h"
#include "BulletHellFactory.h"



BulletHell::BulletHell(const Shared<dxe::Mesh>& bossMesh, std::list<Shared<EnemyBullet>> bossBullet) 
	: _bossMesh_ref(bossMesh),_bulletHell_bullets(bossBullet) {

	_bltHellFactory = std::make_shared<BulletHellFactory>();
}



void BulletHell::AddBullet(const Shared<EnemyBullet>& bullet) {

	_bulletHell_bullets.push_back(bullet);
}


void BulletHell::ShotBulletHell_SilentSerena() {

	/*Shared<BulletHell> b =*/ _bltHellFactory->CreateBulletHell(BulletHell::TYPE::Silent_Serena, _bossMesh_ref);
}


void BulletHell::ShotBulletHell_PerfectFreeze() {

	/*Shared<BulletHell> b =*/ _bltHellFactory->CreateBulletHell(BulletHell::TYPE::Perfect_Freeze, _bossMesh_ref);
}


void BulletHell::ShotBulletHell_KeroChanStandsFirm_AgainstTheStorm() {

	/*Shared<BulletHell> b =*/ _bltHellFactory->CreateBulletHell(BulletHell::TYPE::KeroChan_StandsFirm_AgainstTheStorm, _bossMesh_ref);
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
		if (!(*it)->_isActive) {
			(*it)->_isActive = true;
			(*it)->Update(delta_time);
		}
		it++;
	}
}