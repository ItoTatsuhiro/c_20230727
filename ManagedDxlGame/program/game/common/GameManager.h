#pragma once
#include <vector>
#include <string>
#include "../../dxlib_ext/dxlib_ext.h"
#include "GraphicManager.h"
#include "../base/SceneBase.h"


class GameManager {
public :

	static GameManager* instance_;
	static GameManager* GetInstance(SceneBase* start_scene = nullptr);

	void update(float delta_time);

	// シーン切り替え用関数
	void changeScene(SceneBase* next_scene);

	std::vector<std::vector<std::string>> csvAddress;		// 読み込むcsvファイルのアドレスを格納する用

	void Load_CsvAddress();			// 読み込むcsvファイルのアドレスを格納したcsvファイルを読み込む関数


	// csvファイルのアドレス
	enum class CSV_NAME {	
		GRAPH_ADDRESS,		// 画像の保存先のアドレス用
		CHARACTER_BASE,		// キャラクターベース用
		STAGE_DATA,			// ステージに関する値を入れる用
		CSV_MAX				// CSVファイルの数


	}csv_name;

	//CSV_NAME csv_name = GameManager::CSV_NAME::GRAPH_ADDRESS;



private :

	GameManager(SceneBase* start_scene);

	SceneBase* now_scene_ = nullptr;
	SceneBase* next_scene_ = nullptr;

};
