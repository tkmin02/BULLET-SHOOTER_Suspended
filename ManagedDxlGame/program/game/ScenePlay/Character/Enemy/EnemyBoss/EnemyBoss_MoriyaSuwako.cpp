#include "EnemyBoss_MoriyaSuwako.h"
#include "../../../Bullet/Enemy/BulletHell.h"


EnemyBoss_MoriyaSuwako::EnemyBoss_MoriyaSuwako(const EnemyBossInfo& info, const Shared<Player>& player, const Shared<dxe::Camera>& camera)
	: EnemyBase(info, player, camera)  {

	collide_size = { 50,50,50 };
}


void EnemyBoss_MoriyaSuwako::SetMeshInfo() {

	// CSV‚Ìƒf[ƒ^‚É‚æ‚Á‚ÄðŒ•ªŠò


	_mesh = dxe::Mesh::CreateSphereMV(50);
	_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/box.bmp"));

	_mesh->pos_ = { 30, 30, 30 };
	_mesh->scl_ = { 1.0f, 1.0f, 1.0f };
}



void EnemyBoss_MoriyaSuwako::AttackPlayer(const float& delta_time) {

	_bulletHell->ShotBulletHell_KeroChanStandsFirm_AgainstTheStorm(delta_time);

}




void EnemyBoss_MoriyaSuwako::Render(Shared<dxe::Camera> camera) {

	if (_isDead) return;

	_mesh->render(camera);

	ShowHpGage_EnemyBoss();
}


bool EnemyBoss_MoriyaSuwako::Update(float delta_time) {

	if (_isDead) return false;


	return true;
}