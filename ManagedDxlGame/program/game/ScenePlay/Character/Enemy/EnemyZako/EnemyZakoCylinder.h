#pragma once
#include "../EnemyBase.h"
#include "../../../../../library/tnl_sequence.h"
#include "../../../Bullet/Enemy/EnemyBullet.h"
#include "../../../../Loader/CsvLoader.h"

class HomingBullet;


class EnemyZakoCylinder : public EnemyBase
{
public:

	EnemyZakoCylinder(){}

	explicit EnemyZakoCylinder(tnl::Vector3){}

	EnemyZakoCylinder(const EnemyZakoInfo& info) {}

	EnemyZakoCylinder(std::vector<Shared<EnemyBase>>& list) {}

	EnemyZakoCylinder(std::vector<Shared<EnemyZakoInfo>>& enemyList) {}

	// �ϊ��R���X�g���N�^
	EnemyZakoCylinder(const EnemyZakoInfo& info, const Shared<Player>& player, const Shared<dxe::Camera>& camera);
	

private:

	// �e�n----------------------------------------------------------------

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

	static std::list<Shared<StraightBullet>> _straight_bullets_zakoCylinder;
	static std::list<Shared<HomingBullet>> _homing_bullets_zakoCylinder;

private:

	tnl::Vector3 prev_pos;

	int straight_bullet_count;
	int homing_bullet_count;

	const int INIT_BULLET_NUM = 3;

	const float _IDLE_DISTANCE = 500.0f;
	const float _ATTACK_DISTANCE = 450.0f;
	const float BULLET_SPEED = 200.0f;
};