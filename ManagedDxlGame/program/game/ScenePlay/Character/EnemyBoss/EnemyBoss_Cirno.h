#pragma once
#include "../Enemy/EnemyBase.h"

class BulletHell;

class EnemyBoss_Cirno : public EnemyBase
{
public:

	EnemyBoss_Cirno() {}
	EnemyBoss_Cirno(Shared<EnemyBoss_Cirno> boss) {}
	EnemyBoss_Cirno(const EnemyBossInfo& info, const Shared<Player>& player, const Shared<dxe::Camera>& camera);


	void SetMeshInfo() override;

	void AttackPlayer(float delta_time) override;

	//bool ShowHpGage_EnemyZako() override;

	void LookAtPlayer(const float delta_time) override;

	bool Update(float delta_time) override;

	void Render(Shared<dxe::Camera> camera) override;


public:

	Shared<BulletHell> _bulletHell = nullptr;
};

