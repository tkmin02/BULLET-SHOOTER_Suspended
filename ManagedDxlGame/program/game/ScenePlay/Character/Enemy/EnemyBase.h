#pragma once
#include <chrono>
#include "../../../DxLibEngine.h"
#include "../Player/Player.h"
#include "../../../Loader/EnemyLoader.h"
#include "../../Bullet/Bullet.h"
#include "../../Bullet/Enemy/EnemyBullet.h"
#include "../../EnemyMove/EnemyMover.h"

class EnemyMover;
class EnemyBullet;
class StraightBullet;

class EnemyBase : public CollisionObject
{

public:

	EnemyBase() {}

	EnemyBase(std::vector<Shared<EnemyBase>>& enemyList) {}

	EnemyBase(const EnemyZakoInfo& data, const Shared<Player>& player, const Shared<dxe::Camera>& camera);

	virtual ~EnemyBase() = default;

	virtual bool Update(float delta_time);

	virtual void Render(Shared<dxe::Camera> _mainCamera) {};

	void Initialize();

	// EnemyMover オブジェクト生成
	void NewEnemyMover() { _mover = std::make_shared<EnemyMover>(); }

	// ゲッター
	float GetDistanceToPlayer();

	virtual float GetRandomValue_Mt19337() const { return 0.0f; }

	int GetCounter() const { return _elapsed; }

	float getSpeed() const { return _charaMoveSpeed; }

	float getAngle() const { return _angle; }

	int   getMovePatternID() const { return _move_pattern_id; }

	//　セッター
	void  setAngle(float angle) { _angle = angle; }

	// 敵の行動パターン初期化
	void InitEnemyMove();

	void DecreaseHP(int damage);

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

	virtual void LookAtPlayer(const float delta_time) {};

	// 待機、追跡、攻撃などのパターンを管理し実行
	virtual void DoRoutineMoves(float delta_time) {}

	virtual void ChasePlayer(const float delta_time) {}

	virtual void AttackPlayer(float delta_time) {}

public:

	Shared<dxe::Mesh>       _mesh = nullptr;

protected:

	std::list <Shared<EnemyBase>> _enemy_list_ref;

	// ScenePlayのメンバ変数参照ポインタ	
	Shared<Player>        _player_ref = nullptr;
	Shared<dxe::Camera>   _mainCamera_ref = nullptr;

	Shared<EnemyMover> _mover = nullptr;

	// EnemyLoader.hからの参照
	EnemyZakoInfo        _enemyInfo_ref;

public:

	bool _isDead = false;    //敵単体の死亡フラグ
	bool _isAllDead = false; //敵クラス(最大生成数分)の死亡フラグ
	bool _canShot = false;   //弾が撃てるようになったか

	// CSVからロード-----------------------

	int           _id{};
	int           _hp{};
	int           _maxBulletSpawnCount{};
	int           _maxTotalEnemySpawnCount{};
	float         _charaMoveSpeed{};
	float         _scale{};
	std::string   _name{};

	// ------------------------------------

protected:

	int        _score{};
	int        _elapsed{};
	int        _life_time_duration{};
	int        _move_pattern_id{};  //移動パターン
	float      _angle{}; // 自分自身の現在向いている方向の角度
	float      _angle_to_player{}; // 自分とプレイヤーの角度差分

	bool addedRandVal_posX = false;

	int _int_time{};  // 出現時間

	int _stop_time{}; // 停止時間

	int shot_count{}; // 弾が打てるようになってからのカウント

	int _life_timer{}; // 生成時に時間カウントを開始し、寿命を超えたら消滅

	int _life_time_limit{}; // 敵の寿命。タイマーがこの値を超えたら敵が消滅

	// 弾系--------------------------------------------------------------
	std::chrono::steady_clock::time_point last_shot_time_straight_blt;
	std::chrono::steady_clock::time_point last_shot_time_homing_blt;
};