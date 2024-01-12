#pragma once
#include "../../DxLibEngine.h"

class SkyBox
{
public:

	SkyBox(){}
	SkyBox(int stage_id);

	Shared<dxe::Mesh> skybox = nullptr;

	void Update();
	void Render(const Shared<dxe::Camera> camera);
};