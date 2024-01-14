#pragma once
#include <chrono>
#include "../../../DxLibEngine.h"
#include "../Player/Player.h"
#include "../../../Loader/CsvLoader.h"
#include "../../Bullet/Bullet.h"
#include "../../Bullet/Enemy/EnemyBullet.h"
#include "../../EnemyMove/EnemyMover.h"

class EnemyMover;
class EnemyBullet;
class StraightBullet;

class EnemyBase : public CollisionObject
{
public:

	//-
	EnemyBase() {}

	EnemyBase(std::vector<Shared<EnemyBase>>& enemyList) {}

	EnemyBase(const EnemyZakoInfo& data, const Shared<Player>& player, const Shared<dxe::Camera>& camera);

	EnemyBase(const EnemyBossInfo& data, const Shared<Player>& player, const Shared<dxe::Camera>& camera);

	virtual ~EnemyBase() = default;

	virtual bool Update(float delta_time);

	virtual void Render(Shared<dxe::Camera> _mainCamera) {};

	void Initialize();

	// EnemyMover オブジェクト生成
	void NewEnemyMover() { _mover = std::make_shared<EnemyMover>(); }

	// ゲッター
	float GetDistanceToPlayer();

	tnl::Vector3 GetRandomPosition_Mt19337() const;

	// 敵の行動パターン初期化
	void InitEnemyMove();

	void DecreaseHP(int damage);

	void DecreaseBossHP(int damage);


	virtual bool ShowHpGage_EnemyZako();

	virtual bool ShowHpGage_EnemyBoss();

protected:

	// 弾系--------------------------------------------------------------
	virtual void UpdateStraightBullet(const float delta_time) {}
	// プレイヤーへ照射、追跡なし
	virtual void ShotStraightBullet(std::list<Shared<EnemyBullet>> bullet) {};

	virtual void UpdateHomingBullet(const float delta_time) {}

	virtual void InitHomingBullet() {}

	// 形状、テクスチャ、ポジション、スケール
	virtual void SetMeshInfo() {};

	// 複製
	virtual void Clone() {}

	virtual void InitStraightBullet() {}

	// プレイヤーへ照射、角度制限付きで追跡
	virtual void ShotHomingBullet() {};

	virtual tnl::Vector3 CalcVecFromAngle(float angle) { return _mesh->pos_; };

	virtual float GetAngleBtw_EnemyAndPlayer(Shared<dxe::Mesh> enemy, Shared<Player> player) { return 0; };


	// 待機、追跡、攻撃などのパターンを管理し実行
	virtual void DoRoutineMoves(float delta_time) {}

	virtual void ChasePlayer(const float delta_time) {}

	virtual void AttackPlayer(float delta_time) {}

	void LookAtPlayer();

	void RenderBossName();

	void RenderBossRemainLife();

public:

	Shared<dxe::Mesh>       _mesh = nullptr;

protected:

	std::list <Shared<EnemyBase>> _enemy_list_ref;

	// ScenePlayのメンバ変数参照ポインタ	
	Shared<Player>        _player_ref = nullptr;
	Shared<dxe::Camera>   _mainCamera_ref = nullptr;

	Shared<EnemyMover> _mover = nullptr;

public:

	bool _isDead = false;    //敵単体の死亡フラグ
	bool _isAllDead = false; //敵クラス(最大生成数分)の死亡フラグ
	bool _canShotStraightBullet = true;   // 直行弾が撃てる状態か
	bool _canShotHomingBullet = true;   // 直行弾が撃てるようになったか


	// CSVからロード-----------------------

	int            _id{};
	int            _maxBulletSpawnCount{};
	int            _maxTotalEnemySpawnCount{};
	int            _hp{};
	std::deque<int>_bossHp{};
	float          _charaMoveSpeed{};
	float          _scale{};
	std::string    _name{};
	int _MAX_HP{};

	// ------------------------------------

protected:

	int        _move_pattern_id{};  //移動パターン

	int _life_timer{}; // 生成時に時間カウントを開始し、寿命を超えたら消滅

	int _life_time_limit{}; // 敵の寿命。タイマーがこの値を超えたら敵が消滅

	// 弾系--------------------------------------------------------------
	unsigned int last_shot_time_straight_blt;
	unsigned int last_shot_time_homing_blt;

private:

	std::stack<std::deque<int>> _remaining_life_indicator;

};