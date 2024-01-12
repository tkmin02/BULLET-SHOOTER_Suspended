#include "SkyBox.h"


SkyBox::SkyBox(int stage_id) {

	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	SetDefaultLightParameter("directional_light_parameter.bin");

	skybox = dxe::Mesh::CreateBoxMV(30000, 20, 20);

	switch (stage_id)
	{
	case 1:
		skybox->setTexture(dxe::Texture::CreateFromFile("graphics/skybox/_skybox_c.png"));
		break;
	case 2:
		skybox->setTexture(dxe::Texture::CreateFromFile("graphics/skybox/_skybox_b.png"));
		break;
	case 3:
		skybox->setTexture(dxe::Texture::CreateFromFile("graphics/skybox/_skybox_a.png"));
		break;
	}
}


void SkyBox::Update() {

	// �����X�V
	skybox->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(0.01f));

}


void SkyBox::Render(const Shared<dxe::Camera> camera) {

	skybox->render(camera);
}