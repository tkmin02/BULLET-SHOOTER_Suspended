#include "EnemyBullet.h"



EnemyBullet::EnemyBullet() {

	_mesh = dxe::Mesh::CreateSphere(10);
	_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/colorTexture/emeraldGreen.jpg"));
}




void EnemyBullet::Update(float deltaTime) {


}


void EnemyBullet::Render(Shared<dxe::Camera> camera) {


}
