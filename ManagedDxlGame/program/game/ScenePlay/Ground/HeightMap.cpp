#include "HeightMap.h"


HeightMap::HeightMap() {


	_mesh = dxe::Mesh::CreateFromHeightMapMV("graphics/height_map.png", 5000, 5000, 50, 50, 50);
	_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/skybox/_skybox_a.png"));
	_mesh->pos_ = { 0,-500,0 };
}

void HeightMap::Update() {

	_mesh->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(0.01f));
}



void HeightMap::Render(Shared<dxe::Camera> camera) {


	_mesh->render(camera);

}


