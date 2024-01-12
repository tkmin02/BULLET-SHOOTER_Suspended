#include "ScenePlay.h"
#include "../Manager/Scene/SceneManager.h"
#include "../Manager/Enemy/EnemyManager.h"
#include "Character/Enemy/EnemyZakoBox.h"
#include "Sky/SkyBox.h"
#include "Ground/HeightMap.h"
#include "Star/ShiningStar.h"
#include "Bullet/Player/PlayerBullet.h"
#include "Bullet/Enemy/EnemyBullet.h"



ScenePlay::ScenePlay(std::string selected_difficulty, int stage) : _DIFFICULTY(selected_difficulty) {

	// ���C���J����
	_mainCamera = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	// �v���C���[
	_player = std::make_shared<Player>(_mainCamera);
	_player->SetPlayerRef(_player);

	// �n�C�g�}�b�v(�n��) �@�� �X�J�C�{�b�N�X�Ƒ��������̂ŗ����͎g��Ȃ�
	//_heightMap = std::make_shared<HeightMap>(stage);

	// �X�J�C�{�b�N�X(�V��)
	_skyBox = std::make_shared<SkyBox>(stage);

	// �����蔻��
	_collision = std::make_shared<Collision>();

	// �G�Ɋւ��邠���鏈����S�ĊǗ�
	_enemyManager = std::make_shared<EnemyManager>(stage, _player, _mainCamera, _collision, selected_difficulty);

	// ��ʍ����̍��G���[�_�[�̉摜
	miniMap_hdl = LoadGraph("graphics/miniMap/radar.jpg");
}


void ScenePlay::RenderEnemyRadarOnMiniMap() {

	// �����̃~�j�}�b�v���[�_�[
	std::list<tnl::Vector3> enemy_pos_list = _enemyManager->GetEnemyPositions_FromPlayer();

	for (auto e_pos = enemy_pos_list.begin(); e_pos != enemy_pos_list.end(); e_pos++) {

		tnl::Vector3 screen_pos = tnl::Vector3::ConvertToScreen(
			{ (*e_pos).x, (*e_pos).y, (*e_pos).z },
			miniMap_center_pos.x,
			miniMap_center_pos.y,
			_mainCamera->view_,
			_mainCamera->proj_
		);

		// �G�ʒu��΂̉~�ŕ`��
		DrawCircleAA(
			std::clamp((int)screen_pos.x, (int)miniMap_center_pos.x, 160),
			std::clamp((int)screen_pos.y, (int)miniMap_center_pos.y, 660),
			2, 10, GetColor(0, 255, 0));
	}
}



void ScenePlay::MoveNextStage(int stage) {

	switch (stage)
	{
	case 2:
	{
		SceneManager* mgr = SceneManager::GetInstance();
		mgr->ChangeScene(new ScenePlay(_DIFFICULTY , stage));

		break;
	}

	case 3:
	{
		SceneManager* mgr = SceneManager::GetInstance();
		mgr->ChangeScene(new ScenePlay(_DIFFICULTY, stage));

		break;
	}
	default:
		break;
	}
}



void ScenePlay::Render() {

	_skyBox->Render(_mainCamera);

	//_heightMap->Render(_mainCamera);

	_player->Render(_mainCamera);

	_enemyManager->Render();

	
	// �~�j�}�b�v
	DrawRotaGraph(miniMap_center_pos.x, miniMap_center_pos.y, 0.035, 0, miniMap_hdl, 1);
	RenderEnemyRadarOnMiniMap();
}



void ScenePlay::Update(float deltaTime) {

	_skyBox->Update();

	//_heightMap->Update();

	_enemyManager->Update(deltaTime);
	
	_player->Update(deltaTime);
	_player->ActivateDarkSoulsCamera();

	// �������ܕ`��
	ShiningStar s;	s.Update();
}