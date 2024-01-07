#include "../DxLibEngine.h"
#include "SceneSelectDifficulty.h"
#include "../ScenePlay/ScenePlay.h"
#include "../Manager/Scene/SceneManager.h"


void SceneSelectDifficulty::UpdateSelectDifficultyCursor_ByInput() {

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP))
	{
		_levelIndex--;
		if (_levelIndex < 0) _levelIndex = _LELVEL_COUNT - 1; // ������
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN))  // ���L�[
	{
		_levelIndex++;
		if (_levelIndex >= _LELVEL_COUNT) _levelIndex = 0;	   // �擪��
	}
}



void SceneSelectDifficulty::RenderDifficultiesAndAnnotation() {

	int r = 1, g = 1, b = 1, a = 1;

	for (int i = 0; i < _LELVEL_COUNT; i++) {

		if (i == _levelIndex && _levelIndex == 0)	r = -1;
		else if (i == _levelIndex && _levelIndex == 1)	g = -1;
		else if (i == _levelIndex && _levelIndex == 2)	b = -1;
		else if (i == _levelIndex && _levelIndex == 3)	a = -1;

		SetFontSize(66);
		DrawStringEx(_LEVEL_POS_X, _LEVEL_POS_Y, r, "Easy");
		SetFontSize(20);
		DrawStringEx(ANNOTATION_POS_X, ANNOTATION_POS_Y, r, "�����Ƃ��Ղ�����Փx�ł��B\n�V���[�e�B���O�Q�[���͎኱���A\n�������̓m�[�}���ł͓������A�Ƃ����������ł��B");

		SetFontSize(66);
		DrawStringEx(_LEVEL_POS_X - 40, _LEVEL_POS_Y + 140, g, "Normal");
		SetFontSize(20);
		DrawStringEx(ANNOTATION_POS_X - 40, ANNOTATION_POS_Y + 140, g, "�����Ƃ��W���̓�Փx�ł��B\n�V���[�e�B���O�����ʂȕ�������Փx�ł��B");

		SetFontSize(66);
		DrawStringEx(_LEVEL_POS_X - 80, _LEVEL_POS_Y + 280, b, "Hard");
		SetFontSize(20);
		DrawStringEx(ANNOTATION_POS_X - 80, ANNOTATION_POS_Y + 280, b, "������ƍ��߂̓�Փx�ł��B\n�A�[�P�[�h�ŃV���[�e�B���O���v���C������ɂ́A\n���x�������炢�ɂȂ��Ă��܂��B");

		SetFontSize(66);
		DrawStringEx(_LEVEL_POS_X - 120, _LEVEL_POS_Y + 420, a, "Lunatic");
		SetFontSize(20);
		DrawStringEx(ANNOTATION_POS_X - 120, ANNOTATION_POS_Y + 420, a, "����ȓ�Փx�ł��B");
	}
}



void SceneSelectDifficulty::DecideSelectedLevel_ByInput() {

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		if (_levelIndex == 0) {
			auto mgr = SceneManager::GetInstance();
			mgr->ChangeScene(new ScenePlay("Easy"));
		}
		if (_levelIndex == 1) {
			auto mgr = SceneManager::GetInstance();
			mgr->ChangeScene(new ScenePlay("Normal"));
		}
		if (_levelIndex == 2) {
			auto mgr = SceneManager::GetInstance();
			mgr->ChangeScene(new ScenePlay("Hard"));
		}
		if (_levelIndex == 3) {
			auto mgr = SceneManager::GetInstance();
			mgr->ChangeScene(new ScenePlay("Lunatic"));
		}
	}
}



void SceneSelectDifficulty::RenderBackGround() {
	DrawRotaGraph(600, 360, 1, 0, _backGround_hdl, false);
}



void SceneSelectDifficulty::Render() {

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	RenderBackGround();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	RenderDifficultiesAndAnnotation();
}



void SceneSelectDifficulty::Update(float deltaTime) {

	UpdateSelectDifficultyCursor_ByInput();
	DecideSelectedLevel_ByInput();
}