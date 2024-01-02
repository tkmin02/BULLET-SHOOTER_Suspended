#include "HomingBullet.h"



void HomingBullet::Shoot() {


}



void HomingBullet::Render(Shared<dxe::Camera> _mainCamera) {


	_mesh->render(_mainCamera);
}


void HomingBullet::Update(float delta_time) {


	// プレイヤー位置と弾の進行方向の差が一定範囲内なら
	if (_to_player_angle <= tnl::PI / 4.0f) {

		_mesh->pos_.x += cos(_player_ref->_mesh->pos_.x) * _speed * delta_time;
		_mesh->pos_.y += sin(_player_ref->_mesh->pos_.y) * _speed * delta_time;
	}


	_mesh->pos_ -= _move_dir * 5;
	if (_mesh->pos_.z > -1000) _isActive = false;
}