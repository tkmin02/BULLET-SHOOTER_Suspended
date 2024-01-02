#include "EnemyZakoBox.h"
#include "../../Bullet/Enemy/EnemyBullet.h"
#include "../../Bullet/Enemy/StraightBullet.h"
#include "../../EnemyMove/EnemyMover.h"
#include <functional>
#include <random>


EnemyZakoBox::EnemyZakoBox(const EnemyInfo& data, const Shared<Player>& player, const Shared<dxe::Camera>& camera)
	: EnemyBase(data, player, camera)
{
	collide_size = { 30,30,30 };
}


void EnemyZakoBox::SetMeshInfo() {


	_mesh = dxe::Mesh::CreateBox(20);
	_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/box.bmp"));
	_mesh->pos_ = { 0, 0, 0 };
	_mesh->scl_ = { 1.0f, 1.0f, 1.0f };
}


float EnemyZakoBox::GetRandomValue_Mt19337() const {


	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> rateDistribution(-1.0f, 1.0f);

	return rateDistribution(gen);
}


tnl::Vector3 EnemyZakoBox::CalcVecFromAngle(float angle) {

	tnl::Vector3 temp;

	temp.x = sin(angle);
	temp.y = -cos(angle);

	return temp;
}



float EnemyZakoBox::GetAngleBtw_EnemyAndPlayer(Shared<dxe::Mesh> enemy, Shared<Player> player) {

	//　外積・内積は２つのベクトルの相対角度とは関係がないので使わない

	float dx = player->_mesh->pos_.x - enemy->pos_.x;
	float dy = player->_mesh->pos_.y - enemy->pos_.y;

	// プレイヤーとエネミーの位置の相対角度を求める
	float angle = atan2(dy, dx);

	return angle;

}



bool EnemyZakoBox::SeqIdle(const float delta_time) {


	if (GetDistanceToPlayer() < _IDLE_DISTANCE) {

		tnl_sequence_.change(&EnemyZakoBox::SeqChasePlayer);
		TNL_SEQ_CO_END;

	}

	if (GetDistanceToPlayer() < _ATTACK_DISTANCE) {

		tnl_sequence_.change(&EnemyZakoBox::SeqAttack);
		TNL_SEQ_CO_END;

	}

	TNL_SEQ_CO_END;
}



bool EnemyZakoBox::SeqChasePlayer(const float delta_time) {

	LookAtPlayer(delta_time);

	prev_pos = _mesh->pos_;


	//_mover->forward;



	//プレイヤー追跡	 一番下に持ってくと画面が止まる
	for (auto it_me = _enemy_list_ref.begin(); it_me != _enemy_list_ref.end(); it_me++) {

		float offSet = 20.0f;
		float randVal_X = GetRandomValue_Mt19337();
		float randVal_Y = GetRandomValue_Mt19337();
		float randVal_Z = GetRandomValue_Mt19337();


		// 移動
		tnl::Vector3 direction = (_player_ref->GetPos() * 40 * delta_time) - (*it_me)->_mesh->pos_;
		direction.x += randVal_X * offSet;
		direction.y += randVal_Y * offSet;
		direction.z += randVal_Z * offSet;

		(*it_me)->_mesh->pos_ += (direction * _speed * delta_time);

		TNL_SEQ_CO_END;

	}


	//if (GetDistanceToPlayer() > _IDLE_DISTANCE)
	//{
	//	tnl_sequence_.change(&EnemyZakoBox::SeqIdle);
	//	TNL_SEQ_CO_END;

	//}
	//if (GetDistanceToPlayer() < _ATTACK_DISTANCE) {

	//	tnl_sequence_.change(&EnemyZakoBox::SeqAttack);
	//	TNL_SEQ_CO_END;

	//}

	//TNL_SEQ_CO_END;
}


bool EnemyZakoBox::SeqAttack(const float delta_time) {


	tnl_sequence_.invokeRepeating(&EnemyZakoBox::ShotStraightBullet, 3.0f, 1.0f);

	TNL_SEQ_CO_END;
}


std::list<Shared<StraightBullet>> EnemyZakoBox::InitStraightBullet() {

	std::list<Shared<StraightBullet>> temp;

	for (int row = 0; row < INIT_BULLET_NUM; ++row) {

		auto bullet = temp.front();

		temp.pop_front();

		// 発射位置を自分の正面に設定
		tnl::Vector3 move_dir = tnl::Vector3::TransformCoord({ 0,0,1 }, _mesh->rot_);


		tnl::Vector3 spawn_pos = _mesh->pos_;
		spawn_pos.x += _mesh->rot_.x;
		spawn_pos.y += _mesh->rot_.y;
		spawn_pos.z += _mesh->rot_.z;
		spawn_pos.z -= 30;

		bullet->_speed = BULLET_SPEED;

		bullet->_mesh->pos_ = spawn_pos;
		bullet->_move_dir = move_dir;


		temp.emplace_back(std::make_shared<StraightBullet>(bullet));
	}

	return std::move(temp);
}



void EnemyZakoBox::ShotStraightBullet() {




	if(_straight_bullets_e.empty())	_straight_bullets_e = InitStraightBullet();


}





void EnemyZakoBox::LookAtPlayer(const float delta_time) {

	tnl::Vector3 direction = (_player_ref->GetPos() * 40 * delta_time) - _mesh->pos_;

	float angle = atan2(direction.x, direction.z);

	_mesh->rot_ = tnl::Quaternion::RotationAxis({ 0,1,0 }, angle);

}


void EnemyZakoBox::DebugInfo() {

	DrawFormatString(10, 0, -1, "BoxPos");
	DrawFormatString(10, 15, -1, "%f", _mesh->pos_.x);
	DrawFormatString(10, 35, -1, "%f", _mesh->pos_.y);
	DrawFormatString(10, 55, -1, "%f", _mesh->pos_.z);


	DrawFormatString(10, 80, -1, "BoxRot");
	DrawFormatString(10, 100, -1, "%f", _mesh->rot_.x);
	DrawFormatString(10, 120, -1, "%f", _mesh->rot_.y);
	DrawFormatString(10, 140, -1, "%f", _mesh->rot_.z);
}

void EnemyZakoBox::SetAndShotBullet(const float delta_time) {

	auto it = _straight_bullets_e.begin();

		while (it != _straight_bullets_e.end()) {

			(*it)->Update(delta_time);
			if (!(*it)->_isActive) {
				it = _straight_bullets_e.erase(it);
				continue;
			}
			it++;
		}
}


bool EnemyZakoBox::Update(float delta_time) {

	SetAndShotBullet(delta_time);

	tnl_sequence_.update(delta_time);

	return true;
}



void EnemyZakoBox::Render(Shared<dxe::Camera> camera) {

	_mesh->render(camera);

	for (auto blt : _straight_bullets_e) {
		blt->Render(camera);
	}

	DebugInfo();
}
