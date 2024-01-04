#include "EnemyBase.h"
#include "../../Bullet/Enemy/StraightBullet.h"


EnemyBase::EnemyBase(const EnemyInfo& data, const Shared<Player>& player, const Shared<dxe::Camera>& camera) {

	_enemyInfo_ref = data;

	_id = data._id;
	_name = data._name;
	_hp = data._hp;
	_scale = data._scale;
	_speed = data._speed;



	_player_ref = player;
	_mainCamera_ref = camera;
}



void EnemyBase::Initialize() {

	SetMeshInfo();

}


void EnemyBase::InitEnemyMove() {
	
}



float EnemyBase::GetDistanceToPlayer() {

	tnl::Vector3 dis = _player_ref->GetPos() - _mesh->pos_;

	return std::sqrt(dis.x * dis.x + dis.y * dis.y + dis.z * dis.z);
}



bool EnemyBase::Update(float delta_time) {

	//_mover->Move(static_cast<Shared<EnemyBase>>(this));
	_elapsed++;

	// Œo‰ßŽžŠÔ‚ªŽõ–½‚ð’´‚¦‚½‚ç false
	return _elapsed > _life_time_duration ? false : true;
}
