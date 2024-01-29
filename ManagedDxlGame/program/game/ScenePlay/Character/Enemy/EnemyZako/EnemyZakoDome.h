#pragma once
#include "../EnemyBase.h"
#include "../../../../../library/tnl_sequence.h"
#include "../../../Bullet/Enemy/EnemyBullet.h"
#include "../../../../Loader/CsvLoader.h"


class HomingBullet;
class BulletFactory;


class EnemyZakoDome : public EnemyBase
{
public:

	EnemyZakoDome(){}

	EnemyZakoDome(const EnemyZakoInfo& info, const Shared<Player>& player, const Shared<dxe::Camera>& camera);
	
	void  InitBulletFactoryInstance() override;

private:

	// íeån----------------------------------------------------------------

	void ShotStraightBullet(const float& delta_time);

	void ReloadStraightBulletByTimer(float& reload_time_counter, const float& delta_time);

	void EraseInvalidStraightBullet() override;

	void ShotHomingBullet(const float& delta_time);


	//----------------------------------------------------------------------

	bool Update(float delta_time) override;

	void Render(Shared<dxe::Camera> camera) override;

	void SetMeshInfo() override;
	
	void DoRoutineMoves(float delta_time) override;

	void ChasePlayer(const float delta_time) override;

	void AttackPlayer(const float& delta_time) override;

public:

	static std::list<Shared<StraightBullet>> _straight_bullets_zakoDome;
	static std::list<Shared<HomingBullet>> _homing_bullets_zakoDome;

private:

	Shared<BulletFactory> _bulletFactory = nullptr;

	std::list<Shared<StraightBullet>> _straightBullet;
	std::deque<Shared<StraightBullet>>_straightBullet_queue;

private:

	tnl::Vector3 prev_pos;

	int straight_bullet_count;
	int homing_bullet_count;

	const float _IDLE_DISTANCE = 500.0f;
	const float _ATTACK_DISTANCE = 450.0f;
};