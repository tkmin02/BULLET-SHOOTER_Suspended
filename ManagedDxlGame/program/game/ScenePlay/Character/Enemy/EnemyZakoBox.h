#pragma once
#include "EnemyBase.h"
#include "../../../../library/tnl_sequence.h"
#include "../../Collision/Object/CollisionObject.h"
#include "../../Bullet/Enemy/EnemyBullet.h"
#include "../../../Loader/EnemyLoader.h"


class EnemyZakoBox : public EnemyBase
{
public:

	EnemyZakoBox(){}

	explicit EnemyZakoBox(tnl::Vector3){}

	EnemyZakoBox(const EnemyInfo& info) {}

	// 変換コンストラクタ
	EnemyZakoBox(const EnemyInfo& info, const Shared<Player>& player, const Shared<dxe::Camera>& camera);


private:


	// 弾系----------------------------------------------------------------


	void ShotStraightBullet() override;

	void SetAndShotBullet(const float delta_time);


	//----------------------------------------------------------------------

	tnl::Vector3 CalcVecFromAngle(float angle) override;

	float GetAngleBtw_EnemyAndPlayer(Shared<dxe::Mesh> enemy, Shared<Player> player) override;

	float GetRandomValue_Mt19337() const override;

	void LookAtPlayer(const float delta_time) override;

	void DebugInfo();

	bool Update(float delta_time) override;

	void Render(Shared<dxe::Camera> camera) override;

	void SetMeshInfo() override;

	void Clone() override { _mesh->createClone(); }
	
	void DoRoutineMoves(float delta_time) override;

	void ChasePlayer(const float delta_time) override;

	void AttackPlayer(float delta_time) override;


private:

	std::list<Shared<StraightBullet>> _straight_bullets_e;
	tnl::Vector3 prev_pos;

	const int INIT_BULLET_NUM = 6;

	const float _IDLE_DISTANCE = 270.0f;
	const float _ATTACK_DISTANCE = 250.0f;
	const float BULLET_SPEED = 200.0f;
};