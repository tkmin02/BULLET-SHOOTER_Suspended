#include <random>
#include "EnemyBase.h"
#include "../../Bullet/Enemy/StraightBullet.h"
#include "../../../Manager/Score/ScoreManager.h"

// 雑魚エネミーデータ読み取り
EnemyBase::EnemyBase(const EnemyZakoInfo& data, const Shared<Player>& player, const Shared<dxe::Camera>& camera) {


	_id = data._id;
	_name = data._name;
	_hp = data._hp;
	_MAX_HP = data._hp;
	_scale = data._scale;
	_charaMoveSpeed = data._charaMoveSpeed;

	_maxBulletSpawnCount = data._maxBulletSpawnCount;
	_maxTotalEnemySpawnCount = data._maxTotalEnemySpawnCount;

	_player_ref = player;
	_mainCamera_ref = camera;
}



// ボスエネミーデータ読み取り
EnemyBase::EnemyBase(const EnemyBossInfo& data, const Shared<Player>& player, const Shared<dxe::Camera>& camera) {

	_id = data._id;
	_name = data._name;

	for (int i = 0; i < 4; i++) {

		_bossHp.push_back(data._hp);
		_remaining_life_indicator.push(_bossHp);
	}


	_MAX_HP = data._hp;
	_scale = data._scale;
	_charaMoveSpeed = data._charaMoveSpeed;

	_maxBulletSpawnCount = data._maxBulletSpawnCount;

	_player_ref = player;
	_mainCamera_ref = camera;
}



void EnemyBase::Initialize() {

	SetMeshInfo();
}




tnl::Vector3 EnemyBase::GetRandomPosition_Mt19337() const {

	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> distX(-900.0f, 900.0f);
	std::uniform_real_distribution<float> distY(-100.0f, 100.0f);
	std::uniform_real_distribution<float> distZ(-500.0f, 500.0f);

	return tnl::Vector3(distX(gen), distY(gen), distZ(gen));
}


void EnemyBase::InitEnemyMove() {

}





void EnemyBase::DecreaseHP(int damage) {

	_hp -= damage;

	if (_hp <= 0) {
		ScoreManager::GetInstance().AddKillBonus(1000);
		_isDead = true;
	}
}

void EnemyBase::DecreaseBossHP(int damage) {

	if (!_bossHp.empty()) {

		_bossHp.front() -= damage;

		if (_bossHp.front() <= 0) {
			_bossHp.pop_front();
			_remaining_life_indicator.pop();
		}
	}
	else {
		ScoreManager::GetInstance().AddKillBonus(10000);
		_isDead = true;
	}
}


float EnemyBase::GetDistanceToPlayer() {

	tnl::Vector3 dis = _player_ref->GetPos() - _mesh->pos_;

	return std::sqrt(dis.x * dis.x + dis.y * dis.y + dis.z * dis.z);
}



void EnemyBase::LookAtPlayer() {

	tnl::Quaternion q = tnl::Quaternion::RotationAxis({ 0,1,0 }, _mainCamera_ref->axis_y_angle_);
	tnl::Vector3 xz = tnl::Vector3::TransformCoord({ 0,0,1 }, q);
	tnl::Vector3 local_axis_y = tnl::Vector3::Cross({ -1,0,0 }, xz);

	_mesh->rot_ = tnl::Quaternion::LookAt(_mesh->pos_, _player_ref->GetPos(), local_axis_y);
}



bool EnemyBase::ShowHpGage_EnemyZako() {

	if (_hp <= 0) return false;

	tnl::Vector3 hpGage_pos =
		tnl::Vector3::ConvertToScreen(_mesh->pos_, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, _mainCamera_ref->view_, _mainCamera_ref->proj_);

	float x1 = hpGage_pos.x - 30;
	float x2 = hpGage_pos.x + 30;

	float gage_width = abs(x2 - x1);

	float average = (_MAX_HP > 0) ? gage_width / _MAX_HP : 0;

	x2 = x1 + static_cast<int>(average * _hp);

	DrawBoxAA(x1, hpGage_pos.y - 30, x2, hpGage_pos.y - 25, GetColor(255, 0, 0), true);

	return true;
}



bool EnemyBase::ShowHpGage_EnemyBoss() {

	if (!_bossHp.empty()) {

		float x1 = 430, x2 = 860;
		int   y1 = 690, y2 = 710;

		float gage_width = abs(x2 - x1);

		float average = (_MAX_HP > 0) ? gage_width / _MAX_HP : 0;

		x2 = x1 + static_cast<int>(average * _bossHp.front());

		DrawBoxAA(x1, y1, 860, y2, GetColor(255, 255, 255), true);
		DrawBoxAA(x1, y1, x2, y2, GetColor(255, 0, 0), true);

		RenderBossName();
		RenderBossRemainLife();
		return true;
	}
	return false;
}



void EnemyBase::RenderBossRemainLife() {

	for (int i = 0; i < _remaining_life_indicator.size(); i++) {

		DrawOvalAA(600 + (i * 30), 670, 12, 12, 4, GetColor(230, 0, 0), true);
	}
	for (int i = 0; i < 4; i++) {

		DrawOvalAA(600 + (i * 30), 670, 12, 12, 4, GetColor(230, 0, 0), false);
	}
}


void EnemyBase::RenderBossName() {



	//フォントサイズ変更ここから
	SetFontSize(20);
	DrawString(870, 690, _name.c_str(), -1);
}



bool EnemyBase::Update(float delta_time) {


	return true;
}
