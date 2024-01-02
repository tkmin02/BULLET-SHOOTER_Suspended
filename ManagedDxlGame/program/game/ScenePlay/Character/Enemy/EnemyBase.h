#pragma once
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

	EnemyBase(std::list <Shared<EnemyBase>> _enemyList) { _enemy_list_ref = _enemyList; }

	EnemyBase(EnemyInfo& info) {}

	EnemyBase(const EnemyInfo& data, const Shared<Player>& player, const Shared<dxe::Camera>& camera);

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

	float getSpeed() const { return _speed; }

	float getAngle() const { return _angle; }

	int   getMovePatternID() const { return _move_pattern_id; }

	//　セッター
	void  setAngle(float angle) { _angle = angle; }

	// 敵の行動パターン初期化
	void InitEnemyMove();

protected:

	// 形状、テクスチャ、ポジション、スケール
	virtual void SetMeshInfo() {};

	// 複製
	virtual void Clone() {}


	// プレイヤーへ照射、追跡なし
	virtual void ShotStraightBullet() {};

	virtual std::list<Shared<StraightBullet>> InitStraightBullet() { return _straight_bullets_e; }


	// プレイヤーへ照射、角度制限付きで追跡
	virtual void ShotHomingBullet() {};

	virtual tnl::Vector3 CalcVecFromAngle(float angle) { return _mesh->pos_; };

	virtual float GetAngleBtw_EnemyAndPlayer(Shared<dxe::Mesh> enemy, Shared<Player> player) { return 0; };

	virtual void LookAtPlayer(const float delta_time) {};

public:

	Shared<dxe::Mesh>       _mesh = nullptr;

protected:

	std::list<Shared<StraightBullet>> _straight_bullets_e;
	std::list <Shared<EnemyBase>> _enemy_list_ref;

	// ScenePlayのメンバ変数参照ポインタ	
	Shared<Player>        _player_ref = nullptr;
	Shared<dxe::Camera>   _camera_ref = nullptr;

	Shared<EnemyMover> _mover = nullptr;

	// EnemyLoader.hからの参照
	EnemyInfo        _enemyInfo_ref;


public:

	bool _isDead = false;    //敵単体の死亡フラグ
	bool _isAllDead = false; //敵クラス(最大生成数分)の死亡フラグ
	bool _canShot = false;   //弾が撃てるようになったか

	// CSVからロード-----------------------
	int           _id{};
	int           _hp{};
	float      _scale{};
	std::string _name{};
	// ------------------------------------
		
protected:

	int        _score{};
	int        _elapsed{};
	int        _life_time_duration{};
	int        _move_pattern_id{};  //移動パターン

	float      _speed{};
	float      _angle{}; // 自分自身の現在向いている方向の角度
	float      _angle_to_player {}; // 自分とプレイヤーの角度差分

	bool addedRandVal_posX = false;

	int _int_time{};  // 出現時間

	int _stop_time{}; // 停止時間

	int _shot_time{}; // 何秒間発射し続けるか

	int shot_count{}; // 弾が打てるようになってからのカウント

	int _life_timer{}; // 生成時に時間カウントを開始し、寿命を超えたら消滅

	int _life_time_limit{}; // 敵の寿命。タイマーがこの値を超えたら敵が消滅
};