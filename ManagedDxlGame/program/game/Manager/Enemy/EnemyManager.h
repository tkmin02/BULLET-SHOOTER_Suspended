#pragma once
#include "./../../DxLibEngine.h"
#include "../../ScenePlay/Character/Enemy/EnemyBase.h"
#include "../../ScenePlay/Character/Player/Player.h"

class Collision;
class EnemyZakoBox;
struct EnemyInfo;


// 生成・削除・更新を管理

class EnemyManager
{
public:

	EnemyManager(){}

	EnemyManager(const Shared<Player>& player, const Shared<dxe::Camera>& camera, Shared<Collision>& collision);

	~EnemyManager() { _enemy_zakoBox_list.clear(); }

	bool Update(const float& deltaTime);
	void Render() const;

	std::list< tnl::Vector3> GetEnemyPositions_FromPlayer();

private:

	void NewEnemy();

	// 敵のスポーン位置はプレイヤーの位置や行動に応じて決める
	void SpawnEnemy(const float& delta_time);

	void SetCollisionPairList();


private:

	Shared<EnemyLoader> _enemyLoader = nullptr;
	Shared<EnemyBase> _enemyBase = nullptr;

	Shared<EnemyZakoBox> _enemy_zakoBox = nullptr;

	std::list<Shared<EnemyBase>> _enemy_zakoBox_list;
	std::unordered_map<int, EnemyInfo> _enemyData;


	EnemyInfo _sEnemy_zakoBox_info;



	// 参照
	Shared<Player> _player_ref;

	Shared<dxe::Camera> _mainCamera_ref;

	Shared<Collision> _collision_ref;

private:

	int _enemyIndex{};
};

