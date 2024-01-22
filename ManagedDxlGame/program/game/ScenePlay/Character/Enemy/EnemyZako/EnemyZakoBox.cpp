#include "EnemyZakoBox.h"
#include "../../../Bullet/Enemy/EnemyBullet.h"
#include "../../../Bullet/Enemy/StraightBullet.h"
#include "../../../Bullet/Enemy/HomingBullet.h"
#include "../../../EnemyMove/EnemyMover.h"
#include "../../../Bullet/Enemy/BulletFactory.h"


std::list<Shared<StraightBullet>> EnemyZakoBox::_straight_bullets_zakoBox;
std::list<Shared<HomingBullet>> EnemyZakoBox::_homing_bullets_zakoBox;



EnemyZakoBox::EnemyZakoBox(const EnemyZakoInfo& data, const Shared<Player>& player, const Shared<dxe::Camera>& camera)
	: EnemyBase(data, player, camera), straight_bullet_count(0), homing_bullet_count(0)
{

	_explode_particle = std::make_shared<dxe::Particle>("particle/preset/explosion.bin");

	collide_size = { 30,30,30 };
}



void EnemyZakoBox::SetMeshInfo() {

	tnl::Vector3 meshSize = { 20,20,20 };
	_mesh = dxe::Mesh::CreateBoxMV(meshSize,
		dxe::Texture::CreateFromFile("graphics/colorTexture/red.bmp"),
		dxe::Texture::CreateFromFile("graphics/colorTexture/red.bmp"),
		dxe::Texture::CreateFromFile("graphics/colorTexture/red.bmp"),
		dxe::Texture::CreateFromFile("graphics/colorTexture/red.bmp"),
		dxe::Texture::CreateFromFile("graphics/colorTexture/red.bmp"),
		dxe::Texture::CreateFromFile("graphics/colorTexture/red.bmp"));

	_mesh->pos_ = GetRandomPosition_Mt19337();
	_mesh->scl_ = { 1.0f, 1.0f, 1.0f };
}



void  EnemyZakoBox::InitBulletFactoryInstance() {

	_bulletFactory = std::make_shared<BulletFactory>(_mesh);
}



void EnemyZakoBox::DoRoutineMoves(float delta_time) {

	LookAtPlayer();

	// 距離 250～270内でプレイヤー追跡
	if (GetDistanceToPlayer() < _IDLE_DISTANCE && GetDistanceToPlayer() > _ATTACK_DISTANCE) {

		ChasePlayer(delta_time);
	}
	// 250以内で攻撃
	else if (GetDistanceToPlayer() < _ATTACK_DISTANCE) {

		AttackPlayer(delta_time);

	}
	// アイドル状態
	else {

		_mover->forward;

	}

	prev_pos = _mesh->pos_;

}



void EnemyZakoBox::ChasePlayer(const float delta_time) {

	//プレイヤー追跡
	tnl::Vector3 direction = _player_ref->GetPos() - _mesh->pos_;

	direction.Normalize(direction);

	_mesh->pos_ += (direction * delta_time * _charaMoveSpeed);
}



void EnemyZakoBox::AttackPlayer(const float& delta_time) {


	int randValue = rand() % 2;

	switch (randValue)
	{
	case 0:
	{
		ShotStraightBullet(delta_time);
		EraseInvalidBullet();

		break;
	}
	case 1:
	{
		//	homing_bullet_count++;

		//	if (!_canShotHomingBullet) _canShotHomingBullet = true;

		//	if (_canShotHomingBullet) {

		//		for (int i = 0; i < INIT_BULLET_NUM; i++) {

		//			InitHomingBullet();
		//		}
		//		UpdateHomingBullet(delta_time);
		//	}
		//	break;
		//}
	}
	}

}




void EnemyZakoBox::ShotStraightBullet(const float& delta_time) {

	straight_bullet_count++;


	if (straight_bullet_count % 50 == 0) {

		_straight_bullets_zakoBox = _bulletFactory->CreateStraightBullet(StraightBullet::USER::ZakoBox);
		straight_bullet_count = 0;
	}

	for (auto it_straight_bullet : _straight_bullets_zakoBox) {

		if (it_straight_bullet->_isActive) {
			tnl::Vector3 move_dir = tnl::Vector3::TransformCoord({ 0,0,1 }, _mesh->rot_);
			it_straight_bullet->_mesh->pos_ += move_dir * delta_time * 500;

			it_straight_bullet->CheckLifeTimeDistance(it_straight_bullet);
		}
	}
}



void EnemyZakoBox::EraseInvalidBullet() {

	auto it = _straight_bullets_zakoBox.begin();

	while (it != _straight_bullets_zakoBox.end()) {

		if (!(*it)->_isActive) {
			it = _straight_bullets_zakoBox.erase(it);
			continue;
		}
		it++;
	}
}



void EnemyZakoBox::InitHomingBullet() {

	for (int i = 0; i < 5; i++) {

		if (homing_bullet_count % 20 != 0) continue;

		// 発射位置を自分の正面に設定
		tnl::Vector3 move_dir = tnl::Vector3::TransformCoord({ 0,0,1 }, _mesh->rot_);

		tnl::Vector3 spawn_pos = _mesh->pos_;
		spawn_pos.x += _mesh->rot_.x;
		spawn_pos.y += _mesh->rot_.y;
		spawn_pos.z += _mesh->rot_.z;
		spawn_pos.z -= 30;

		spawn_pos += move_dir * 20;

		_homing_bullets_zakoBox.emplace_back(std::make_shared<HomingBullet>(spawn_pos, move_dir, _player_ref, BULLET_SPEED));

		homing_bullet_count = 0;
		break;
	}
}



void EnemyZakoBox::UpdateHomingBullet(const float delta_time) {

	auto it = _homing_bullets_zakoBox.begin();

	while (it != _homing_bullets_zakoBox.end()) {

		(*it)->Update(delta_time);

		if (!(*it)->_isActive) {
			it = _homing_bullets_zakoBox.erase(it);
			continue;
		}
		it++;
	}

	if (_homing_bullets_zakoBox.empty()) InitHomingBullet();
}




bool EnemyZakoBox::Update(float delta_time) {

	if (_isDead) return false;

	DoRoutineMoves(delta_time);

	return true;
}



void EnemyZakoBox::Render(Shared<dxe::Camera> camera) {

	if (_isDead) return;

	_mesh->render(camera);

	ShowHpGage_EnemyZako();

	for (auto blt : _straight_bullets_zakoBox) {

		// シャドウマップへの描画開始
		//_shadow->reserveBegin();
		//blt->_mesh->reserveShadow();
		//_shadow->reserveEnd();

		//// シャドウマップとブルーム適用開始
		//_shadow->renderBegin();
		//_screen_effect->renderBegin();
		blt->Render(camera);
		// シャドウマップとブルーム適用終了
		//_screen_effect->renderEnd();
		//_shadow->renderEnd();
	}

	for (auto blt : _homing_bullets_zakoBox) {
		blt->_mesh->reserveShadow();

		blt->Render(camera);
	}


}