#include "EnemyZakoDome.h"
#include "../../../Bullet/Enemy/EnemyBullet.h"
#include "../../../Bullet/Enemy/StraightBullet.h"
#include "../../../Bullet/Enemy/HomingBullet.h"
#include "../../../EnemyMove/EnemyMover.h"


std::list<Shared<StraightBullet>> EnemyZakoDome::_straight_bullets_zakoDome;
std::list<Shared<HomingBullet>> EnemyZakoDome::_homing_bullets_zakoDome;


EnemyZakoDome::EnemyZakoDome(const EnemyZakoInfo& data, const Shared<Player>& player, const Shared<dxe::Camera>& camera)
	: EnemyBase(data, player, camera), straight_bullet_count(0), homing_bullet_count(0)
{
	collide_size = { 30,30,30 };
}



void EnemyZakoDome::SetMeshInfo() {

	_mesh = dxe::Mesh::CreateDomeMV(10);

	_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/box.bmp"));
	_mesh->pos_ = GetRandomPosition_Mt19337();
	_mesh->scl_ = { 1.0f, 1.0f, 1.0f };
}



tnl::Vector3 EnemyZakoDome::CalcVecFromAngle(float angle) {

	tnl::Vector3 temp;

	temp.x = sin(angle);
	temp.y = -cos(angle);

	return temp;
}



float EnemyZakoDome::GetAngleBtw_EnemyAndPlayer(Shared<dxe::Mesh> enemy, Shared<Player> player) {

	//　外積・内積は２つのベクトルの相対角度とは関係がないので使わない

	float dx = player->_mesh->pos_.x - enemy->pos_.x;
	float dy = player->_mesh->pos_.y - enemy->pos_.y;

	// プレイヤーとエネミーの位置の相対角度を求める
	float angle = atan2(dy, dx);

	return angle;
}



void EnemyZakoDome::DoRoutineMoves(float delta_time) {

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




void EnemyZakoDome::ChasePlayer(const float delta_time) {

	//プレイヤー追跡
	tnl::Vector3 direction = _player_ref->GetPos() - _mesh->pos_;

	direction.Normalize(direction);

	_mesh->pos_ += (direction * delta_time * _charaMoveSpeed);
}



void EnemyZakoDome::AttackPlayer(const float& delta_time) {

	int randValue = rand() % 2;

	switch (randValue)
	{
	case 0:
	{
		InitStraightBullet();
		UpdateStraightBullet(delta_time);
		break;
	}
	case 1:
		InitHomingBullet();
		UpdateHomingBullet(delta_time);
		break;
	}
}



void EnemyZakoDome::InitStraightBullet() {



	straight_bullet_count++;

	for (int i = 0; i < INIT_BULLET_NUM; i++) {

		if (straight_bullet_count % 30 != 0 && straight_bullet_count <= 180) continue;

		// 発射位置を自分の正面に設定
		tnl::Vector3 move_dir = tnl::Vector3::TransformCoord({ 0,0,1 }, _mesh->rot_);

		tnl::Vector3 spawn_pos = _mesh->pos_;
		spawn_pos.x += _mesh->rot_.x;
		spawn_pos.y += _mesh->rot_.y;
		spawn_pos.z += _mesh->rot_.z;
		spawn_pos.z -= 30;

		spawn_pos += move_dir * 20;

		_straight_bullets_zakoDome.emplace_back(std::make_shared<StraightBullet>(spawn_pos, move_dir, _player_ref, BULLET_SPEED));

		straight_bullet_count = 0;
		break;

	}
}



void EnemyZakoDome::UpdateStraightBullet(const float delta_time) {

	auto it = _straight_bullets_zakoDome.begin();

	while (it != _straight_bullets_zakoDome.end()) {

		(*it)->Update(delta_time);

		if (!(*it)->_isActive) {
			it = _straight_bullets_zakoDome.erase(it);
			continue;
		}
		it++;
	}

	if (_straight_bullets_zakoDome.empty()) InitStraightBullet();
}




void EnemyZakoDome::InitHomingBullet() {


	homing_bullet_count++;

	for (int i = 0; i < INIT_BULLET_NUM; i++) {

		if (homing_bullet_count % 30 != 0 && homing_bullet_count <= 180) continue;

		// 発射位置を自分の正面に設定
		tnl::Vector3 move_dir = tnl::Vector3::TransformCoord({ 0,0,1 }, _mesh->rot_);

		tnl::Vector3 spawn_pos = _mesh->pos_;
		spawn_pos.x += _mesh->rot_.x;
		spawn_pos.y += _mesh->rot_.y;
		spawn_pos.z += _mesh->rot_.z;
		spawn_pos.z -= 30;

		spawn_pos += move_dir * 20;

		_homing_bullets_zakoDome.emplace_back(std::make_shared<HomingBullet>(spawn_pos, move_dir, _player_ref, BULLET_SPEED));

		homing_bullet_count = 0;
		break;

	}
}



void EnemyZakoDome::UpdateHomingBullet(const float delta_time) {

	auto it = _homing_bullets_zakoDome.begin();

	while (it != _homing_bullets_zakoDome.end()) {

		(*it)->Update(delta_time);

		if (!(*it)->_isActive) {
			it = _homing_bullets_zakoDome.erase(it);
			continue;
		}
		it++;
	}

	if (_homing_bullets_zakoDome.empty()) InitHomingBullet();
}




bool EnemyZakoDome::Update(float delta_time) {

	if (_isDead) return false;

	DoRoutineMoves(delta_time);

	return true;
}



void EnemyZakoDome::Render(Shared<dxe::Camera> camera) {

	if (_isDead) return;

	_mesh->render(camera);

	ShowHpGage_EnemyZako();

	for (auto blt : _straight_bullets_zakoDome) {
		blt->Render(camera);
	}

	for (auto blt : _homing_bullets_zakoDome) {
		blt->Render(camera);
	}
}