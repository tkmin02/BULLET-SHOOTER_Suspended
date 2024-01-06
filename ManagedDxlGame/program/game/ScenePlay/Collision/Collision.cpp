#include "Collision.h"
#include "../../ScenePlay/Character/Player/Player.h"
#include "../../ScenePlay/Character/Enemy/EnemyBase.h"
#include "../Bullet/Enemy/StraightBullet.h"
#include "../Character/Enemy/EnemyZakoBox.h"
#include "../Bullet/Player/PlayerBullet.h"



void Collision::CheckCollision_PlayerBulletAndEnemy(Shared<PlayerBullet> bullet, Shared<EnemyBase> enemy, tnl::Vector3 collisionSize, tnl::Vector3 prev_pos) {

	if (tnl::IsIntersectAABB(bullet->_mesh->pos_, collisionSize, enemy->_mesh->pos_, collisionSize)) {
		tnl::GetCorrectPositionIntersectAABB(
			prev_pos, collisionSize, collisionSize, bullet->_mesh->pos_, enemy->_mesh->pos_, 1);
		bullet->_isActive = false;
	}
}


void Collision::CheckCollision_PlayerAndEnemy(Shared<Player> player, Shared<EnemyBase> enemy, tnl::Vector3 collisionSize, tnl::Vector3 prev_pos) {

	if (tnl::IsIntersectAABB(player->_mesh->pos_, collisionSize, enemy->_mesh->pos_, collisionSize)) {
		tnl::GetCorrectPositionIntersectAABB(
			prev_pos, collisionSize, collisionSize, player->_mesh->pos_, enemy->_mesh->pos_, 1);
	}
}


void Collision::CheckCollision_EnemyBulletAndPlayer(Shared<StraightBullet> bullet, Shared<Player> player, tnl::Vector3 collisionSize, tnl::Vector3 prev_pos) {

	if (tnl::IsIntersectAABB(bullet->_mesh->pos_, collisionSize, player->_mesh->pos_, collisionSize)) {
		tnl::GetCorrectPositionIntersectAABB(prev_pos, collisionSize, collisionSize, bullet->_mesh->pos_, player->_mesh->pos_, 1);
		bullet->_isActive = false;
	}
}



void Collision::DestroyMeshByHit(Shared<dxe::Mesh> meshA, Shared<dxe::Mesh> meshB, tnl::Vector3 collisionSize, tnl::Vector3 prev_pos) {



}
