#pragma once
#include "SceneBase.h"

class GameManager {
public :

	static GameManager* instance_;
	static GameManager* GetInstance(SceneBase* start_scene = nullptr);

	void update(float delta_time);
	void draw() {};

	// ƒV[ƒ“Ø‚è‘Ö‚¦—pŠÖ”
	void changeScene(SceneBase* next_scene);


private :

	GameManager(SceneBase* start_scene);

	SceneBase* now_scene_ = nullptr;
	SceneBase* next_scene_ = nullptr;

};
