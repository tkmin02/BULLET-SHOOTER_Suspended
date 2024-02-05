#pragma once
#include "./../../DxLibEngine.h"
#include "../../../library/tnl_sequence.h"
#include "../../Loader/CsvLoader.h"

class Collision;
class Score;
class EnemyZakoBox;
class EnemyZakoDome;
class EnemyZakoCylinder;
class EnemyZakoBase;
class EnemyBossBase;
class Player;

// 生成・削除・更新を管理

class EnemyManager
{
public:

	EnemyManager() {}

	EnemyManager(int stageID, const Shared<Player>& player, const Shared<dxe::Camera>& camera, Shared<Collision>& collision, const std::string difficulty);

	~EnemyManager() { _enemy_zako_list.clear(); }

	void Update(const float& deltaTime);
	void Render() const;

	const std::vector<tnl::Vector3>& GetEnemyZakoPosition();

	const tnl::Vector3& GetEnemyBossPosition();

private:

	// 雑魚
	void InitEnemyZakoInfo(int stage_id);
	void EnemyZakoCollisionPairLists();
	void EnemyZakoBulletCollisionPairLists();


	// ボス
	void SetSpawnEnemyBoss(const int stage_id);
	void EnemyBossCollisionPairLists();
	void BulletHellCollisionPairLists();
	void InitEnemyBossInfo(int stage_id);
	void ShowAppearsBossText();
	bool IsKilledStageBoss();

	// ザコ及びボスの生成タイミングを制御
	void CheckDoSpawnEnemy(const float& deltaTime);
	void SetCollisionPairList();

	tnl::Sequence<EnemyManager> _sequence = tnl::Sequence<EnemyManager>(this, &EnemyManager::SeqMoveToNextStage);
	// 次のステージに行くか、ゲームクリアかのどちらか
	bool SeqMoveToNextStage(const float deltaTime);

	bool SeqMoveToResult(const float deltaTime);

private:

	Shared<CsvLoader>     _csvLoader = nullptr;
	Shared<EnemyZakoBase> _enemyZakoBase = nullptr;
	Shared<EnemyBossBase> _enemyBossBase = nullptr;

	// 参照
	Shared<Player>      _player_ref = nullptr;
	Shared<dxe::Camera> _mainCamera_ref = nullptr;
	Shared<Collision>   _collision_ref = nullptr;
	Shared<Score>       _score_ref = nullptr;

	// Zako
	std::vector<Shared<EnemyZakoBase>> _enemy_zako_list;
	std::unordered_map<int, EnemyZakoInfo> _enemyZakoData_map;
	EnemyZakoInfo _sEnemy_zakoBox_info{};
	EnemyZakoInfo _sEnemy_zakoDome_info{};
	EnemyZakoInfo _sEnemy_zakoCylinder_info{};

	// Boss
	std::vector<Shared<EnemyBossBase>> _enemy_boss_list{};
	std::unordered_map<int, EnemyBossInfo> _enemyBossData_map{};
	EnemyBossInfo _sBoss_PatchouliKnowledge_info{};
	EnemyBossInfo _sBoss_Cirno_info{};
	EnemyBossInfo _sBoss_MoriyaSuwako_info{};

private:

	const std::string _SELECTED_LEVEL;

	static int _remainingZakoBox_spawnCount;
	static int _remainingZakoDome_spawnCount;
	static int _remainingZakoCylinder_spawnCount;

	bool _isShowBossAppearanceText{};
	bool _summon_boss = false;

	bool _isDefeatedAllStageEnemy{};

	// PlayerSceneからのスコア参照変数
	int _CURRENT_SCORE_REF{};
	int _stageID{};

	// 1度に生成が可能な最大数
	int maxEnemySpawnCount_PerInterval{};

	int _alertSE_hdl{};

	static float _showBossAppearanceText_timer;
};