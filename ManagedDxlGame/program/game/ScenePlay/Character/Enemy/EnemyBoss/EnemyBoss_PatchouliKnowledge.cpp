#include "EnemyBoss_PatchouliKnowledge.h"
#include "../../../Bullet/Enemy/BulletHell.h"

std::list<Shared<EnemyBullet>> EnemyBoss_PatchouliKnowledge::_bullet_patchouli;


EnemyBoss_PatchouliKnowledge::EnemyBoss_PatchouliKnowledge(const EnemyBossInfo& info, const Shared<Player>& player, const Shared<dxe::Camera>& camera)
	: EnemyBase(info, player, camera) {

	collide_size = { 50,50,50 };

}


void EnemyBoss_PatchouliKnowledge::SetMeshInfo() {

	_mesh = dxe::Mesh::CreateSphereMV(50);
	_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/bossTexture/PatchouliKnowledge.jpg"));

	_mesh->pos_ = { 0, 0, 0 };
	_mesh->scl_ = { 1.0f, 1.0f, 1.0f };
}


void EnemyBoss_PatchouliKnowledge::InitBulletHellInstance() {

	_bulletHell = std::make_shared<BulletHell>(_mesh,_bullet_patchouli);
}


void EnemyBoss_PatchouliKnowledge::AttackPlayer(const float& delta_time) {

	_bulletHell->ShotBulletHell_SilentSerena(delta_time);
	UpdateBulletHell(delta_time);
}



void EnemyBoss_PatchouliKnowledge::DoRoutineMoves(float delta_time) {

	LookAtPlayer();

	AttackPlayer(delta_time);
}


void EnemyBoss_PatchouliKnowledge::Render(Shared<dxe::Camera> camera) {

	if (_isDead) return;

	_mesh->render(camera);

	_bulletHell->Render(camera);

	ShowHpGage_EnemyBoss();
}


void EnemyBoss_PatchouliKnowledge::UpdateBulletHell(const float delta_time) {
	_bulletHell->Update(delta_time);
}


bool EnemyBoss_PatchouliKnowledge::Update(float delta_time) {

	if (_isDead) return false;

	DoRoutineMoves(delta_time);
	return true;
}