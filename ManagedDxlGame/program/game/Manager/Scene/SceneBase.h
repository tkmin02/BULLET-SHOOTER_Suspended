#pragma once

class SceneBase
{
public:

	virtual void Initialize() {}
	virtual void Update(float delta_time) {}
	virtual void Render() {}
	virtual void ReleaseMem() {}
};