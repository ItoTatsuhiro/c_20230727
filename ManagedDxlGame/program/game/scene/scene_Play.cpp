#include "scene_Play.h"

ScenePlay::ScenePlay() {

	player_ = new Player(PLAY_AREA_SIZE_MAX, PLAY_AREA_SIZE_MIN);			// ƒvƒŒƒCƒ„[‚Ì¶¬

}

ScenePlay::~ScenePlay() {

	delete player_;
	player_ = nullptr;

}

void ScenePlay::update(float delta_time) {

	player_->update(delta_time);

}

void ScenePlay::draw() {

	player_->draw();

	DrawStringEx(100, 100, -1, "Play");

	DrawStringEx(100, 150, -1, "pos_.x = %d", player_->pos_.x);
	DrawStringEx(100, 200, -1, "pos_.y = %d", player_->pos_.y);

}

tnl::Vector3 ScenePlay::get_PLAY_AREA_SIZE_MAX() {
	return PLAY_AREA_SIZE_MAX;
}

tnl::Vector3 ScenePlay::get_PLAY_AREA_SIZE_MIN() {
	return PLAY_AREA_SIZE_MIN;
}




bool ScenePlay::seqIdle(const float delta_time) {
	return true;
}

