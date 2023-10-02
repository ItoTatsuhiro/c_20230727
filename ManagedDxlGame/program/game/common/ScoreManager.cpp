#include "ScoreManager.h"

ScoreManager::ScoreManager() {

}

ScoreManager::~ScoreManager() {

}

ScoreManager* ScoreManager::GetInstance_() {

	static ScoreManager* instance = nullptr;
	if (!instance) {
		instance = new ScoreManager();
	}

	return instance;
}

void ScoreManager::scoreCount_(float delta_time) {

	static float scoreAddTime_Count = 0;

	if (scoreAddTime_Count >= scoreAddTime_) {

		nowScore_ += scoreAddTime_Value_;

		scoreAddTime_Count = 0;
	}

	scoreAddTime_Count += delta_time;

}

// スコアを初期化する関数
void ScoreManager::scoreReset() {
	nowScore_ = 0;
}

// 最高スコアを更新する際に使用する関数
void ScoreManager::highScoreUpdate() {

	if (nowScore_ >= highScore_) {
		highScore_ = nowScore_;
	}

}

