#include "ScenePlay.h"
#include "../Manager/Scene/SceneManager.h"
#include "../Manager/Enemy/EnemyManager.h"
#include "Collision/Collision.h"
#include "Sky/SkyBox.h"
#include "Ground/HeightMap.h"
#include "Star/ShiningStar.h"
#include "Bullet/Player/PlayerBullet.h"
#include "Bullet/Enemy/EnemyBullet.h"
#include "../Manager/Score/ScoreManager.h"
#include "Camera/FreeLookCamera.h"
#include "Bullet/Enemy/BulletHell.h"
#include "Bullet/Enemy/BulletHellFactory.h"

Shared<dxe::Particle> ScenePlay::_weather_particle;

std::list<Shared<EnemyBullet>> ScenePlay::_bullet_normal_patchouli;
std::list<Shared<EnemyBullet>> ScenePlay::_bullet_silentSerena_patchouli;
std::list<Shared<EnemyBullet>> ScenePlay::_bullet_metalFatigue_patchouli;

std::unordered_map<int, SpawnedBossBulletInfo> ScenePlay::_BLTINFO_T_NORMAL_PATCHOULI;
std::unordered_map<int, SpawnedBossBulletInfo> ScenePlay::_BLTINFO_T_SILENTSERENA_PATCHOULI;
std::unordered_map<int, SpawnedBossBulletInfo> ScenePlay::_BLTINFO_T_METALFATIGUE_PATCHOULI;

bool ScenePlay::_isUsingBullet_normal_patchouli;
bool ScenePlay::_isUsingBullet_silentSerena_patchouli;
bool ScenePlay::_isUsingBullet_metalFatigue_patchouli;



ScenePlay::ScenePlay(std::string selected_difficulty, int stage) : _STAGE_ID(stage) {

	_mainCamera = std::make_shared<FreeLookCamera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	if (_STAGE_ID == 1)
		_weather_particle = std::make_shared<dxe::Particle>("particle/preset/snow.bin");
	else if (_STAGE_ID == 2)
		_weather_particle = std::make_shared<dxe::Particle>("particle/preset/customRain.bin");

	// プレイヤー
	_player = std::make_shared<Player>(_mainCamera);
	_player->SetPlayerRef(_player);

	// スカイボックス(天空)
	_skyBox = std::make_shared<SkyBox>(_STAGE_ID);

	// 当たり判定
	_collision = std::make_shared<Collision>();

	// 敵に関するあらゆる処理を全て管理
	_enemyManager = std::make_shared<EnemyManager>(_STAGE_ID, _player, _mainCamera, _collision, selected_difficulty);

	_screen_effect = std::make_shared<dxe::ScreenEffect>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	_bltHellFactory = std::make_shared<BulletHellFactory>(_enemyManager);


	switch (_STAGE_ID)
	{
	case 1:
	{
		_bullet_normal_patchouli = _bltHellFactory->CreateBulletHell(BulletHell::TYPE::Normal_Patchouli);
		for (auto& bullet : _bullet_normal_patchouli) {
			int id = bullet->_id;
			SpawnedBossBulletInfo info;
			info.originPos = bullet->_mesh->pos_;
			_BLTINFO_T_NORMAL_PATCHOULI[id] = info;
		}

		_bullet_metalFatigue_patchouli = _bltHellFactory->CreateBulletHell(BulletHell::TYPE::MetalFatigue_Patchouli);
		for (auto& bullet : _bullet_metalFatigue_patchouli) {
			int id = bullet->_id;
			SpawnedBossBulletInfo info;
			info.originPos = bullet->_mesh->pos_;
			_BLTINFO_T_METALFATIGUE_PATCHOULI[id] = info;
		}

		_bullet_silentSerena_patchouli = _bltHellFactory->CreateBulletHell(BulletHell::TYPE::SilentSerena_Patchouli);
		for (auto& bullet : _bullet_silentSerena_patchouli) {
			int id = bullet->_id;
			SpawnedBossBulletInfo info;
			info.originPos = bullet->_mesh->pos_;
			_BLTINFO_T_SILENTSERENA_PATCHOULI[id] = info;
		}

		break;
	}
	}


	// 画面左下の索敵レーダーの画像
	miniMap_hdl = LoadGraph("graphics/miniMap/radar.jpg");
}



void ScenePlay::RenderEnemyRadarOnMiniMap() {

	// 左下のミニマップレーダー
	std::list<tnl::Vector3> enemy_pos_list = _enemyManager->GetEnemyZakoPosition();

	for (auto e_pos = enemy_pos_list.begin(); e_pos != enemy_pos_list.end(); e_pos++) {

		tnl::Vector3 screen_pos = tnl::Vector3::ConvertToScreen(
			{ (*e_pos).x, (*e_pos).y, (*e_pos).z },
			miniMap_center_pos.x,
			miniMap_center_pos.y,
			_mainCamera->view_,
			_mainCamera->proj_
		);

		// 敵位置を緑の円で描画
		DrawCircleAA(
			(float)std::clamp((int)screen_pos.x, miniMap_center_pos.x, 160),
			(float)std::clamp((int)screen_pos.y, miniMap_center_pos.y, 660),
			2, 10, GetColor(0, 255, 0));
	}
}



void ScenePlay::MoveToNextStage(int stage, std::string difficulty) {

	SetFontSize(60);
	DrawFormatString(500, 200, -1, "Spell Card Bonus");
	SetFontSize(20);

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));


	switch (stage)
	{
	case 1:
	{
		DestroyFirstStageBulletHellLists();
		auto mgr = SceneManager::GetInstance();

		if (difficulty == "Easy")	      mgr->ChangeScene(new ScenePlay("Easy", 2));
		else if (difficulty == "Normal")  mgr->ChangeScene(new ScenePlay("Normal", 2));
		else if (difficulty == "Hard")	  mgr->ChangeScene(new ScenePlay("Hard", 2));
		else if (difficulty == "Lunatic") mgr->ChangeScene(new ScenePlay("Lunatic", 2));
		return;
	}
	case 2:
	{
		auto mgr = SceneManager::GetInstance();

		if (difficulty == "Easy")	      mgr->ChangeScene(new ScenePlay("Easy", 3));
		else if (difficulty == "Normal")  mgr->ChangeScene(new ScenePlay("Normal", 3));
		else if (difficulty == "Hard")	  mgr->ChangeScene(new ScenePlay("Hard", 3));
		else if (difficulty == "Lunatic") mgr->ChangeScene(new ScenePlay("Lunatic", 3));
		return;
	}
	case 3:
	{
		auto mgr = SceneManager::GetInstance();

		if (difficulty == "Easy")	      mgr->ChangeScene(new ScenePlay("Easy", 2));
		else if (difficulty == "Normal")  mgr->ChangeScene(new ScenePlay("Normal", 2));
		else if (difficulty == "Hard")    mgr->ChangeScene(new ScenePlay("Hard", 2));
		else if (difficulty == "Lunatic") mgr->ChangeScene(new ScenePlay("Lunatic", 2));
		return;
	}
	default:
		break;
	}
}





void ScenePlay::Render() {

	_screen_effect->renderBegin();


	_skyBox->Render(_mainCamera);
	_player->Render(_mainCamera);
	_enemyManager->Render();
	ScoreManager::GetInstance().RenderTotalScore();

	if (_STAGE_ID == 1 || _STAGE_ID == 2) {

		dxe::DirectXRenderBegin();
		_weather_particle->render(_mainCamera);
		dxe::DirectXRenderEnd();
	}


	RenderFirstStageBulletHellLists();


	_screen_effect->renderEnd();



	if (_STAGE_ID == 3) {
		// お星さま描画
		ShiningStar s;	s.Update();
	}

	// グリッド線
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawGridGround(_mainCamera, 100, 30);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// ミニマップ
	DrawRotaGraph(miniMap_center_pos.x, miniMap_center_pos.y, 0.035, 0, miniMap_hdl, 1);
}


void ScenePlay::DestroyFirstStageBulletHellLists() {

	_bullet_normal_patchouli.clear();
	_bullet_metalFatigue_patchouli.clear();
	_bullet_silentSerena_patchouli.clear();
}


void ScenePlay::RenderFirstStageBulletHellLists()
{
	if (_isUsingBullet_normal_patchouli) {
		for (auto blt : _bullet_normal_patchouli) {
			if (blt->_isActive)	blt->Render(_mainCamera);
		}
		std::string s = std::to_string(_bullet_normal_patchouli.size());
		DrawFormatString(1200, 50, -1, "%s個", s.c_str());
	}

	if (_isUsingBullet_metalFatigue_patchouli) {

		for (auto blt : _bullet_metalFatigue_patchouli) {
			if (blt->_isActive)  blt->Render(_mainCamera);
		}
		std::string s = std::to_string(_bullet_metalFatigue_patchouli.size());
		DrawFormatString(1200, 50, -1, "%s個", s.c_str());
	}

	if (_isUsingBullet_silentSerena_patchouli) {

		for (auto blt : _bullet_silentSerena_patchouli) {
			if (blt->_isActive)  blt->Render(_mainCamera);
		}
		std::string s = std::to_string(_bullet_silentSerena_patchouli.size());
		DrawFormatString(1200, 50, -1, "%s個", s.c_str());
	}
}



void ScenePlay::UpdateFirstStageBulletHellLists()
{
	if (_isUsingBullet_normal_patchouli) {

		auto it = _bullet_normal_patchouli.begin();

		while (it != _bullet_normal_patchouli.end())
		{
			if (!(*it)->_isActive) {

				(*it)->_mesh->pos_ = _BLTINFO_T_NORMAL_PATCHOULI[(*it)->_id].originPos;
				(*it)->_moveDirection = _BLTINFO_T_NORMAL_PATCHOULI[(*it)->_id].moveDirection;
				(*it)->_isActive = true;
			}
			it++;
		}
	}


	if (_isUsingBullet_metalFatigue_patchouli) {

		auto it = _bullet_metalFatigue_patchouli.begin();

		while (it != _bullet_metalFatigue_patchouli.end())
		{
			if (!(*it)->_isActive) {

				(*it)->_mesh->pos_ = _BLTINFO_T_METALFATIGUE_PATCHOULI[(*it)->_id].originPos;
				(*it)->_moveDirection = _BLTINFO_T_METALFATIGUE_PATCHOULI[(*it)->_id].moveDirection;
				(*it)->_isActive = true;
			}
			it++;
		}
	}



	if (_isUsingBullet_silentSerena_patchouli) {

		auto it = _bullet_silentSerena_patchouli.begin();

		while (it != _bullet_silentSerena_patchouli.end())
		{
			if (!(*it)->_isActive) {

				(*it)->_mesh->pos_ = _BLTINFO_T_SILENTSERENA_PATCHOULI[(*it)->_id].originPos;
				(*it)->_moveDirection = _BLTINFO_T_SILENTSERENA_PATCHOULI[(*it)->_id].moveDirection;
				(*it)->_isActive = true;
			}
			it++;
		}
	}
}



void ScenePlay::Update(float deltaTime) {

	_skyBox->Update();

	_enemyManager->Update(deltaTime);

	_player->Update(deltaTime);


	UpdateFirstStageBulletHellLists();
}



