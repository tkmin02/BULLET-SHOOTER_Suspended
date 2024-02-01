#include <random>
#include "../Player/Player.h"
#include "../../EnemyMove/EnemyMover.h"
#include "../../../Manager/Score/ScoreManager.h"
#include "../../Bullet/Enemy/EnemyBullet.h"
#include "EnemyZakoBase.h"
#include "../../../Loader/CsvLoader.h"

Shared<dxe::Particle> EnemyZakoBase::_explode_particle;


// 雑魚エネミーデータ読み取り
EnemyZakoBase::EnemyZakoBase(const EnemyZakoInfo& data, const Shared<Player>& player, const Shared<dxe::Camera>& camera) {


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




void EnemyZakoBase::DecreaseHP(int damage, Shared<dxe::Camera> camera) {

	_hp -= damage;

	if (_hp <= 0) {

		dxe::DirectXRenderBegin();
		_explode_particle->setPosition(_mesh->pos_);
		_explode_particle->start();
		_explode_particle->render(camera);
		dxe::DirectXRenderEnd();

		ScoreManager::GetInstance().AddKillBonus(1000);
		_isDead = true;

	}
}


bool EnemyZakoBase::ShowHpGage_EnemyZako() {

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