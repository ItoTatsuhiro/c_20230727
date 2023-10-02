#pragma once
#include "../base/SceneBase.h"
#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/GameManager.h"
#include "../common/ScoreManager.h"
#include "scene_Title.h"
#include "scene_Play.h"
#include "../stage/BackGround.h"

// リザルトシーンの表示フェーズの内容
enum class RESULT_DIS_PHASE {
	TITLE,				// リザルトのタイトル
	NOW_SCORE,			// 取得したスコア
	HIGH_SCORE,			// 過去最高スコア
	COMMAND,			// リザルトの操作コマンド
	MAX					// 表示フェーズ数
};

// リザルトシーンのコマンドの内容
enum class RESULT_COMMAND {
	RESTART,			// リスタート
	TITLE,				// タイトルへ戻る
	MAX					// コマンドの数
};

class SceneResult : public SceneBase {
public:

	SceneResult();
	~SceneResult() {};

	void update(float delta_time);
	void draw(float delta_time);

private:

	// シーン切り替え用
	bool seqIdle(const float delta_time);
	tnl::Sequence<SceneResult> sequence_ = tnl::Sequence<SceneResult>(this, &SceneResult::seqIdle);

	int nowScore_ = 0;			// 今回のプレイで取得したスコア
	int highScore_ = 0;			// これまででの最高スコア


	tnl::Vector3 resultTextPos_{ 450, 200, 0 };
	tnl::Vector3 nowScorePos_{ 500, 350, 0 };
	tnl::Vector3 highScorePos_{ 500, 450, 0 };


	tnl::Vector3 commandRestartPos_{ 400, 550, 0 };
	tnl::Vector3 commandReturnTitlePos_{ 750, 550, 0 };

	RESULT_COMMAND selectCommand_ = RESULT_COMMAND::RESTART;

	float textDisplayTimeInterval_ = 1.0f;		// リザルト画面でのテキストを表示する間隔
	float textDisplayTimeCount_ = 0;			// リザルトシーンでの経過時間を表示する間隔

	// ハイスコアの表示の色の変数、通常時とハイスコア更新時に色を変えたい
	int textColor_highScore_ = 0;				
												

	int textDisplayPhase_ = 0;					// テキストの表示段階

	BackGround* background_ = nullptr;

	int resultBGM_hdl_ = 0;
	int resultDis_hdl_ = 0;
};