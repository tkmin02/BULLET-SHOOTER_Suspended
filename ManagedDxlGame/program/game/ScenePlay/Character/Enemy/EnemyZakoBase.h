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
	// �v���C���[�֏ƎˁA�ǐՂȂ�
	virtual void ShotStraightBullet(std::list<Shared<EnemyBullet>> bullet) {};

	virtual void UpdateStraightBullet(const float delta_time) {}

	virtual void UpdateHomingBullet(const float delta_time) {}
	// �v���C���[�֏ƎˁA�p�x�����t���Œǐ�
	virtual void ShotHomingBullet() {}

public:

	static Shared<dxe::Particle> _explode_particle;

	bool     _isAllDead = false; //�G�N���X(�ő吶������)�̎��S�t���O
	bool     _canShotStraightBullet = true;   // ���s�e�����Ă��Ԃ�
	bool     _canShotHomingBullet = true;   // ���s�e�����Ă�悤�ɂȂ�����

	// CSV���烍�[�h-----------------------
	int      _hp{};
	int      _maxTotalEnemySpawnCount{};
	int      _bulletFireInterval{};
	int      _bulletMoveSpeed{};
	float    _reloadTimeInterval{};

protected:

	std::list<Shared<EnemyZakoBase>> _enemy_list_ref;
};