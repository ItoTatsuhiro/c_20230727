#pragma once

class ScoreManager {
private:
	ScoreManager();
	~ScoreManager();

	int nowScore_ = 0;			// 現在実行中のゲームのスコア
	int highScore_ = 0;			// 過去最高スコア

	float scoreAddTime_ = 0.5f;								// スコアを加算する時間

	int scoreAddTime_Value_ = 100;							// スコアの加算一回当たりの加算されるスコアの量

public:

	// スコアマネージャーをインスタンス化するための関数
	static ScoreManager* GetInstance_();

	const int& get_nowScore_() { return nowScore_; }			// 現在のゲームのスコアを取得する関数
	const int& get_highScore_() { return highScore_; }		// 過去最高スコアを取得する関数

	void scoreCount_(float delta_time);						// スコアを加算する用の関数

	void scoreReset();										// スコアを初期化する関数
	void highScoreUpdate();									// 最高スコアを更新する際に使用する関数
};