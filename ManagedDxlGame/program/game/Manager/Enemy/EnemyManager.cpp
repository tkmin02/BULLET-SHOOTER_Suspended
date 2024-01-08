#include <random>
#include "EnemyManager.h"
#include "../../ScenePlay/Character/Enemy/EnemyZakoBox.h"
#include "../../Loader/EnemyLoader.h"
#include "../../ScenePlay/Collision/Collision.h"
#include "../../ScenePlay/Bullet/Player/PlayerBullet.h"
#include "../../ScenePlay/Bullet/Enemy/StraightBullet.h"
#include "../../ScenePlay/Bullet/Enemy/HomingBullet.h"

int EnemyManager::_spawnedCount_zakoBox = 0;


EnemyManager::EnemyManager(
	const Shared<Player>& player, const Shared<dxe::Camera>& camera, Shared<Collision>& collision, const std::string difficulty)
	: _player_ref(player), _mainCamera_ref(camera), _collision_ref(collision), _SELECTED_LEVEL(difficulty) {


	// 敵のロード
	_enemyLoader = std::make_shared<EnemyLoader>(difficulty);

	_enemyZakoData_map = _enemyLoader->LoadEnemyZakoInfos("csv/EnemyZakoInfos.csv");

	if (_SELECTED_LEVEL == "Easy")         maxEnemySpawnCount_PerInterval = 1;
	else if (_SELECTED_LEVEL == "Normal")  maxEnemySpawnCount_PerInterval = 2;
	else if (_SELECTED_LEVEL == "Hard")    maxEnemySpawnCount_PerInterval = 3;
	else if (_SELECTED_LEVEL == "Lunatic") maxEnemySpawnCount_PerInterval = 4;

	NewEnemy();

	// メッシュの定義など
	for (auto enemy : _enemy_zako_list) enemy->Initialize();


	_enemy_zakoBox = std::make_shared<EnemyZakoBox>(_enemy_zako_list);


	// プレイヤークラスでエネミーのリストを参照する変数
	_player_ref->SetEnemiesListRef_ClassP(_enemy_zako_list);
}



void EnemyManager::NewEnemy() {

	// 生成位置はランダムにしたい
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> rateDistribution(-1.0f, 1.0f);

	// ロードしたエネミーデータ分ループ
	for (auto enemy = _enemyZakoData_map.begin(); enemy != _enemyZakoData_map.end(); enemy++) {

		switch ((*enemy).first)
		{
		case 0:

			_sEnemy_zakoBox_info._maxTotalEnemySpawnCount = (*enemy).second._maxTotalEnemySpawnCount;

		default:
			break;
		}
	}


	for (int i = 0; i < maxEnemySpawnCount_PerInterval; i++) {
		_enemy_zako_list.emplace_back(std::make_shared<EnemyZakoBox>(_enemyZakoData_map[0], _player_ref, _mainCamera_ref));
		EnemyManager::_spawnedCount_zakoBox++;
	}
}





void EnemyManager::CheckDoSpawnEnemy(const float& delta_time) {


	// EnemyZakoBoxがまだ１体でも画面上に残っていれば
	if (_enemy_zako_list[0] || !_enemy_zako_list[0]->_isDead) return;

	for (int i = 0; i < maxEnemySpawnCount_PerInterval; i++) {


		// 生成数が全体の上限値に達したら
		if (EnemyManager::_spawnedCount_zakoBox >= _sEnemy_zakoBox_info._maxTotalEnemySpawnCount) break;


		_enemy_zako_list.emplace_back(std::make_shared<EnemyZakoBox>(_enemyZakoData_map[0], _player_ref, _mainCamera_ref));
		EnemyManager::_spawnedCount_zakoBox++;
	}

	_enemy_zako_list[0]->_isAllDead = true;
}




void EnemyManager::SetCollisionPairList() {

	for (auto it : _enemy_zako_list) {

		// プレイヤーとZakoBox
		_collision_ref->CheckCollision_PlayerAndEnemy(_player_ref, it, _collision_ref->COLLISION_SIZE_ZAKOBOX, _player_ref->GetPos());

		// プレイヤーの弾とZakoBox
		for (Shared<PlayerBullet> b : _player_ref->_straight_bullets_p) {
			_collision_ref->CheckCollision_PlayerBulletAndEnemy(b, it, _collision_ref->COLLISION_SIZE_ZAKOBOX, _player_ref->GetPos());
		}
	}


	//敵の直進弾とプレイヤー
	if (EnemyZakoBox::_straight_bullets_e.size() >= 1) {

		for (auto it : _enemy_zakoBox->_straight_bullets_e) {

			tnl::Vector3 prev_pos = (*it)._mesh->pos_;
			_collision_ref->CheckCollision_EnemyStraightBulletAndPlayer(it, _player_ref, tnl::Vector3{ 30,30,30 }, prev_pos);
		}
	}

	//敵の追尾弾とプレイヤー
	if (EnemyZakoBox::_homing_bullets_e.size() >= 1) {

		for (auto it : _enemy_zakoBox->_homing_bullets_e) {

			tnl::Vector3 prev_pos = (*it)._mesh->pos_;
			_collision_ref->CheckCollision_EnemyHomingBulletAndPlayer(it, _player_ref, tnl::Vector3{ 30,30,30 }, prev_pos);
		}
	}
}





std::list<tnl::Vector3> EnemyManager::GetEnemyPositions_FromPlayer() {

	std::list<tnl::Vector3> enemy_pos;

	for (auto& it_enemies : _enemy_zako_list) {

		// 有効なエネミーのみリストに格納
		if (it_enemies) {

			enemy_pos.emplace_back(_player_ref->_mesh->pos_ - it_enemies->_mesh->pos_);
		}
	}

	return enemy_pos;
}



void EnemyManager::Render() const {


	for (const auto enemy : _enemy_zako_list) {
		enemy->Render(_mainCamera_ref);
	}
}



bool EnemyManager::Update(const float& deltaTime) {

	CheckDoSpawnEnemy(deltaTime);
	SetCollisionPairList();

	for (auto it_enemy = _enemy_zako_list.begin(); it_enemy != _enemy_zako_list.end();) {

		(*it_enemy)->SetDeltaTimeRef(deltaTime);

		if ((*it_enemy)->Update(deltaTime) == false) {

			it_enemy = _enemy_zako_list.erase(it_enemy);
		}
		else {
			it_enemy++;
		}
	}


	return true;
}
