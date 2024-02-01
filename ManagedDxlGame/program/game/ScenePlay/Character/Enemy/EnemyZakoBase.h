#pragma once
#include "EnemyBase.h"

class Player;
class CsvLoader;
class BulletHell;
class EnemyBullet;
struct EnemyZakoInfo;

class EnemyZakoBase : public EnemyBase
{
public:

	EnemyZakoBase(){}

	EnemyZakoBase(const EnemyZakoInfo& data, const Shared<Player>& player, const Shared<dxe::Camera>& camera);

	void DecreaseHP(int damage, Shared<dxe::Camera> camera);

	virtual bool ShowHpGage_EnemyZako();

protected:

	virtual void InitBulletFactoryInstance() {}

	virtual void EraseInvalidStraightBullet() {}
	// プレイヤーへ照射、追跡なし
	virtual void ShotStraightBullet(std::list<Shared<EnemyBullet>> bullet) {};

	virtual void UpdateStraightBullet(const float delta_time) {}

	virtual void UpdateHomingBullet(const float delta_time) {}
	// プレイヤーへ照射、角度制限付きで追跡
	virtual void ShotHomingBullet() {}

public:

	static Shared<dxe::Particle> _explode_particle;

	bool     _isAllDead = false; //敵クラス(最大生成数分)の死亡フラグ
	bool     _canShotStraightBullet = true;   // 直行弾が撃てる状態か
	bool     _canShotHomingBullet = true;   // 直行弾が撃てるようになったか

	// CSVからロード-----------------------
	int      _hp{};
	int      _maxTotalEnemySpawnCount{};
	int      _bulletFireInterval{};
	int      _bulletMoveSpeed{};
	float    _reloadTimeInterval{};

protected:

	std::list<Shared<EnemyZakoBase>> _enemy_list_ref;
};