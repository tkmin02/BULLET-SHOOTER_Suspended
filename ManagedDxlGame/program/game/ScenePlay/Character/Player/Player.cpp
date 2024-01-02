#include "Player.h"
#include "../../Bullet/Player/PlayerBullet.h"
#include "../../Sky/SkyBox.h"
#include "../../ScenePlay.h"

// CreateClone()

// �������̃I�u�W�F�N�g�̕`������鎞�̒���

//�@��ɕs�����ȃI�u�W�F�N�g��S�ĕ`�悵�Ă���Ō�ɔ������̃I�u�W�F�N�g��`�悷��
//�@�����łȂ��ƁA�I�u�W�F�N�g���d�Ȃ������ɔ������̃I�u�W�F�N�g����s�����ȃI�u�W�F�N�g�������Č����Ȃ�
//�@�܂��A�������ȃI�u�W�F�N�g�ǂ����ł���΁A�J�������狗�����������ɐ�ɕ`�悷��


Player::Player(Shared<dxe::Camera> camera_ref) {

	_mesh = dxe::Mesh::CreateSphere(18, 10, 10, false);
	_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/pexels-mikke-house-518917.copy.jpg"));
	_mesh->scl_ = { 1.0f, 1.0f, 1.0f };
	_mesh->pos_ = { 0, 100, -300 };


	_mesh->setBlendMode(DX_BLENDMODE_ADD);
	_mesh->setAlpha(0.1f);

	_mainCamera_ref = camera_ref;
}



void Player::SetEnemiesListRef_ClassP(std::list<Shared<EnemyBase>> enemies_list_ref) {

	_enemies_list_ref = std::move(enemies_list_ref);
}



void Player::ControlPlayerMove() {

	// ������
	if (tnl::Input::IsKeyDown(eKeys::KB_A) && !_mainCamera_ref->follow) {

		move_vel_ -= tnl::Vector3::TransformCoord({ 1.0f, 0, 0 }, rot_y_);

		NormalizeCameraSpeed();
	}

	// �E����
	if (tnl::Input::IsKeyDown(eKeys::KB_D) && !_mainCamera_ref->follow) {

		move_vel_ += tnl::Vector3::TransformCoord({ 1.0f, 0, 0 }, rot_y_);

		NormalizeCameraSpeed();
	}


	// �����
	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {

		move_vel_ += tnl::Vector3::TransformCoord({ 0, 1.0f, 0.1f }, rot_y_);
		_mesh->pos_.z += moveSpeed;

		NormalizeCameraSpeed();
	}


	// ������
	if (tnl::Input::IsKeyDown(eKeys::KB_S)) {

		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {

			move_vel_ -= tnl::Vector3::TransformCoord({ 0, 1.0f, 0.1f }, rot_y_);
			_mesh->pos_.z -= 5.0f;
		}
		else {

			move_vel_ -= tnl::Vector3::TransformCoord({ 0, 1.0f, 0.1f }, rot_y_);
			_mesh->pos_.z -= moveSpeed;
		}

		NormalizeCameraSpeed();
	}
}



void Player::MoveForward(const float deltaTime) {

	if (tnl::Input::IsKeyDown(eKeys::KB_SPACE))

		_mesh->pos_ += tnl::Vector3::TransformCoord(
			{ 0,0,2 }, _mesh->rot_) * _forward_velocity * deltaTime * 200;
}



float Player::GetDistanceToEnemy(const float& e_x, const float& e_y, const float& e_z) {

	tnl::Vector3 enemy_pos = { e_x,e_y,e_z };
	tnl::Vector3 dis = enemy_pos - _mesh->pos_;

	return std::sqrt(dis.x * dis.x + dis.y * dis.y + dis.z * dis.z);
}



float Player::GetAngleBtw_PlayerAndEnemy(Shared<dxe::Mesh> enemy) {

	//�@�O�ρE���ς͂Q�̃x�N�g���̑��Ίp�x�Ƃ͊֌W���Ȃ��̂Ŏg��Ȃ�

	float dx = enemy->pos_.x - _mesh->pos_.x;
	float dz = enemy->pos_.z - _mesh->pos_.z;

	// �v���C���[�ƃG�l�~�[�̈ʒu�̑��Ίp�x�����߂�
	float angle = atan2(dz, dx);

	return angle;
}



const tnl::Vector3 Player::GetTargetsScreenCoordinates(const float& x, const float& y, const float& z) {

	tnl::Vector3 temp = { x,y,z };

	return temp;
}



void Player::ChangeTarget_ByMouseWheel() {


	int wheel = tnl::Input::GetMouseWheel();

	// �}�E�X�z�C�[���̓��͂ɉ����ēG�̃C���f�b�N�X�𑝌�
	if (wheel > 0) {
		_enemy_index++;
		if (_enemy_index >= _enemies_list_ref.size()) {
			_enemy_index = 0;
		}
	}
	else if (wheel < 0) {
		_enemy_index--;
		if (_enemy_index < 0) {
			_enemy_index = _enemies_list_ref.size() - 1;
		}
	}

	// �C���f�b�N�X���u����Ă���G�̂݃C�e���[�^�[�Ŏ擾
	auto it = std::next(_enemies_list_ref.begin(), _enemy_index);

	if (_mainCamera_ref->isShowTargetPointer) {

		tnl::Vector3 enemy_pos = (*it)->_mesh->pos_;

		// �X�N���[�����W�֕ϊ�
		tnl::Vector3 screen_pos = tnl::Vector3::ConvertToScreen
		(
			{ enemy_pos.x, enemy_pos.y, enemy_pos.z }
			, DXE_WINDOW_WIDTH
			, DXE_WINDOW_HEIGHT
			, _mainCamera_ref->view_
			, _mainCamera_ref->proj_
		);


		// �Ǐ]�|�C���^�[�`��
		GetTargetsScreenCoordinates(enemy_pos.x, enemy_pos.y, enemy_pos.z);
		DrawCircleAA(screen_pos.x, screen_pos.y, 5, 10, GetColor(255, 0, 0), 1, 1);

		DrawFormatString(130, 0, -1, "enemy_index");
		DrawFormatString(150, 15, -1, "%d", _enemy_index);
	}
}


void Player::ConstraintMovableCoords(const float& enemy_x, const float& enemy_y, const float& enemy_z) {


	if ( // �E��������
		abs(enemy_x - _mesh->pos_.x) > 225 &&
		_mesh->pos_.x > 0 &&
		!tnl::Input::IsKeyDown(eKeys::KB_A)
		)
	{
		_mesh->pos_.x = 225;
	}

	if ( // ����������
		abs(enemy_x - _mesh->pos_.x) > 225 &&
		_mesh->pos_.x < 0 &&
		!tnl::Input::IsKeyDown(eKeys::KB_D)
		)
	{
		_mesh->pos_.x = -140;
	}


	if ( // ���������
		abs(enemy_y - _mesh->pos_.y) > 240 &&
		_mesh->pos_.y > 0 &&
		!tnl::Input::IsKeyDown(eKeys::KB_S)
		)
	{
		_mesh->pos_.y = 240;
	}


	if ( // ����������
		abs(enemy_y - _mesh->pos_.y) > 165 &&
		_mesh->pos_.y < 0 &&
		!tnl::Input::IsKeyDown(eKeys::KB_W)
		)
	{
		_mesh->pos_.y = -80;
	}


	if (abs(enemy_z - _mesh->pos_.z) > 370)  _mesh->pos_.z = 370;
}





void Player::ActivateDarkSoulsCamera() {

	float to_target_distance_ = 80;

	// Space�ŒǏ]�J����ON

	ChangeTarget_ByMouseWheel();


	for (auto it_eneList_ref = _enemies_list_ref.begin(); it_eneList_ref != _enemies_list_ref.end(); it_eneList_ref++) {

		float dis_player_enemy = ((*it_eneList_ref)->_mesh->pos_ - _mesh->pos_).length();

		if (dis_player_enemy < 500) {

			if (_mainCamera_ref->follow && (*it_eneList_ref) != nullptr) {

				tnl::Vector3 _camera_offset = { 0, 110, -150 };


				// �J�������v���C���[�ƓG�̒��Ԓn�_�ɌŒ�
				_mainCamera_ref->target_ = (_mesh->pos_ + (*it_eneList_ref)->_mesh->pos_) / 2;


				// �J�����̈ʒu = �v���C���[���W + (normalized(�v���C���[���W - �G���W) * �J�����ƃv���C���[�̍���)
				// �������A�P���Ƀv���C���[�̍��W���g���ƃv���C���[�ƃG�l�~�[���d�Ȃ��Ă��܂����߁A�������g��

				 //������
				if (tnl::Input::IsKeyDown(eKeys::KB_A)) {

					tnl::Quaternion q = tnl::Quaternion::RotationAxis({ 0,1,0 }, _mainCamera_ref->axis_y_angle_);

					tnl::Vector3 xz = tnl::Vector3::TransformCoord({ 0,0,1 }, q);

					tnl::Vector3 local_axis_x = tnl::Vector3::Cross({ 0,1,0 }, xz);

					q *= tnl::Quaternion::RotationAxis(local_axis_x, _mainCamera_ref->axis_x_angle_);

					_mesh->pos_ = _mainCamera_ref->target_ + tnl::Vector3::TransformCoord({ 0, 0, -to_target_distance_ }, q);

					_mainCamera_ref->axis_y_angle_ += tnl::ToRadian(1);
				}

				// �E����
				if (tnl::Input::IsKeyDown(eKeys::KB_D)) {

					tnl::Quaternion q = tnl::Quaternion::RotationAxis({ 0,1,0 }, _mainCamera_ref->axis_y_angle_);

					tnl::Vector3 xz = tnl::Vector3::TransformCoord({ 0,0,1 }, q);

					tnl::Vector3 local_axis_x = tnl::Vector3::Cross({ 0,1,0 }, xz);

					q *= tnl::Quaternion::RotationAxis(local_axis_x, _mainCamera_ref->axis_x_angle_);

					_mesh->pos_ = _mainCamera_ref->target_ + tnl::Vector3::TransformCoord({ 0, 0, -to_target_distance_ }, q);

					_mainCamera_ref->axis_y_angle_ -= tnl::ToRadian(1);
				}




				// �J�����̓����̒x������
				tnl::Vector3 fix_pos = _mesh->pos_ + tnl::Vector3::TransformCoord({ _player_behind_cameraX, 100, -150 }, _mesh->rot_);
				_mainCamera_ref->pos_ += (fix_pos - _mainCamera_ref->pos_) * 0.1f;

				// �Ǐ]�|�C���^�[ON
				_mainCamera_ref->isShowTargetPointer = true;
			}
			else {

				tnl::Vector3 _camera_offset = { 0, -50, 20 };


				// �G�ɃJ�������Œ肵�Ȃ��ꍇ
				_mainCamera_ref->target_ = _mesh->pos_;
				_mainCamera_ref->target_ -= _camera_offset;

				ControlRotationByMouse((*it_eneList_ref));


				// �J�����̓����̒x������
				tnl::Vector3 fix_pos = _mesh->pos_ + tnl::Vector3::TransformCoord({ 0, 100, -150 }, _mesh->rot_);
				_mainCamera_ref->pos_ += (fix_pos - _mainCamera_ref->pos_) * 0.1f;

				// �Ǐ]�|�C���^�[OFF
				_mainCamera_ref->isShowTargetPointer = false;
			}
		}
	}
}




void Player::NormalizeCameraSpeed() {

	tnl::Vector3 zero = { 0,0,0 };

	if ((move_vel_ - zero).length() > 0.0f) {

		// �x�N�g�����K��
		move_vel_ = move_vel_.Normalize(move_vel_) * 4;
	}
}




void Player::ControlMainCameraPos(const CameraPos enum_camera_pos) {

	switch (enum_camera_pos)
	{
	case CameraPos::DIR_RIGHT:
		_mainCamera_ref->pos_.x -= moveSpeed + camera_pos_offset;

		break;
	case CameraPos::DIR_LEFT:
		_mainCamera_ref->pos_.x += moveSpeed + camera_pos_offset;

		break;
	case CameraPos::DIR_UP:
		_mainCamera_ref->pos_.z -= moveSpeed + camera_pos_offset;

		break;
	case CameraPos::DIR_DOWN:
		_mainCamera_ref->pos_.z += moveSpeed + camera_pos_offset;

		break;
	default:
		break;
	}
}



void Player::ControlRotationByMouse(Shared<EnemyBase> enemy) {

	tnl::Vector3 vel = tnl::Input::GetMouseVelocity();

	// ���E���_
	rot_y_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(vel.x * 0.05f));

	//// �㉺���_���L��������ꍇ�̓A���R�����g���Ă�������
	//tnl::Vector3 forward = tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_y_);
	//rot_x_ *= tnl::Quaternion::RotationAxis(tnl::Vector3::Cross({ 0, 1, 0 }, forward), tnl::ToRadian(vel.y * 0.01f));
}



tnl::Quaternion Player::ClampRotation(tnl::Quaternion quaternion) {

	// X�������̉�]���g��

	const float radian = 57.29578f;
	const float degree = 0.0174532924f;
	const float minX = -90.0f;
	const float minY = 90.0f;

	quaternion.w = 1;

	quaternion.x = quaternion.w;
	quaternion.y = quaternion.w;
	quaternion.z = quaternion.w;

	float angleX = std::atan(quaternion.x) * radian * 2.f;
	angleX = std::clamp(angleX, minX, minY);

	quaternion.x = std::atan(angleX * degree * 0.5f);
	return quaternion;
}



void Player::ShotStraightBullet() {

	tnl::Vector3 move_dir = tnl::Vector3::TransformCoord({ 0,0,1 }, _mesh->rot_);

	if (tnl::Input::IsMouseDown(eMouse::LEFT)) {

		tnl::Vector3 spawn_pos = _mesh->pos_;
		spawn_pos.x += _mesh->rot_.x;
		spawn_pos.y += _mesh->rot_.y;
		spawn_pos.z += _mesh->rot_.z;

		tnl::Vector3 temp = tnl::Vector3::CreateScreenRay
		(

			targets_screen_coords.x,
			targets_screen_coords.y,
			DXE_WINDOW_WIDTH,
			DXE_WINDOW_HEIGHT,
			_mainCamera_ref->view_,
			_mainCamera_ref->proj_
		);

		_straight_bullets_p.emplace_back(std::make_shared<PlayerBullet>(spawn_pos, move_dir, _player_ref));
	}
}



void Player::AdjustPlayerVelocity() {

	// Time.deltaTime�̂悤�Ȃ��́B���ꂪ�Ȃ��ƃv���C���[���������
	tnl::EasyAdjustObjectVelocity(centroid_radius_, mass_, friction_, past_move_vel_, move_vel_, center_of_gravity_);

	_mesh->pos_ += move_vel_;

	if (center_of_gravity_.length() > FLT_EPSILON) {
		// �d�S�ʒu�𗘗p���ČX���Ăق����A�b�p�[�x�N�g�����쐬
		tnl::Vector3 upper = tnl::Vector3::Normalize({ center_of_gravity_.x, centroid_radius_, center_of_gravity_.z });
		// �X���̊p�x���v�Z
		float angle = upper.angle({ 0, 1, 0 });
		// �X���x�N�g���Ɛ^��x�N�g���̊O�ς����]�����v�Z���A�X���p�x�𒲐����ĉ�]�N�H�[�^�j�I�����쐬
		rot_xz_ = tnl::Quaternion::RotationAxis(tnl::Vector3::Cross(upper, { 0, 1, 0 }), -(angle * 0.2f));
	}

	// �ŏI�I�Ȏp��
	_mesh->rot_ = rot_y_ * rot_xz_;


	_mesh->rot_ = rot_y_ * rot_x_ * rot_xz_;
}



void Player::Update(float delta_time) {

	ControlPlayerMove();

	ActivateDarkSoulsCamera();

	// �E�}�E�X�������ꂽ��A�J������G�ɌŒ肷��t���O�𔽓]
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_RIGHT)) {
		_mainCamera_ref->follow = !_mainCamera_ref->follow;
	}


	_mainCamera_ref->Update();


	MoveForward(delta_time);

	ShotStraightBullet();


	AdjustPlayerVelocity();

	auto it_blt = _straight_bullets_p.begin();

	while (it_blt != _straight_bullets_p.end()) {

		(*it_blt)->Update(delta_time);

		if (!(*it_blt)->_isActive) {
			it_blt = _straight_bullets_p.erase(it_blt);
			continue;
		}
		it_blt++;
	}
}



void Player::Render(Shared<dxe::Camera> camera) {

	_mesh->render(camera);

	DrawFormatString(DXE_WINDOW_WIDTH - 100, 5, -1, "PlayerPos");
	DrawFormatString(DXE_WINDOW_WIDTH - 100, 20, -1, "%f", _mesh->pos_.x);
	DrawFormatString(DXE_WINDOW_WIDTH - 100, 40, -1, "%f", _mesh->pos_.y);
	DrawFormatString(DXE_WINDOW_WIDTH - 100, 60, -1, "%f", _mesh->pos_.z);


	DrawFormatString(DXE_WINDOW_WIDTH - 100, 80, -1, "PlayerRot");
	DrawFormatString(DXE_WINDOW_WIDTH - 100, 100, -1, "%f", _mesh->rot_.x);
	DrawFormatString(DXE_WINDOW_WIDTH - 100, 120, -1, "%f", _mesh->rot_.y);
	DrawFormatString(DXE_WINDOW_WIDTH - 100, 140, -1, "%f", _mesh->rot_.z);



	DrawFormatString(DXE_WINDOW_WIDTH - 100, 160, -1, "CameraPos");
	DrawFormatString(DXE_WINDOW_WIDTH - 100, 180, -1, "%f", _mainCamera_ref->pos_.x);
	DrawFormatString(DXE_WINDOW_WIDTH - 100, 200, -1, "%f", _mainCamera_ref->pos_.y);
	DrawFormatString(DXE_WINDOW_WIDTH - 100, 220, -1, "%f", _mainCamera_ref->pos_.z);


	for (auto blt : _straight_bullets_p) {
		blt->Render(camera);
	}
}