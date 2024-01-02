#include "SkyBox.h"


SkyBox::SkyBox() {

	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	SetDefaultLightParameter("directional_light_parameter.bin");


	skybox = dxe::Mesh::CreateBoxMV(30000, 20, 20);
	skybox->setTexture(dxe::Texture::CreateFromFile("graphics/skybox/_skybox_a.png"));
	skybox->loadMaterial("material.bin");


}



void SkyBox::Update() {

	// Ž©“®XV
	skybox->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(0.01f));

}



void SkyBox::Render(const Shared<dxe::Camera> camera) {

	skybox->render(camera);
}
