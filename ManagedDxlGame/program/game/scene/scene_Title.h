#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../base/SceneBase.h"


class SceneTitle : public SceneBase {
private:
	//タイトル画面で選択するメニュー
	enum TitleSelect {
		TITLE_START,		//ゲームを始める選択肢
		TITLE_EXIT,			//ゲームを終了する選択肢
		TITLE_MAX			//選択肢の数
	};

public:
	int TitleSelect_now = TITLE_START;		//タイトルシーンで現在選択中の選択肢

	//SceneTitle();
	//~SceneTitle();

	void update(float delta_time) override;

	void draw() override;

	//void title_menu_select();		//タイトル画面の選択肢の選択用

private:
	//タイトルシーンのシーケンスを定義
	tnl::Sequence<SceneTitle> sequence_ = tnl::Sequence<SceneTitle>(this, &SceneTitle::seqIdle);
	bool seqIdle(float delta_time);

	tnl::Vector3
		Title_pos{ 400, 200, 0 },		//タイトルのテキストの表示位置
		Start_pos{ 500, 450, 0 };		//startの表示位置

	static constexpr int MENU_SPACE = 70;				//タイトルメニューの間隔



};
