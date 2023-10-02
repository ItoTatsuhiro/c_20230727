#include "GameManager.h"


GameManager* GameManager::instance_ = nullptr;

GameManager::GameManager(SceneBase* start_scene) : now_scene_(start_scene) {

	// マネージャークラスのインスタンス化
	GraphicManager::GetInstance_();
	AnimManager::GetInstance_();
	ScoreManager::GetInstance_();
	SoundManager::GetInstance_();

	GameManager::Load_CsvAddress();

}


GameManager* GameManager::GetInstance_(SceneBase* start_scene) {
	if (!instance_) {
		instance_ = new GameManager(start_scene);
	}
	return instance_;
}

void GameManager::update(float delta_time) {
	if (now_scene_) now_scene_->update(delta_time);
	if (now_scene_) now_scene_->draw(delta_time);
}

void GameManager::changeScene(SceneBase* next_scene) {
	next_scene_ = next_scene;
	delete now_scene_;
	now_scene_ = nullptr;
	now_scene_ = next_scene_;
}

void GameManager::Load_CsvAddress() {

	csvAddress = tnl::LoadCsv<std::string>("csv/CsvAddress.csv");


}