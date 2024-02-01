#include "Player.h"
#include "../../Bullet/Player/PlayerBullet.h"
#include "../../Sky/SkyBox.h"
#include "../../ScenePlay.h"
#include "../../Camera/FreeLookCamera.h"


// �������̃I�u�W�F�N�g�̕`������鎞�̒���

//�@��ɕs�����ȃI�u�W�F�N�g��S�ĕ`�悵�Ă���Ō�ɔ������̃I�u�W�F�N�g��`�悷��
//�@�����łȂ��ƁA�I�u�W�F�N�g���d�Ȃ������ɔ������̃I�u�W�F�N�g����s�����ȃI�u�W�F�N�g�������Č����Ȃ�
//�@�܂��A�������ȃI�u�W�F�N�g�ǂ����ł���΁A�J�������狗�����������ɐ�ɕ`�悷��



Player::Player(Shared<FreeLookCamera> camera_ref) {

	_mesh = dxe::Mesh::CreateSphereMV(20, 10, 10, false);
	_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/playerTexture.jpg"));
	_mesh->scl_ = { 1.0f, 1.0f, 1.0f };
	_mesh->pos_ = { 0, 100, -300 };

	//�@�v���C���[��������
	_mesh->setBlendMode(DX_BLENDMODE_ADD);
	_mesh->setAlpha(0.5f);

	collide_size = { 20, 10, 10 };

	_hp = 100;
	_MAX_HP = _hp;

	_mainCamera_ref = camera_ref;
}


void Player::DecreaseHP(int damage) {

	_hp -= damage;

	if (_hp <= 0) {

		// �Q�[���I�[�o�[����
	}
}



void Player::RenderPlayerHp() {

	if (_hp <= 0) return;

	float x1 = 60;
	float x2 = x1 + 150;

	float gage_width = abs(x2 - x1);

	float average = (_MAX_HP > 0) ? gage_width / _MAX_HP : 0;

	x2 = x1 + static_cast<int>(average * _hp);

	DrawBoxAA(x1, 50, x2, 65, GetColor(0, 255, 0), true);
}



void Player::SetEnemyZakoListRef(const std::vector<Shared<EnemyZakoBase>>& enemies_list_ref) {

	_enemyZako_list_ref = enemies_list_ref;
}


void Player::SetEnemyBossListRef(const std::vector<Shared<EnemyBossBase>>& enemyBoss_list_ref) {
	_enemyBoss_list_ref = enemyBoss_list_ref;
}


void Player::EraseEnemyZakoListRef(Shared<EnemyZakoBase>& enemy_list_ref) {

	for (auto it = _enemyZako_list_ref.begin(); it != _enemyZako_list_ref.end(); it++) {

		if (*it == enemy_list_ref) {
			_enemyZako_list_ref.erase(it);
			break;
		}
	}
}


void Player::EraseEnemyBossListRef(Shared<EnemyBossBase>& enemyBoss_ref) {

	for (auto it = _enemyBoss_list_ref.begin(); it != _enemyBoss_list_ref.end(); it++) {

		if (*it == enemyBoss_ref) {
			_enemyBoss_list_ref.erase(it);
			break;
		}
	}
}


void Player::ControlPlayerMove(const float delta_time) {

	float speed = 4.f;

	// ����  �Q�[���p�b�h�̏ꍇ�́����x
	if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT) || tnl::Input::IsPadDown(ePad::KEY_3))
		speed = 2.5f;


	// ������
	if (tnl::Input::IsKeyDown(eKeys::KB_A) || tnl::Input::IsPadDown(ePad::KEY_LEFT) && !_mainCamera_ref->follow) {

		move_vel_ -= tnl::Vector3::TransformCoord({ 1.0f, 0, 0 }, rot_y_);

		NormalizeCameraSpeed(speed);
	}

	// �E����
	if (tnl::Input::IsKeyDown(eKeys::KB_D) || tnl::Input::IsPadDown(ePad::KEY_RIGHT) && !_mainCamera_ref->follow) {

		move_vel_ += tnl::Vector3::TransformCoord({ 1.0f, 0, 0 }, rot_y_);

		NormalizeCameraSpeed(speed);
	}

	// ������@�@//�@���̃Q�[���p�b�h��L���ɂ���ƍ��W����ɔ��ōs���o�O������
	if (tnl::Input::IsKeyDown(eKeys::KB_W) /*|| tnl::Input::IsPadDown(ePad::KEY_UP)*/) {

		move_vel_ += tnl::Vector3::TransformCoord({ 0, 1.0f, 0.1f }, rot_y_);
		_mesh->pos_.z += _moveSpeed;

		NormalizeCameraSpeed(speed);
	}

	// ������
	if (tnl::Input::IsKeyDown(eKeys::KB_S) || tnl::Input::IsPadDown(ePad::KEY_DOWN)) {

		move_vel_ -= tnl::Vector3::TransformCoord({ 0, 1.0f, 0.1f }, rot_y_);
		_mesh->pos_.z -= _moveSpeed;

		NormalizeCameraSpeed(speed);
	}

	// �O�����@�Q�[���p�b�h�̏ꍇ��L1
	if (tnl::Input::IsKeyDown(eKeys::KB_SPACE) || tnl::Input::IsPadDown(ePad::KEY_4)) {

		_mesh->pos_ += tnl::Vector3::TransformCoord(
			{ 0,0,2 }, _mesh->rot_) * _forward_velocity * delta_time * 150;
	}
}



void Player::NormalizeCameraSpeed(const float speed) {

	tnl::Vector3 zero = { 0,0,0 };

	if ((move_vel_ - zero).length() > 0.0f) {

		// �x�N�g�����K��
		move_vel_ = move_vel_.Normalize(move_vel_) * speed;
	}
}


void Player::ControlRotationByPadOrMouse() {

	// �Q�[���p�b�h
	if (!_mainCamera_ref->follow) {

		tnl::Vector3 vel = tnl::Input::GetLeftStick();

		// ���E���_
		rot_y_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(vel.x * 1));

		// �㉺���_
		tnl::Vector3 forward = tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_y_);
		rot_x_ *= tnl::Quaternion::RotationAxis(tnl::Vector3::Cross({ 0, 1, 0 }, forward), tnl::ToRadian(vel.y * 0.01f));
	}

	// �}�E�X
	if (!_mainCamera_ref->follow
		&& tnl::Input::GetLeftStick().x == 0
		&& tnl::Input::GetLeftStick().y == 0
		&& tnl::Input::GetLeftStick().z == 0) {

		tnl::Vector3 vel = tnl::Input::GetMouseVelocity();

		// ���E���_
		rot_y_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(vel.x * 0.05f));

		// �㉺���_
		tnl::Vector3 forward = tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_y_);
		rot_x_ *= tnl::Quaternion::RotationAxis(tnl::Vector3::Cross({ 0, 1, 0 }, forward), tnl::ToRadian(vel.y * 0.01f));
	}
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
		if (_enemy_index >= _enemyZako_list_ref.size()) {
			_enemy_index = 0;
		}
	}
	else if (wheel < 0) {
		_enemy_index--;
		if (_enemy_index < 0) {
			_enemy_index = _enemyZako_list_ref.size() - 1;
		}
	}
}



void Player::RenderFollowPointer()
{
	std::vector<Shared<EnemyZakoBase>>::iterator it_zako;
	std::vector<Shared<EnemyBossBase>>::iterator it_boss;
	tnl::Vector3 enemy_pos;

	if (_mainCamera_ref->isShowTargetPointer) {

		if (!_enemyZako_list_ref.empty()) {

			// �C���f�b�N�X���u����Ă���G�̂݃C�e���[�^�[�Ŏ擾
			it_zako = std::next(_enemyZako_list_ref.begin(), _enemy_index);
			enemy_pos = (*it_zako)->_mesh->pos_;

		}
		else if (_enemyZako_list_ref.empty() && !_enemyBoss_list_ref.empty()) {
			it_boss = _enemyBoss_list_ref.begin();
			enemy_pos = (*it_boss)->_mesh->pos_;
		}


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
	}
}


bool Player::IsEnemyInCapturableRange() {

	tnl::Vector3 player_pos = _mesh->pos_;

	if (!_enemyZako_list_ref.empty()) {

		for (auto it_enemyList = _enemyZako_list_ref.begin(); it_enemyList != _enemyZako_list_ref.end(); it_enemyList++) {

			if (!(*it_enemyList)) break;

			tnl::Vector3 target_enemy_pos = (*it_enemyList)->_mesh->pos_;
			float dis_player_enemy = (target_enemy_pos - player_pos).length();
			if (dis_player_enemy < 500) {
				return true;
			}
		}
	}
	else if (_enemyZako_list_ref.empty() && !_enemyBoss_list_ref.empty()) {

		auto it_bossList = _enemyBoss_list_ref.begin();

		if ((*it_bossList)) {

			tnl::Vector3 target_enemy_pos = (*it_bossList)->_mesh->pos_;
			float dis_player_enemy = (target_enemy_pos - player_pos).length();
			if (dis_player_enemy < 500) {
				return true;
			}
		}
	}

	return false;
}


void Player::ActivateDarkSoulsCamera() {

	tnl::Vector3 player_pos = _mesh->pos_;
	tnl::Vector3 target_enemy_pos;

	if (!_enemyZako_list_ref.empty()) {

		for (auto it_zakoList_ref = _enemyZako_list_ref.begin(); it_zakoList_ref != _enemyZako_list_ref.end(); it_zakoList_ref++) {

			if ((*it_zakoList_ref)) {
				target_enemy_pos = (*it_zakoList_ref)->_mesh->pos_;
			}
		}
	}
	else if (_enemyZako_list_ref.empty() && !_enemyBoss_list_ref.empty()) {

		auto it_bossList_ref = _enemyBoss_list_ref.begin();

		if (*it_bossList_ref)
			target_enemy_pos = (*it_bossList_ref)->_mesh->pos_;
	}


	float dis_player_enemy = (target_enemy_pos - player_pos).length();

	if (_mainCamera_ref->follow) {

		// �Ǐ]�|�C���^�[ON�i�`��j
		_mainCamera_ref->isShowTargetPointer = true;

		ChangeTarget_ByMouseWheel();
		RenderFollowPointer();

		tnl::Vector3 tmp{};
		tmp.y = player_pos.y - 70;

		// �J�������v���C���[�ƓG�̒��Ԓn�_�ɌŒ�
		_mainCamera_ref->target_ = (tmp + target_enemy_pos) / 2;

		//_player_ref->_mainCamera_ref->ControlFreeLookCamera(_mainCamera_ref, _player_ref->_mesh, _mainCamera_ref->target_);

		tnl::Vector3 cameraOffset = { 0, 0, -200 };
		tnl::Vector3 cameraPos = player_pos + cameraOffset;
		// �J�����̈ʒu = �v���C���[���W + (normalized(�v���C���[���W - �G���W) * �J�����ƃv���C���[�̍���)
		// �������A�P���Ƀv���C���[�̍��W���g���ƃv���C���[�ƃG�l�~�[���d�Ȃ��Ă��܂����߁A�������g��


		tnl::Quaternion q = tnl::Quaternion::RotationAxis({ 0,1,0 }, _mainCamera_ref->axis_y_angle_);
		tnl::Vector3 xz = tnl::Vector3::TransformCoord({ 0,0,1 }, q);

		tnl::Vector3 local_axis_x = tnl::Vector3::Cross({ 0,1,0 }, xz);
		q *= tnl::Quaternion::RotationAxis(local_axis_x, _mainCamera_ref->axis_x_angle_);

		_mesh->rot_ = tnl::Quaternion::LookAt(player_pos, target_enemy_pos, local_axis_x);

		//������
		if (tnl::Input::IsKeyDown(eKeys::KB_A) || tnl::Input::IsPadDown(ePad::KEY_LEFT)) {

			tnl::Vector3 new_pos = _mainCamera_ref->target_ + tnl::Vector3::TransformCoord({ 0, _mesh->pos_.y, -350 }, q);
			new_pos.y = _mesh->pos_.y;

			_mesh->pos_ = new_pos;
			_mainCamera_ref->axis_y_angle_ += tnl::ToRadian(2);
		}

		// �E����
		if (tnl::Input::IsKeyDown(eKeys::KB_D) || tnl::Input::IsPadDown(ePad::KEY_RIGHT)) {

			tnl::Vector3 new_pos = _mainCamera_ref->target_ + tnl::Vector3::TransformCoord({ 0, _mesh->pos_.y, -350 }, q);
			new_pos.y = _mesh->pos_.y;

			_mesh->pos_ = new_pos;
			_mainCamera_ref->axis_y_angle_ -= tnl::ToRadian(2);
		}


		// �J�����̓����̒x������
		tnl::Vector3 fix_pos = player_pos + tnl::Vector3::TransformCoord({ _player_behind_cameraX, 100, -150 }, _mesh->rot_);
		_mainCamera_ref->pos_ += (fix_pos - _mainCamera_ref->pos_) * 0.1f;
	}
}




void Player::ControlCameraWithoutEnemyFocus()
{
	tnl::Vector3 player_pos = _mesh->pos_;

	tnl::Vector3 _camera_offset = { 0, -50, 20 };

	// �G�ɃJ�������Œ肵�Ȃ��ꍇ
	_mainCamera_ref->target_ = player_pos;
	_mainCamera_ref->target_ -= _camera_offset;

	ControlRotationByPadOrMouse();

	// �J�����̓����̒x������
	tnl::Vector3 fix_pos = player_pos + tnl::Vector3::TransformCoord({ 0, 100, -150 }, _mesh->rot_);
	_mainCamera_ref->pos_ += (fix_pos - _mainCamera_ref->pos_) * 0.1f;

	// �Ǐ]�|�C���^�[OFF
	_mainCamera_ref->isShowTargetPointer = false;
}





void Player::ShotPlayerBullet() {

	tnl::Vector3 move_dir = tnl::Vector3::TransformCoord({ 0,0,1 }, _mesh->rot_);

	if (tnl::Input::IsMouseDown(eMouse::LEFT) || tnl::Input::IsPadDown(ePad::KEY_1)) {

		tnl::Vector3 spawn_pos = _mesh->pos_;
		spawn_pos.x += _mesh->rot_.x;
		spawn_pos.y += _mesh->rot_.y;
		spawn_pos.z += _mesh->rot_.z;

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
	// ControlRotationByMouse �ŏ㉺���_���g�p����ꍇ�́����g��
	_mesh->rot_ = rot_y_ * rot_x_ * rot_xz_;
}



void Player::Update(float delta_time) {

	ControlPlayerMove(delta_time);

	ActivateDarkSoulsCamera();

	ControlCameraWithoutEnemyFocus();

	// �E�}�E�X�������ꂽ��A�J������G�ɌŒ肷��t���O�𔽓]
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_RIGHT) && IsEnemyInCapturableRange()) {
		_mainCamera_ref->follow = !_mainCamera_ref->follow;
	}


	_mainCamera_ref->Update(delta_time);

	ShotPlayerBullet();


	AdjustPlayerVelocity();

	UpdateStraightBullet(delta_time);
}



void Player::UpdateStraightBullet(float delta_time)
{
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



void Player::Render(Shared<FreeLookCamera> camera) {

	_mesh->render(camera);

	DrawBoxAA(60, 50, 210, 65, GetColor(150, 150, 150), true);

	RenderPlayerHp();
	SetFontSize(16);
	DrawString(30, 50, "HP:", -1);
	SetFontSize(22);

	for (auto blt : _straight_bullets_p) blt->Render(camera);
}