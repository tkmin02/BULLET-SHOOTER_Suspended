#include "EnemyZakoBox.h"
#include "../../Bullet/Enemy/EnemyBullet.h"
#include "../../Bullet/Enemy/StraightBullet.h"
#include "../../Bullet/Enemy/HomingBullet.h"
#include "../../EnemyMove/EnemyMover.h"
#include <functional>
#include <random>

std::list<Shared<StraightBullet>> EnemyZakoBox::_straight_bullets_e;
std::list<Shared<HomingBullet>> EnemyZakoBox::_homing_bullets_e;


EnemyZakoBox::EnemyZakoBox(const EnemyZakoInfo& data, const Shared<Player>& player, const Shared<dxe::Camera>& camera)
	: EnemyBase(data, player, camera)
{
	collide_size = { 30,30,30 };
}



void EnemyZakoBox::SetMeshInfo() {


	_mesh = dxe::Mesh::CreateBox(20);
	_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/box.bmp"));
	_mesh->pos_ = { 0, 0, 0 };
	_mesh->scl_ = { 1.0f, 1.0f, 1.0f };
}


float EnemyZakoBox::GetRandomValue_Mt19337() const {


	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> rateDistribution(-1.0f, 1.0f);

	return rateDistribution(gen);
}


tnl::Vector3 EnemyZakoBox::CalcVecFromAngle(float angle) {

	tnl::Vector3 temp;

	temp.x = sin(angle);
	temp.y = -cos(angle);

	return temp;
}



float EnemyZakoBox::GetAngleBtw_EnemyAndPlayer(Shared<dxe::Mesh> enemy, Shared<Player> player) {

	//　外積・内積は２つのベクトルの相対角度とは関係がないので使わない

	float dx = player->_mesh->pos_.x - enemy->pos_.x;
	float dy = player->_mesh->pos_.y - enemy->pos_.y;

	// プレイヤーとエネミーの位置の相対角度を求める
	float angle = atan2(dy, dx);

	return angle;
}



void EnemyZakoBox::DoRoutineMoves(float delta_time) {

	LookAtPlayer(delta_time);

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

	_mesh->pos_ += (direction * _charaMoveSpeed * delta_time);
}



void EnemyZakoBox::AttackPlayer(float delta_time) {

	int randValue = rand() % 2;

	switch (randValue)
	{
	case 0:
	{
		//InitStraightBullet();
		//UpdateStraightBullet(delta_time);
		break;
	}
	case 1:
		InitHomingBullet();
		UpdateHomingBullet(delta_time);
		break;
	}
}


int straight_bullet_count = 0;

void EnemyZakoBox::InitStraightBullet() {

	auto now = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - last_shot_time_straight_blt).count();

	// 3秒間隔で弾を発射
	if (elapsed < 3) return;

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

		_straight_bullets_e.emplace_back(std::make_shared<StraightBullet>(spawn_pos, move_dir, _player_ref, BULLET_SPEED));


		straight_bullet_count = 0;
		break;

		last_shot_time_straight_blt = now;
	}
}



void EnemyZakoBox::UpdateStraightBullet(const float delta_time) {

	auto it = _straight_bullets_e.begin();

	while (it != _straight_bullets_e.end()) {

		(*it)->Update(delta_time);

		if (!(*it)->_isActive) {
			it = _straight_bullets_e.erase(it);
			continue;
		}
		it++;
	}

	if (_straight_bullets_e.empty()) InitStraightBullet();
}



int homing_bullet_count = 0;

void EnemyZakoBox::InitHomingBullet() {

	auto now = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - last_shot_time_homing_blt).count();

	// 3秒間隔で弾を発射
	if (elapsed < 3) return;

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

		_homing_bullets_e.emplace_back(std::make_shared<HomingBullet>(spawn_pos, move_dir, _player_ref, BULLET_SPEED));

		homing_bullet_count = 0;
		break;

		last_shot_time_homing_blt = now;
	}
}



void EnemyZakoBox::UpdateHomingBullet(const float delta_time) {

	auto it = _homing_bullets_e.begin();

	while (it != _homing_bullets_e.end()) {

		(*it)->Update(delta_time);

		if (!(*it)->_isActive) {
			it = _homing_bullets_e.erase(it);
			continue;
		}
		it++;
	}

	if (_homing_bullets_e.empty()) InitHomingBullet();
}




void EnemyZakoBox::LookAtPlayer(const float delta_time) {

	//tnl::Vector3 direction = (_player_ref->GetPos() * 40 * delta_time) - _mesh->pos_;
	//float angle = atan2(direction.x, direction.z);
	//_mesh->rot_ = tnl::Quaternion::RotationAxis({ 0,1,0 }, angle);

	tnl::Quaternion q = tnl::Quaternion::RotationAxis({ 0,1,0 }, _mainCamera_ref->axis_y_angle_);
	tnl::Vector3 xz = tnl::Vector3::TransformCoord({ 0,0,1 }, q);
	tnl::Vector3 local_axis_y = tnl::Vector3::Cross({ -1,0,0 }, xz);

	_mesh->rot_ = tnl::Quaternion::LookAt(_mesh->pos_, _player_ref->GetPos(), local_axis_y);
}




void EnemyZakoBox::DebugInfo() {

	DrawFormatString(10, 0, -1, "BoxPos");
	DrawFormatString(10, 15, -1, "%f", _mesh->pos_.x);
	DrawFormatString(10, 35, -1, "%f", _mesh->pos_.y);
	DrawFormatString(10, 55, -1, "%f", _mesh->pos_.z);


	DrawFormatString(10, 80, -1, "BoxRot");
	DrawFormatString(10, 100, -1, "%f", _mesh->rot_.x);
	DrawFormatString(10, 120, -1, "%f", _mesh->rot_.y);
	DrawFormatString(10, 140, -1, "%f", _mesh->rot_.z);
}




bool EnemyZakoBox::Update(float delta_time) {

	if (_isDead) return false;

	DoRoutineMoves(delta_time);

	return true;
}



void EnemyZakoBox::Render(Shared<dxe::Camera> camera) {

	if (_isDead) return;

	_mesh->render(camera);

	for (auto blt : _straight_bullets_e) {
		blt->Render(camera);
	}

	for (auto blt : _homing_bullets_e) {
		blt->Render(camera);
	}

	DebugInfo();
}