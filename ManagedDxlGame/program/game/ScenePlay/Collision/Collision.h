#pragma once
#include "../../DxLibEngine.h"
#include "Object/CollisionObject.h"
#include "Pair/PairObject.h"

class Player;
class PlayerBullet;
class EnemyBase;
class StraightBullet;
class EnemyZakoBox;

class Collision {

public:

	void CheckCollision_PlayerBulletAndEnemy(Shared<PlayerBullet> meshA, Shared<EnemyBase> meshB, tnl::Vector3 collisionSize, tnl::Vector3 prev_pos);

	void CheckCollision_PlayerAndEnemy(Shared<Player> meshA, Shared<EnemyBase> meshB, tnl::Vector3 collisionSize, tnl::Vector3 prev_pos);

	void CheckCollision_EnemyBulletAndPlayer(Shared<StraightBullet> bullet, Shared<Player> player, tnl::Vector3 collisionSize, tnl::Vector3 prev_pos);

	void DestroyMeshByHit(Shared<dxe::Mesh> meshA, Shared<dxe::Mesh> meshB, tnl::Vector3 collisionSize, tnl::Vector3 prev_pos);


	tnl::Vector3 COLLISION_SIZE_ZAKOBOX = { 30,30,30 };
};
