#include "EnemyMover.h"
#include "../Character/Enemy/EnemyBase.h"


EnemyMover::EnemyMover() {

	SetMovePatterns();
}




void EnemyMover::MoveLeft(Shared<EnemyBase> enemy) {



}


void EnemyMover::MoveRight(Shared<EnemyBase> enemy) {


}


void EnemyMover::MoveAbove(Shared<EnemyBase> enemy) {



}



void EnemyMover::MoveBelow(Shared<EnemyBase> enemy) {


}


void EnemyMover::MoveForward(Shared<EnemyBase> enemy) {


}


void EnemyMover::MoveBack(Shared<EnemyBase> enemy) {


}

void EnemyMover::Move_ChasePlayer(Shared<EnemyBase> enemy) {


}


void EnemyMover::SetMovePatterns() {

	_movePattern.push_back(forward);
	_movePattern.push_back(back);
	_movePattern.push_back(above);
	_movePattern.push_back(below);
	_movePattern.push_back(left);
	_movePattern.push_back(right);
	_movePattern.push_back(chase_player);

}