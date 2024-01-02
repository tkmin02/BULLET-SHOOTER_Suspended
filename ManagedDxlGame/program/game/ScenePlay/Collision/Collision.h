#pragma once
#include "../../DxLibEngine.h"
#include "Object/CollisionObject.h"
#include "Pair/PairObject.h"


class Player;
class EnemyBase;

class Collision {

public:


	std::list<PairObject> intersect_list_;

	std::unordered_map< std::string, IntersectedCall > intersect_map_;

	template< class A, class B >
	void RegisterPairObject(A* a, B* b) {

		std::string ab_name = std::string(typeid(A).name()) + typeid(B).name();

		if (intersect_map_.find(ab_name) == intersect_map_.end()) return;

		auto intersected_call = intersect_map_[ab_name];
		intersect_list_.emplace_back(PairObject(a, b, intersected_call));

	}

	template< class A, class B >
	void RegisterIntersectedProcess(const IntersectedCall& func) {
		std::string ab_name = std::string(typeid(A).name()) + typeid(B).name();
		intersect_map_.try_emplace(ab_name, func);
	}



	void UpdateCollisionCensor(const Collision* collision) {

		for (auto li : collision->intersect_list_) {

			if (1) { // li->a_ Ç∆ li->b_ ÇÃè’ìÀîªíË
				li.intersected_call_(li.a_, li.b_);
			}
		}
	}



	void SetCollision_MeshAMeshB(Shared<dxe::Mesh> meshA, Shared<dxe::Mesh> meshB, tnl::Vector3 collisionSize, tnl::Vector3 prev_pos);
	void DestroyMeshByHit(Shared<dxe::Mesh> meshA, Shared<dxe::Mesh> meshB, tnl::Vector3 collisionSize, tnl::Vector3 prev_pos);


	tnl::Vector3 COLLISION_SIZE_ZAKOBOX = { 30,30,30 };
};
