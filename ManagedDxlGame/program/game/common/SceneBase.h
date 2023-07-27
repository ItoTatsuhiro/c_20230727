#pragma once

class SceneBase {
public :

	virtual ~SceneBase() {};

	virtual void update(float delta_time) {};
	virtual void draw() = 0;
};