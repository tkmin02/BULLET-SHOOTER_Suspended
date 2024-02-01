#include <random>
#include "../../EnemyMove/EnemyMover.h"
#include "../../../Manager/Score/ScoreManager.h"
#include "../../Bullet/Enemy/EnemyBullet.h"
#include "../Player/Player.h"
#include "../../../Loader/CsvLoader.h"
#include "EnemyBossBase.h"

std::deque<int>EnemyBossBase::_bossHp;


// �{�X�G�l�~�[�f�[�^�ǂݎ��
EnemyBossBase::EnemyBossBase(const EnemyBossInfo& data, const Shared<Player>& player, const Shared<dxe::Camera>& camera)  {

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


void EnemyBossBase::ActKeepDistanceToPlayer(const float& delta_time) {

	// �G�ƃv���C���[�̋���
	float current_distance = GetDistanceToPlayer();
	// �G�ƃv���C���[�̋���
	tnl::Vector3 _diff_vector = _player_ref->_mesh->pos_ - _mesh->pos_;

	tnl::Vector3 moveDirection;

	if (current_distance < 500) {

		moveDirection.x = _diff_vector.x * -1;
		moveDirection.z = _diff_vector.z * -1;
	}
	else if (current_distance > 500) {
		moveDirection.x = _diff_vector.x;
		moveDirection.z = _diff_vector.z;
	}
	else {
		moveDirection = tnl::Vector3::Cross(_diff_vector, tnl::Vector3::up);
	}

	moveDirection.normalize();
	_mesh->pos_.y = _player_ref->_mesh->pos_.y + 20;
	_mesh->pos_ += moveDirection * 100.f * delta_time;
}


void EnemyBossBase::DecreaseBossHP(int damage) {

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


bool EnemyBossBase::ShowHpGage_EnemyBoss() {

	if (!_bossHp.empty()) {

		float x1 = 430, x2 = 860;
		int   y1 = 675, y2 = 695;

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



void EnemyBossBase::RenderBossRemainLife() {

	for (int i = 0; i < _remaining_life_indicator.size(); i++) {

		DrawOvalAA(600 + (i * 30), 655, 12, 12, 4, GetColor(230, 0, 0), true);
	}
	for (int i = 0; i < 4; i++) {

		DrawOvalAA(600 + (i * 30), 655, 12, 12, 4, GetColor(230, 0, 0), false);
	}
}



void EnemyBossBase::RenderBossName() {

	//�t�H���g�T�C�Y�ύX��������
	SetFontSize(18);
	DrawString(430, 700, _name.c_str(), -1);
}