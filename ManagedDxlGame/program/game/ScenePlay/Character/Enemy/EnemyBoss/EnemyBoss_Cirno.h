#pragma once
#include "../EnemyBase.h"

class BulletHell;

class EnemyBoss_Cirno : public EnemyBase
{
public:

	EnemyBoss_Cirno() {}
	explicit EnemyBoss_Cirno(Shared<EnemyBoss_Cirno> boss) {}
	EnemyBoss_Cirno(const EnemyBossInfo& info, const Shared<Player>& player, const Shared<dxe::Camera>& camera);


	void SetMeshInfo() override;

	void AttackPlayer(const float& delta_time) override;

	bool Update(float delta_time) override;

	void Render(Shared<dxe::Camera> camera) override;

	void InitBulletHellInstance() override;

	void DoRoutineMoves(float delta_time) override;

	void RenderBossSpellCardName() override;


private:

	Shared<BulletHell> _bulletHell = nullptr;

private:

	static std::list<Shared<EnemyBullet>> _bullet_patchouli;

	int _MAX_HP;
};