#pragma once
#include "../Manager/Scene/SceneBase.h"


class SceneSelectDifficulty : public SceneBase
{
public:

	SceneSelectDifficulty() { _backGround_hdl = LoadGraph("graphics/Scene/select.jpg"); }

	void UpdateSelectDifficultyCursor_ByInput();

	void RenderDifficultiesAndAnnotation();

	void RenderBackGround();

	void DecideSelectedLevel_ByInput();

	void Render() override;

	void Update(float deltaTime) override;

private:

	int _backGround_hdl{};

	const int _LEVEL_POS_X = 580;
	const int _LEVEL_POS_Y = 110;

	const int ANNOTATION_POS_X = 560;
	const int ANNOTATION_POS_Y = 180;

	const int _LELVEL_COUNT = 4;
	int _levelIndex = 0;
};