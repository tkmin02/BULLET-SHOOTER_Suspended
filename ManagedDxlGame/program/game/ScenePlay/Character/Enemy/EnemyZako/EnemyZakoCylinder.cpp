#include "EnemyZakoCylinder.h"
#include "../../../Bullet/Enemy/EnemyBullet.h"
#include "../../../Bullet/Enemy/StraightBullet.h"
#include "../../../Bullet/Enemy/HomingBullet.h"
#include "../../../EnemyMove/EnemyMover.h"
#include "../../../Bullet/Enemy/BulletFactory.h"

std::list<Shared<StraightBullet>> EnemyZakoCylinder::_straight_bullets_zakoCylinder;
std::list<Shared<HomingBullet>> EnemyZakoCylinder::_homing_bullets_zakoCylinder;


EnemyZakoCylinder::EnemyZakoCylinder(const EnemyZakoInfo& data, const Shared<Player>& player, const Shared<dxe::Camera>& camera)
	: EnemyBase(data, player, camera), straight_bullet_count(0), homing_bullet_count(0)
{
	_explode_particle = std::make_shared<dxe::Particle>("particle/preset/explosion.bin");

	collide_size = { 30,30,30 };
}



void EnemyZakoCylinder::SetMeshInfo() {

	_mesh = dxe::Mesh::CreateCylinderMV(20, 20);
	_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/box.bmp"));
	_mesh->pos_ = GetRandomPosition_Mt19337();
	_mesh->scl_ = { 1.0f, 1.0f, 1.0f };
}



void EnemyZakoCylinder::InitBulletFactoryInstance() {
	_bulletFactory = std::make_shared<BulletFactory>(_mesh);

	std::list<Shared<StraightBullet>> bullets = _bulletFactory->CreateStraightBullet(StraightBullet::USER::ZakoBox, _maxBulletSpawnCount);
	for (const auto& bullet : bullets) {
		_straightBullet_queue.push_back(bullet);
	}

}




void EnemyZakoCylinder::DoRoutineMoves(float delta_time) {

	LookAtPlayer();

	// 距離 250～270内でプレイヤー追跡
	if (GetDistanceToPlayer() < _IDLE_DISTANCE && GetDistanceToPlayer() > _ATTACK_DISTANCE) {

		ChasePlayer(delta_time);
	}
	// 250以内で攻撃
	else if (GetDistanceToPlayer() < _ATTACK_DISTANCE) {

		AttackPlayer(delta_time);
		_canShotStraightBullet = false;

	}
	// アイドル状態
	else {

		_mover->forward;

	}

	prev_pos = _mesh->pos_;

}



void EnemyZakoCylinder::ChasePlayer(const float delta_time) {

	//プレイヤー追跡
	tnl::Vector3 direction = _player_ref->GetPos() - _mesh->pos_;

	direction.Normalize(direction);

	_mesh->pos_ += (direction * delta_time * _charaMoveSpeed);
}




void EnemyZakoCylinder::AttackPlayer(const float& delta_time) {

	int randValue = rand() % 2;

	switch (randValue)
	{
	case 0:
	{
		ShotStraightBullet(delta_time);

		break;
	}
	case 1:
	{

	}
	}

}


void EnemyZakoCylinder::ShotStraightBullet(const float& delta_time) {
	static float reload_time_counter = 0.0f;  // リロード時間を追跡する変数

	straight_bullet_count++;



	// 撃った弾の間隔を空けるための処理
	if (straight_bullet_count % _bulletFireInterval == 0 && !_straightBullet_queue.empty()) {

		_straight_bullets_zakoCylinder.push_back(_straightBullet_queue.front());
		_straightBullet_queue.pop_front();
		straight_bullet_count = 0;
	}



	auto it = _straight_bullets_zakoCylinder.begin();

	while (it != _straight_bullets_zakoCylinder.end()) {

		if ((*it)->_isActive) {
			tnl::Vector3 move_dir = tnl::Vector3::TransformCoord({ 0,0,1 }, _mesh->rot_);

			(*it)->_mesh->pos_ += move_dir * delta_time * _bulletMoveSpeed;

			(*it)->CheckLifeTimeDistance(*it);

		}

		else if (!(*it)->_isActive) {
			it = _straight_bullets_zakoCylinder.erase(it);
			continue;
		}
		it++;

	}

	ReloadStraightBulletByTimer(reload_time_counter, delta_time);
}

void EnemyZakoCylinder::ReloadStraightBulletByTimer(float& reload_time_counter, const float& delta_time) {
	if (_straightBullet_queue.empty()) {

		reload_time_counter += delta_time;

		if (reload_time_counter >= _reloadTimeInterval) {
			std::list<Shared<StraightBullet>> bullets = _bulletFactory->CreateStraightBullet(StraightBullet::USER::ZakoBox, _maxBulletSpawnCount);
			for (const auto& bullet : bullets) {
				_straightBullet_queue.push_back(bullet);
			}
			reload_time_counter = 0.0f;
		}
	}
}

void EnemyZakoCylinder::EraseInvalidStraightBullet() {
	auto it = _straight_bullets_zakoCylinder.begin();

	while (it != _straight_bullets_zakoCylinder.end()) {

		if (!(*it)->_isActive) {
			it = _straight_bullets_zakoCylinder.erase(it);
			continue;
		}
		it++;
	}

}

void EnemyZakoCylinder::ShotHomingBullet(const float& delta_time) {

}





bool EnemyZakoCylinder::Update(float delta_time) {

	if (_isDead) return false;

	DoRoutineMoves(delta_time);

	return true;
}



void EnemyZakoCylinder::Render(Shared<dxe::Camera> camera) {

	if (_isDead) return;

	_mesh->render(camera);

	ShowHpGage_EnemyZako();

	for (auto blt : _straight_bullets_zakoCylinder) {
		blt->Render(camera);
	}

	//for (auto blt : _homing_bullets_zakoCylinder) {
	//	blt->Render(camera);
	//}
}