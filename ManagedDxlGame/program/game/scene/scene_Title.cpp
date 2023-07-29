#include "../dxlib_ext/dxlib_ext.h"
#include "../common/GameManager.h"
#include "scene_Title.h"
#include "scene_Play.h"

void SceneTitle::update(float delta_time) {
	sequence_.update(delta_time);

	//上下キーで選択中の選択肢を切り替える
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		++TitleSelect_now;
		if (TitleSelect_now == TITLE_MAX) {
			TitleSelect_now = TITLE_START;
		}
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		--TitleSelect_now;
		if (TitleSelect_now == (TITLE_START - 1)) {
			TitleSelect_now = (TITLE_MAX - 1);
		}
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		if (TitleSelect_now == TITLE_START) {
			auto mgr = GameManager::GetInstance();
			mgr->changeScene(new ScenePlay());
		}
	}
}

void SceneTitle::draw() {

	SetFontSize(50);

	DrawStringEx(Title_pos.x, Title_pos.y, -1, "Title");

	SetFontSize(20);


	if (TitleSelect_now == TITLE_START) {
		SetFontSize(30);
		DrawStringEx(Start_pos.x, Start_pos.y, 0xffff0000, "Start");		// 赤で表示

		SetFontSize(20);
		DrawStringEx(Start_pos.x, Start_pos.y + MENU_SPACE, -1, "Exit");	// 黒で表示
	}
	else if (TitleSelect_now == TITLE_EXIT) {
		SetFontSize(20);
		DrawStringEx(Start_pos.x, Start_pos.y, -1, "Start");		// 黒で表示
		SetFontSize(30);
		DrawStringEx(Start_pos.x, Start_pos.y + MENU_SPACE, 0xffff0000, "Exit");	// 赤で表示
	}



}

bool SceneTitle::seqIdle(float delta_time) {
	return true;
}