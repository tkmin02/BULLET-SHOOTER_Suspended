#pragma once
#include <functional>
#include "../Character/Enemy/EnemyBase.h"


// “G‚Ì“®‚«‚ð’è‹`‚·‚éƒNƒ‰ƒX

class EnemyMover
{
public:

	EnemyMover();

	EnemyMover(std::vector<std::function<void(EnemyMover*, Shared<EnemyBase>)>> move){}

	EnemyMover(Shared<EnemyBase> enemy){}

	~EnemyMover() = default;

	void Move(Shared<EnemyBase> enemy){}

	void MoveForward(Shared<EnemyBase> enemy);
	void MoveBack(Shared<EnemyBase> enemy);
	void MoveAbove(Shared<EnemyBase> enemy);
	void MoveBelow(Shared<EnemyBase> enemy);
	void MoveLeft(Shared<EnemyBase> enemy);
	void MoveRight(Shared<EnemyBase> enemy);

	void Move_ChasePlayer(Shared<EnemyBase> enemy);


	void SetMovePatterns();

public:

	typedef void(EnemyMover::* MOVE_FUNC)(Shared<EnemyBase> enemy);
	std::vector<std::function<void(EnemyMover* , Shared<EnemyBase>)>> _movePattern;

	MOVE_FUNC forward = &EnemyMover::MoveForward;
	MOVE_FUNC back = &EnemyMover::MoveBack;
	MOVE_FUNC above = &EnemyMover::MoveAbove;
	MOVE_FUNC below = &EnemyMover::MoveBelow;
	MOVE_FUNC left = &EnemyMover::MoveLeft;
	MOVE_FUNC right = &EnemyMover::MoveRight;
	MOVE_FUNC chase_player = &EnemyMover::Move_ChasePlayer;
};