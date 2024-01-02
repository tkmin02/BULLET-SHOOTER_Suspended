#include "Collision.h"
#include "../../ScenePlay/Character/Player/Player.h"
#include "../../ScenePlay/Character/Enemy/EnemyBase.h"



void Collision::SetCollision_MeshAMeshB(Shared<dxe::Mesh> meshA, Shared<dxe::Mesh> meshB, tnl::Vector3 collisionSize, tnl::Vector3 prev_pos) {

	// “–‚½‚è”»’è
	if (tnl::IsIntersectAABB(meshA->pos_, collisionSize, meshB->pos_, collisionSize)) {

			tnl::GetCorrectPositionIntersectAABB
			(
				prev_pos, collisionSize, collisionSize, meshA->pos_, meshB->pos_, 2
			);

	}
}



void Collision::DestroyMeshByHit(Shared<dxe::Mesh> meshA, Shared<dxe::Mesh> meshB, tnl::Vector3 collisionSize, tnl::Vector3 prev_pos) {



}
