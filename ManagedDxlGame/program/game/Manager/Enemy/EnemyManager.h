#pragma once
#include "./../../DxLibEngine.h"
#include "../../ScenePlay/Character/Enemy/EnemyBase.h"
#include "../../ScenePlay/Character/Player/Player.h"

class Collision;
class Score;
class EnemyZakoBox;
class EnemyZakoDome;
class EnemyZakoCylinder;
struct EnemyZakoInfo;
struct EnemyBossInfo;


// 生成・削除・更新を管理

class EnemyManager
{
public:

	EnemyManager() {}

	EnemyManager(int stageID, const Shared<Player>& player, const Shared<dxe::Camera>& camera, Shared<Collision>& collision, const std::string difficulty, Shared<Score>& score, int current_score);

	~EnemyManager() { _enemy_zako_list.clear(); }

	void Update(const float& deltaTime);
	void Render() const;

	std::list< tnl::Vector3> GetEnemyPositions_FromPlayer();

private:

	void InitEnemyZakoInfo(int stage_id);

	void InitEnemyBossInfo(int stage_id);

	// 敵のスポーン位置はプレイヤーの位置や行動に応じて決める
	void CheckDoSpawnZakoEnemy();

	// ボス召喚準備
	void SetSpawnEnemyBoss(const int stage_id);

	void SetCollisionPairList();

	tnl::Sequence<EnemyManager> _sequence = tnl::Sequence<EnemyManager>(this, &EnemyManager::SeqMoveNextStage);
	// 次のステージに行くか、ゲームクリアかのどちらか
	bool SeqMoveNextStage(float deltaTime);

	bool IsKilledStageBoss();

private:

	Shared<CsvLoader>   _csvLoader = nullptr;
	Shared<EnemyBase>   _enemyBase = nullptr;
	Shared<EnemyZakoBox>_enemy_zakoBox = nullptr;
	Shared<EnemyZakoDome>_enemy_zakoDome = nullptr;
	Shared<EnemyZakoCylinder>_enemy_zakoCylinder = nullptr;


	// 参照
	Shared<Player>      _player_ref = nullptr;
	Shared<dxe::Camera> _mainCamera_ref = nullptr;
	Shared<Collision>   _collision_ref = nullptr;
	Shared<Score>       _score_ref = nullptr;


	// Zako
	std::vector<Shared<EnemyBase>> _enemy_zako_list;
	std::unordered_map<int, EnemyZakoInfo> _enemyZakoData_map;
	EnemyZakoInfo _sEnemy_zakoBox_info{};
	EnemyZakoInfo _sEnemy_zakoDome_info{};
	EnemyZakoInfo _sEnemy_zakoCylinder_info{};

	// Boss
	std::vector<Shared<EnemyBase>> _enemy_boss_list;
	std::unordered_map<int, EnemyBossInfo> _enemyBossData_map;
	EnemyBossInfo _sBoss_PatchouliKnowledge_info{};
	EnemyBossInfo _sBoss_Cirno_info{};
	EnemyBossInfo _sBoss_MoriyaSuwako_info{};

private:

	const std::string _SELECTED_LEVEL;

	static int _remainingZakoBox_spawnCount;
	static int _remainingZakoDome_spawnCount;
	static int _remainingZakoCylinder_spawnCount;


	bool summon_boss = false;

	// PlayerSceneからのスコア参照変数
	int _CURRENT_SCORE_REF{};
	int _stageID{};

	// 1度に生成が可能な最大数
	int maxEnemySpawnCount_PerInterval{};
};