#pragma once
#include "../EnemyBase.h"
#include "../../../../../library/tnl_sequence.h"
#include "../../../Bullet/Enemy/EnemyBullet.h"
#include "../../../../Loader/CsvLoader.h"


class HomingBullet;


class EnemyZakoDome : public EnemyBase
{
public:

	EnemyZakoDome(){}

	explicit EnemyZakoDome(tnl::Vector3){}

	EnemyZakoDome(const EnemyZakoDome& info) {}

	EnemyZakoDome(std::vector<Shared<EnemyBase>>& list) {}

	EnemyZakoDome(std::vector<Shared<EnemyZakoInfo>>& enemyList) {}

	// 変換コンストラクタ
	EnemyZakoDome(const EnemyZakoInfo& info, const Shared<Player>& player, const Shared<dxe::Camera>& camera);
	

private:

	// 弾系----------------------------------------------------------------

	void UpdateStraightBullet(const float delta_time) override;

	void InitStraightBullet() override;

	void UpdateHomingBullet(const float delta_time) override;

	void InitHomingBullet() override;

	//----------------------------------------------------------------------

	tnl::Vector3 CalcVecFromAngle(float angle) override;

	float GetAngleBtw_EnemyAndPlayer(Shared<dxe::Mesh> enemy, Shared<Player> player) override;

	bool Update(float delta_time) override;

	void Render(Shared<dxe::Camera> camera) override;

	void SetMeshInfo() override;

	void Clone() override { _mesh->createClone(); }
	
	void DoRoutineMoves(float delta_time) override;

	void ChasePlayer(const float delta_time) override;

	void AttackPlayer(const float& delta_time) override;

public:

	static std::list<Shared<StraightBullet>> _straight_bullets_zakoDome;
	static std::list<Shared<HomingBullet>> _homing_bullets_zakoDome;

private:

	tnl::Vector3 prev_pos;

	int straight_bullet_count;
	int homing_bullet_count;


	const int INIT_BULLET_NUM = 6;

	const float _IDLE_DISTANCE = 500.0f;
	const float _ATTACK_DISTANCE = 450.0f;
	const float BULLET_SPEED = 200.0f;
};