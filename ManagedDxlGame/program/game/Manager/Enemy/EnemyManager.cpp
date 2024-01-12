#include <random>
#include "EnemyManager.h"
#include "../../ScenePlay/Character/Enemy/EnemyZakoBox.h"
#include "../../ScenePlay/Character/Enemy/EnemyZakoDome.h"
#include "../../ScenePlay/Character/Enemy/EnemyZakoCylinder.h"
#include "../../ScenePlay/Character/EnemyBoss/EnemyBoss_PatchouliKnowledge.h"
#include "../../ScenePlay/Character/EnemyBoss/EnemyBoss_Cirno.h"
#include "../../ScenePlay/Character/EnemyBoss/EnemyBoss_MoriyaSuwako.h"
#include "../../Loader/CsvLoader.h"
#include "../../ScenePlay/Collision/Collision.h"
#include "../../ScenePlay/Bullet/Player/PlayerBullet.h"
#include "../../ScenePlay/Bullet/Enemy/StraightBullet.h"
#include "../../ScenePlay/Bullet/Enemy/HomingBullet.h"


int EnemyManager::_deadCount_zakoBox = 0;


EnemyManager::EnemyManager(
	int stageID, const Shared<Player>& player, const Shared<dxe::Camera>& camera, Shared<Collision>& collision, const std::string difficulty)
	: _player_ref(player), _mainCamera_ref(camera), _collision_ref(collision), _SELECTED_LEVEL(difficulty), _stageID(stageID) {


	// 敵のロード
	_csvLoader = std::make_shared<CsvLoader>(difficulty);


	_enemyZakoData_map = _csvLoader->LoadEnemyZakoInfos("csv/EnemyZakoInfos.csv");
	_enemyBossData_map = _csvLoader->LoadEnemyBossInfos("csv/EnemyBossInfos.csv");

	if (_SELECTED_LEVEL == "Easy")         maxEnemySpawnCount_PerInterval = 1;
	else if (_SELECTED_LEVEL == "Normal")  maxEnemySpawnCount_PerInterval = 2;
	else if (_SELECTED_LEVEL == "Hard")    maxEnemySpawnCount_PerInterval = 3;
	else if (_SELECTED_LEVEL == "Lunatic") maxEnemySpawnCount_PerInterval = 4;

	InitEnemyZakoInfo(_stageID);
	InitEnemyBossInfo(_stageID);

	// メッシュの定義など
	for (auto enemy : _enemy_zako_list) enemy->Initialize();

	for (auto enemy : _enemy_boss_list) enemy->Initialize();


	// プレイヤークラスでエネミーのリストを参照する変数
	_player_ref->SetEnemiesListRef_ClassP(_enemy_zako_list);
}



void EnemyManager::InitEnemyZakoInfo(int stage_id) {

	// 生成位置はランダムにしたい
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> rateDistribution(-1.0f, 1.0f);

	// ロードしたエネミーデータ分ループ
	for (auto enemy = _enemyZakoData_map.begin(); enemy != _enemyZakoData_map.end(); enemy++) {

		switch ((*enemy).first) // id
		{
		case 0: // EnemyZakoBoxデータ取得
			_sEnemy_zakoBox_info._charaMoveSpeed = (*enemy).second._charaMoveSpeed;
			_sEnemy_zakoBox_info._maxTotalEnemySpawnCount = (*enemy).second._maxTotalEnemySpawnCount;
			_sEnemy_zakoBox_info._name = (*enemy).second._name;
			_sEnemy_zakoBox_info._scale = (*enemy).second._scale;
			_sEnemy_zakoBox_info._stageID = (*enemy).second._stageID;
			break;
		case 1: // EnemyZakoDomeデータ取得
			_sEnemy_zakoDome_info._charaMoveSpeed = (*enemy).second._charaMoveSpeed;
			_sEnemy_zakoDome_info._maxTotalEnemySpawnCount = (*enemy).second._maxTotalEnemySpawnCount;
			_sEnemy_zakoDome_info._name = (*enemy).second._name;
			_sEnemy_zakoDome_info._scale = (*enemy).second._scale;
			_sEnemy_zakoDome_info._stageID = (*enemy).second._stageID;
			break;
		case 2: // EnemyZakoCylinderデータ取得
			_sEnemy_zakoCylinder_info._charaMoveSpeed = (*enemy).second._charaMoveSpeed;
			_sEnemy_zakoCylinder_info._maxTotalEnemySpawnCount = (*enemy).second._maxTotalEnemySpawnCount;
			_sEnemy_zakoCylinder_info._name = (*enemy).second._name;
			_sEnemy_zakoCylinder_info._scale = (*enemy).second._scale;
			_sEnemy_zakoCylinder_info._stageID = (*enemy).second._stageID;
			break;
		default:
			break;
		}
	}

	if (stage_id == _sEnemy_zakoBox_info._stageID) {

		for (int i = 0; i < _sEnemy_zakoBox_info._maxTotalEnemySpawnCount; i++) {

			auto enemy_box = std::make_shared<EnemyZakoBox>(_enemyZakoData_map[0], _player_ref, _mainCamera_ref);

			enemy_box->_isDead = false;
			enemy_box->_charaMoveSpeed = _sEnemy_zakoBox_info._charaMoveSpeed;
			enemy_box->_name = _sEnemy_zakoBox_info._name;
			enemy_box->_scale = _sEnemy_zakoBox_info._scale;
			_enemy_zako_list.push_back(enemy_box);	// EnemyZakoBox 生成
		}
	}
	else if (stage_id == _sEnemy_zakoDome_info._stageID) {

		for (int j = 0; j < _sEnemy_zakoDome_info._maxTotalEnemySpawnCount; j++) {

			auto enemy_dome = std::make_shared<EnemyZakoDome>(_enemyZakoData_map[1], _player_ref, _mainCamera_ref);

			enemy_dome->_isDead = false;
			enemy_dome->_charaMoveSpeed = _sEnemy_zakoDome_info._charaMoveSpeed;
			enemy_dome->_name = _sEnemy_zakoDome_info._name;
			enemy_dome->_scale = _sEnemy_zakoDome_info._scale;
			_enemy_zako_list.push_back(enemy_dome); // EnemyZakoDome 生成 
		}
	}
	else if (stage_id == _sEnemy_zakoCylinder_info._stageID) {

		for (int j = 0; j < _sEnemy_zakoCylinder_info._maxTotalEnemySpawnCount; j++) {

			auto enemy_cylinder = std::make_shared<EnemyZakoCylinder>(_enemyZakoData_map[2], _player_ref, _mainCamera_ref);

			enemy_cylinder->_isDead = false;
			enemy_cylinder->_charaMoveSpeed = _sEnemy_zakoCylinder_info._charaMoveSpeed;
			enemy_cylinder->_name = _sEnemy_zakoCylinder_info._name;
			enemy_cylinder->_scale = _sEnemy_zakoCylinder_info._scale;
			_enemy_zako_list.push_back(enemy_cylinder); // EnemyZakoCylinder 生成 
		}
	}
}




void EnemyManager::InitEnemyBossInfo(int stage_id) {

	for (auto boss = _enemyBossData_map.begin(); boss != _enemyBossData_map.end(); boss++) {

		switch ((*boss).first) // id
		{
		case 0: // パチュリー データ取得
			_sBoss_PatchouliKnowledge_info._charaMoveSpeed = (*boss).second._charaMoveSpeed;
			_sBoss_PatchouliKnowledge_info._name = (*boss).second._name;
			_sBoss_PatchouliKnowledge_info._scale = (*boss).second._scale;
			_sBoss_PatchouliKnowledge_info._stageID = (*boss).second._stageID;
			break;
		case 1: // チルノ データ取得
			_sBoss_Cirno_info._charaMoveSpeed = (*boss).second._charaMoveSpeed;
			_sBoss_Cirno_info._name = (*boss).second._name;
			_sBoss_Cirno_info._scale = (*boss).second._scale;
			_sBoss_Cirno_info._stageID = (*boss).second._stageID;
			break;
		case 2: // 洩矢諏訪子 データ取得
			_sBoss_MoriyaSuwako_info._charaMoveSpeed = (*boss).second._charaMoveSpeed;
			_sBoss_MoriyaSuwako_info._name = (*boss).second._name;
			_sBoss_MoriyaSuwako_info._scale = (*boss).second._scale;
			_sBoss_MoriyaSuwako_info._stageID = (*boss).second._stageID;
			break;
		default:
			break;
		}
	}


	if (stage_id == _sBoss_PatchouliKnowledge_info._stageID) {

		auto boss_patchouli = std::make_shared<EnemyBoss_PatchouliKnowledge>(_enemyBossData_map[0], _player_ref, _mainCamera_ref);

		boss_patchouli->_isDead = false;
		boss_patchouli->_charaMoveSpeed = _sBoss_PatchouliKnowledge_info._charaMoveSpeed;
		boss_patchouli->_name = _sBoss_PatchouliKnowledge_info._name;
		boss_patchouli->_scale = _sBoss_PatchouliKnowledge_info._scale;

		_enemy_boss_list.push_back(boss_patchouli); // EnemyZakoDome 生成 
	}
	else if (stage_id == _sBoss_Cirno_info._stageID) {

		auto boss_cirno = std::make_shared<EnemyBoss_Cirno>(_enemyBossData_map[1], _player_ref, _mainCamera_ref);

		boss_cirno->_isDead = false;
		boss_cirno->_charaMoveSpeed = _sBoss_Cirno_info._charaMoveSpeed;
		boss_cirno->_name = _sBoss_Cirno_info._name;
		boss_cirno->_scale = _sBoss_Cirno_info._scale;

		_enemy_boss_list.push_back(std::make_shared<EnemyBoss_Cirno>(boss_cirno));
	}
	else if (stage_id == _sBoss_MoriyaSuwako_info._stageID) {

		auto boss_suwako = std::make_shared<EnemyBoss_MoriyaSuwako>(_enemyBossData_map[2], _player_ref, _mainCamera_ref);

		boss_suwako->_isDead = false;
		boss_suwako->_charaMoveSpeed = _sBoss_MoriyaSuwako_info._charaMoveSpeed;
		boss_suwako->_name = _sBoss_MoriyaSuwako_info._name;
		boss_suwako->_scale = _sBoss_MoriyaSuwako_info._scale;

		_enemy_boss_list.push_back(std::make_shared<EnemyBoss_MoriyaSuwako>(boss_suwako));
	}
}




void EnemyManager::CheckDoSpawnEnemy(const float& delta_time) {

	// EnemyZakoBoxがまだ１体でも画面上に残っていれば
	if (_enemy_zako_list[0] || !_enemy_zako_list[0]->_isDead) return;

	for (int i = 0; i < maxEnemySpawnCount_PerInterval; i++) {


		// 生成数が全体の上限値に達したら
		if (EnemyManager::_deadCount_zakoBox >= _sEnemy_zakoBox_info._maxTotalEnemySpawnCount) break;


		_enemy_zako_list.push_back(std::make_shared<EnemyZakoBox>(_enemyZakoData_map[0], _player_ref, _mainCamera_ref));
	}

	_enemy_zako_list[0]->_isAllDead = true;
}




void EnemyManager::SetCollisionPairList() {

	for (auto it : _enemy_zako_list) {

		// プレイヤーとZakoエネミー各種
		_collision_ref->CheckCollision_PlayerAndEnemy(_player_ref, it, _collision_ref->COLLISION_SIZE_ZAKOBOX, _player_ref->GetPos());

		// プレイヤーの弾とZakoエネミー各種
		for (Shared<PlayerBullet> b : _player_ref->_straight_bullets_p) {
			_collision_ref->CheckCollision_PlayerBulletAndEnemy(b, it, _collision_ref->COLLISION_SIZE_ZAKOBOX, _player_ref->GetPos());
		}

		// Zakoエネミー同士の当たり判定
		for (auto it2 : _enemy_zako_list) {

			tnl::Vector3 prev_pos = (*it)._mesh->pos_;

			if (it == it2) continue;
			_collision_ref->CheckCollision_EnemyAndEnemy(it, it2, _collision_ref->COLLISION_SIZE_ZAKOBOX, prev_pos);
		}
	}


	for (auto it : _enemy_boss_list) {

		// プレイヤーとBossエネミー各種
		_collision_ref->CheckCollision_PlayerAndEnemy(_player_ref, it, _collision_ref->COLLISION_SIZE_ZAKOBOX, _player_ref->GetPos());

		// プレイヤーの弾とBossエネミー各種
		for (Shared<PlayerBullet> b : _player_ref->_straight_bullets_p) {
			_collision_ref->CheckCollision_PlayerBulletAndEnemy(b, it, _collision_ref->COLLISION_SIZE_ZAKOBOX, _player_ref->GetPos());
		}
	}




	//敵の直進弾とプレイヤー
	if (EnemyZakoBox::_straight_bullets_zakoCylinder.size() >= 1) {

		for (auto it : _enemy_zakoBox->_straight_bullets_zakoCylinder) {

			tnl::Vector3 prev_pos = (*it)._mesh->pos_;
			_collision_ref->CheckCollision_EnemyStraightBulletAndPlayer(it, _player_ref, tnl::Vector3{ 30,30,30 }, prev_pos);
		}
	}

	//敵の追尾弾とプレイヤー
	if (EnemyZakoBox::_homing_bullets_zakoCylinder.size() >= 1) {

		for (auto it : _enemy_zakoBox->_homing_bullets_zakoCylinder) {

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

	// ザコ
	for (const auto enemy : _enemy_zako_list) {
		enemy->Render(_mainCamera_ref);
	}

	// ボス
	if (_enemy_zako_list.empty() && !_enemy_boss_list.empty()) {

		for (const auto boss : _enemy_boss_list) {
			boss->Render(_mainCamera_ref);
		}
	}
}



bool EnemyManager::Update(const float& deltaTime) {

	//CheckDoSpawnEnemy(deltaTime);
	SetCollisionPairList();

	// ザコ
	if (!_enemy_zako_list.empty()) {

		for (auto it_zako = _enemy_zako_list.begin(); it_zako != _enemy_zako_list.end();) {

			if ((*it_zako)->Update(deltaTime) == false) {

				it_zako = _enemy_zako_list.erase(it_zako);
			}
			else {
				it_zako++;
			}
		}
	}

	// ボス
	if (_enemy_zako_list.empty() && !_enemy_boss_list.empty()) {

		for (auto it_boss = _enemy_boss_list.begin(); it_boss != _enemy_boss_list.end();) {

			if ((*it_boss)->Update(deltaTime) == false) {

				it_boss = _enemy_boss_list.erase(it_boss);
			}
			else {
				it_boss++;
			}
		}
	}


	if (_enemy_zako_list.empty() && _enemy_boss_list.empty()) {


	}


	return true;
}