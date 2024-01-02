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

	TNL_CO_SEQUENCE(EnemyZakoBox, &EnemyZakoBox::SeqIdle);

	bool SeqIdle(const float delta_time);

	bool SeqChasePlayer(const float delta_time);

	bool SeqAttack(const float delta_time) ;

	// 弾系----------------------------------------------------------------


	void ShotStraightBullet() override;

	void SetAndShotBullet(const float delta_time);

	std::list<Shared<StraightBullet>> InitStraightBullet() override;


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
	

private:

	std::list<Shared<StraightBullet>> _straight_bullets_e;
	tnl::Vector3 prev_pos;

	const int INIT_BULLET_NUM = 6;

	const float _IDLE_DISTANCE = 400.0f;
	const float _ATTACK_DISTANCE = 300.0f;
	const float BULLET_SPEED = 30.0f;

};

