#include "EnemyManager.h"
#include "../../ScenePlay/Character/Enemy/EnemyZakoBox.h"
#include "../../Loader/EnemyLoader.h"
#include "../../ScenePlay/Collision/Collision.h"
#include "../../ScenePlay/Bullet/Player/PlayerBullet.h"
#include <random>
#include "../../ScenePlay/Bullet/Enemy/StraightBullet.h"


EnemyManager::EnemyManager(const Shared<Player>& player, const Shared<dxe::Camera>& camera, Shared<Collision>& collision)
	: _player_ref(player), _mainCamera_ref(camera), _collision_ref(collision) {


	// 敵のロード
	_enemyLoader = std::make_shared<EnemyLoader>();

	_enemyData = _enemyLoader->LoadEnemyInfos("csv/EnemyInfos.csv");


	NewEnemy();


	for (auto enemy : _enemy_zakoBox_list) {

		enemy->Initialize();

	}

	_enemyBase = std::make_shared<EnemyBase>(_enemy_zakoBox_list);
	_enemy_zakoBox = std::make_shared<EnemyZakoBox>();

	_enemyBase->NewEnemyMover();
	_enemyBase->InitEnemyMove();

	// プレイヤークラスでエネミーのリストを参照する変数
	_player_ref->SetEnemiesListRef_ClassP(_enemy_zakoBox_list);
}



void EnemyManager::NewEnemy() {

	// 生成位置はランダムにしたい
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> rateDistribution(-1.0f, 1.0f);

	// ロードしたエネミーデータ分ループ
	for (auto enemy = _enemyData.begin(); enemy != _enemyData.end(); enemy++) {

		switch ((*enemy).first)
		{
		case 0:

			_sEnemy_zakoBox_info._hp = (*enemy).second._hp;
			_sEnemy_zakoBox_info._speed = (*enemy).second._speed;
			_sEnemy_zakoBox_info._maxSpawnCount = (*enemy).second._maxSpawnCount;

		default:
			break;
		}
	}

	for (int i = 0; i < _sEnemy_zakoBox_info._maxSpawnCount; i++) {


		_enemy_zakoBox_list.emplace_back(std::make_shared<EnemyZakoBox>(_enemyData[0], _player_ref, _mainCamera_ref));
	}

}


// 難易度によって生成間隔は異なる
//　更に敵のスピードやHp、スポーンカウントも異なる
void EnemyManager::SpawnEnemy(const float& delta_time) {



	// 該当のエネミーの最大生成数分ループ

}



void EnemyManager::SetCollisionPairList() {

	for (auto it : _enemy_zakoBox_list) {

		// プレイヤーとZakoBox
		_collision_ref->CheckCollision_PlayerAndEnemy(_player_ref, it, _collision_ref->COLLISION_SIZE_ZAKOBOX, _player_ref->GetPos());

		// プレイヤーの弾とZakoBox
		for (Shared<PlayerBullet> b : _player_ref->_straight_bullets_p) {
			_collision_ref->CheckCollision_PlayerBulletAndEnemy(b, it, _collision_ref->COLLISION_SIZE_ZAKOBOX, _player_ref->GetPos());
		}
	}


	if (EnemyZakoBox::_straight_bullets_e.size() >= 1) {

		for (auto it : _enemy_zakoBox->_straight_bullets_e) {

			//敵の弾とプレイヤー
			DrawString(200, 200, "hit", -1);

			tnl::Vector3 prev_pos = (*it)._mesh->pos_;
			_collision_ref->CheckCollision_EnemyBulletAndPlayer(it, _player_ref, tnl::Vector3{ 30,30,30 }, prev_pos);
		}
	}
}






std::list<tnl::Vector3> EnemyManager::GetEnemyPositions_FromPlayer() {

	std::list<tnl::Vector3> enemy_pos;

	for (auto& it_enemies : _enemy_zakoBox_list) {

		// 有効なエネミーのみリストに格納
		if (it_enemies) {

			enemy_pos.emplace_back(_player_ref->_mesh->pos_ - it_enemies->_mesh->pos_);
		}
	}

	return enemy_pos;
}



void EnemyManager::Render() const {


	for (const auto enemy : _enemy_zakoBox_list) {
		enemy->Render(_mainCamera_ref);
	}
}



bool EnemyManager::Update(const float& deltaTime) {

	SpawnEnemy(deltaTime);

	for (auto it_enemy = _enemy_zakoBox_list.begin(); it_enemy != _enemy_zakoBox_list.end();) {

		(*it_enemy)->SetDeltaTimeRef(deltaTime);

		if ((*it_enemy)->Update(deltaTime) == false) {

			it_enemy = _enemy_zakoBox_list.erase(it_enemy);
		}
		else {
			it_enemy++;
		}
	}

	SetCollisionPairList();

	return true;
}
