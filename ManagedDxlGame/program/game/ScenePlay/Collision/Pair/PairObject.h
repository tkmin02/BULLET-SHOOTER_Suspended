#pragma once
#include "../Object/CollisionObject.h"


class PairObject {
public:
	PairObject() {}
	PairObject(CollisionObject* a, CollisionObject* b, IntersectedCall call)
		: a_(a)
		, b_(b)
		, intersected_call_(call)
	{}
	CollisionObject* a_;
	CollisionObject* b_;
	IntersectedCall intersected_call_;
};


