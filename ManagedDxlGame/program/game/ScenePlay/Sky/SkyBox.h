#pragma once
#include "../../DxLibEngine.h"

class SkyBox
{
public:

	SkyBox();

	Shared<dxe::Mesh> skybox = nullptr;

	void Update();
	void Render(const Shared<dxe::Camera> camera);
};