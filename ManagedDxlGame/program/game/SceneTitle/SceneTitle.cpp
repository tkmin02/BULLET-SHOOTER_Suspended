#include "../DxLibEngine.h"
#include "SceneTitle.h"
#include "../SceneSelectDifficulty/SceneSelectDifficulty.h"
#include "../Manager/Scene/SceneManager.h"


SceneTitle::SceneTitle() {

	_shadowMap = std::make_shared<dxe::ShadowMap>(dxe::ShadowMap::eSize::S2048);
	_screenEffect = std::make_shared<dxe::ScreenEffect>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
	_screenEffect->loadStatus("screenEffect/titleSceneEffect.bin");

	_backGround_hdl = LoadGraph("graphics/Scene/titleBackGround.png");
	_titleLogo_hdl = LoadGraph("graphics/Scene/titleLogo_star.png");
}



void SceneTitle:: Render() {

	_shadowMap->reserveBegin();
	_screenEffect->renderBegin();

	// ”wŒi‰æ‘œ
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
	DrawRotaGraph(640, 250, 1, 0, _backGround_hdl, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// ƒƒS
	DrawRotaGraph(630, 230, 1.4f, 0, _titleLogo_hdl, true);

	_screenEffect->renderEnd();
	_shadowMap->reserveEnd();


	// ƒfƒoƒbƒOî•ñ•`‰æ
	DrawDefaultLightGuiController();
	_screenEffect->drawGuiController({ 0, 0 });
}



void SceneTitle::Update(float deltaTime) {
	_sequence.update(deltaTime);

	FirstFadeOut(deltaTime);
	
	MakeMonoTransition(deltaTime);
}



void SceneTitle::MakeMonoTransition(float deltaTime)
{
	trans_time_cb += deltaTime;
	trans_time_cr -= deltaTime;

	float cb = tnl::SingleOscillationy(tnl::eOscStart::CENTER, 0, 1, trans_time_cb);
	float cr = tnl::SingleOscillationy(tnl::eOscStart::CENTER, 0, 1, trans_time_cr);

	_screenEffect->setMonoCb(cb * 30);
	_screenEffect->setMonoCr(cr * 30);
}



void SceneTitle::FirstFadeOut(float deltaTime)
{
	_blur_timer += deltaTime;
	if (_blur_timer >= 0.125f) {

		_blur_alpha -= (_sequence.getProgressTime() / 0.01f * 1.0f);
		_blur_timer = 0.0f;
	}
	if (_blur_alpha <= 0) _blur_alpha = 0;
	_screenEffect->setBlurAlpha(_blur_alpha);
}



bool SceneTitle::SeqIdle(float deltaTime) {

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_1)) {

		auto mgr = SceneManager::GetInstance();
		mgr->ChangeScene(new SceneSelectDifficulty());
	}

	//if (moveToSongSelect) {

	//	soundPlayed = false;
	//	StopSoundMem(title_BGM_hdl);
	//	SetCurrentPositionSoundMem(0, title_BGM_hdl);
	//}
	//else {

	//	PlaySoundMem(title_BGM_hdl, DX_PLAYTYPE_LOOP, FALSE);
	//}

	return true;
}