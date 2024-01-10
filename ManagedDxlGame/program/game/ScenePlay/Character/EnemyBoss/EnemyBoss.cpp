#include "EnemyBoss.h"
#include "../../Bullet/Enemy/BulletHell.h"


EnemyBoss::EnemyBoss(const EnemyBossInfo& info, const Shared<Player>& player, const Shared<dxe::Camera>& camera) 
	: EnemyBase(info, player, camera) , _MAX_HP(info._hp) {

	SetMeshInfo();

	_bulletHell = std::make_shared<BulletHell>();
}


void EnemyBoss::SetMeshInfo() {

	// CSV‚Ìƒf[ƒ^‚É‚æ‚Á‚ÄðŒ•ªŠò


	_mesh = dxe::Mesh::CreateCylinder(20,20);
	_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/box.bmp"));

	_mesh->pos_ = { 30, 30, 30 };
	_mesh->scl_ = { 1.0f, 1.0f, 1.0f };
}



void EnemyBoss::AttackPlayer(float delta_time) {

	

}



bool EnemyBoss::ShowHpGage(int hp) {

	if (_hp <= 0) {
		return false;
	}


	float x1 = 430;
	float x2 = 860;

	int gage_width = abs(x2 - x1);

	float average = (_MAX_HP > 0) ? gage_width / _MAX_HP : 0;

	x2 = x1 + average * _hp;


	DrawBoxAA(x1, DXE_WINDOW_HEIGHT - 30, 860, DXE_WINDOW_HEIGHT - 10, GetColor(255, 255, 255), true);
	DrawBoxAA(x1, DXE_WINDOW_HEIGHT-30, x2, DXE_WINDOW_HEIGHT -10, GetColor(255, 0, 0), true);

	return true;
}



void EnemyBoss::LookAtPlayer(const float delta_time) {

	tnl::Quaternion q = tnl::Quaternion::RotationAxis({ 0,1,0 }, _mainCamera_ref->axis_y_angle_);
	tnl::Vector3 xz = tnl::Vector3::TransformCoord({ 0,0,1 }, q);
	tnl::Vector3 local_axis_y = tnl::Vector3::Cross({ -1,0,0 }, xz);

	_mesh->rot_ = tnl::Quaternion::LookAt(_mesh->pos_, _player_ref->GetPos(), local_axis_y);

}


void EnemyBoss::Render(Shared<dxe::Camera> camera) {

	if (_isDead) return;

	_mesh->render(camera);

	ShowHpGage(_hp);

}


bool EnemyBoss::Update(float delta_time) {

	if (_isDead) return false;


	return true;
}



