#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/GameManager.h"
#include "../common/GraphicManager.h"
#include "../common/SoundManager.h"
#include "../base/SceneBase.h"
#include "scene_Play.h"
#include "../stage/BackGround.h"
//#include "../object/Player.h"

class SceneTitle : public SceneBase {
private:
	//タイトル画面で選択するメニュー
	enum class TitleSelect {
		TITLE_START,		//ゲームを始める選択肢
		TITLE_EXIT,			//ゲームを終了する選択肢
		TITLE_MAX			//選択肢の数
	};

public:

	SceneTitle();
	~SceneTitle();

	TitleSelect Select_now = TitleSelect::TITLE_START;		//タイトルシーンで現在選択中の選択肢

	//SceneTitle();
	//~SceneTitle();

	void update(float delta_time) override;

	void draw(float delta_time) override;

	//void title_menu_select();		//タイトル画面の選択肢の選択用

private:
	//タイトルシーンのシーケンスを定義
	tnl::Sequence<SceneTitle> sequence_ = tnl::Sequence<SceneTitle>(this, &SceneTitle::seqIdle);
	bool seqIdle(float delta_time);

	tnl::Vector3
		Title_pos{ 250, 250, 0 },		//タイトルのテキストの表示位置
		Start_pos{ 400, 550, 0 };		//startの表示位置

	static constexpr int MENU_SPACE = 400;				//タイトルメニューの間隔

	BackGround* background_ = nullptr;

	int titleBGM_hdl_ = 0;
};
