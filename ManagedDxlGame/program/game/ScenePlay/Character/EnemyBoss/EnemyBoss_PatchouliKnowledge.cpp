#include "EnemyBoss_PatchouliKnowledge.h"
#include "../../Bullet/Enemy/BulletHell.h"


EnemyBoss_PatchouliKnowledge::EnemyBoss_PatchouliKnowledge(const EnemyBossInfo& info, const Shared<Player>& player, const Shared<dxe::Camera>& camera)
	: EnemyBase(info, player, camera)  {


	_bulletHell = std::make_shared<BulletHell>();
}


void EnemyBoss_PatchouliKnowledge::SetMeshInfo() {

	// CSV‚Ìƒf[ƒ^‚É‚æ‚Á‚ÄðŒ•ªŠò

	_mesh = dxe::Mesh::CreateSphere(50);
	_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/bossTexture/PatchouliKnowledge.jpg"));

	_mesh->pos_ = { 30, 30, 30 };
	_mesh->scl_ = { 1.0f, 1.0f, 1.0f };
}



void EnemyBoss_PatchouliKnowledge::AttackPlayer(float delta_time) {

	

}





void EnemyBoss_PatchouliKnowledge::LookAtPlayer(const float delta_time) {

	tnl::Quaternion q = tnl::Quaternion::RotationAxis({ 0,1,0 }, _mainCamera_ref->axis_y_angle_);
	tnl::Vector3 xz = tnl::Vector3::TransformCoord({ 0,0,1 }, q);
	tnl::Vector3 local_axis_y = tnl::Vector3::Cross({ -1,0,0 }, xz);

	_mesh->rot_ = tnl::Quaternion::LookAt(_mesh->pos_, _player_ref->GetPos(), local_axis_y);

}


void EnemyBoss_PatchouliKnowledge::Render(Shared<dxe::Camera> camera) {

	if (_isDead) return;

	_mesh->render(camera);

	ShowHpGage_EnemyBoss();

}


bool EnemyBoss_PatchouliKnowledge::Update(float delta_time) {

	if (_isDead) return false;


	return true;
}