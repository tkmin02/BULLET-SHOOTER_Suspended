#pragma once
#include "EnemyBullet.h"



class SpreadBullet :
    public EnemyBullet
{


	void Shoot();

	void Render(Shared<dxe::Camera> _mainCamera) override;
	void Update(float deltaTime) override;

};

