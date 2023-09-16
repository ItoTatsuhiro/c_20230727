#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../base/MapChipBase.h"
#include "../common/GraphicManager.h"
#include "../common/GameManager.h"
#include "../mapchip/Block.h"

class Stage {
public :

	Stage();
	//~Stage() {};

	void update(float delta_time);
	void draw();

	//// マップチップに使用する用の定数
	//enum class Mstage_display_size_APCHIP {
	//	AIR,			// 0：配置なし
	//	BLOCK,			// 1：地面
	//	MAX				// マップチップの総数
	//};

	// ステージのマップを取得する用
	std::vector<std::vector<MAPCHIP>>& get_stageMap_Data_();

	std::vector<std::vector<MapChipBase*>>& get_stageMap_Obj_();


	int& get_mapchipSize_();					// マップチップの一辺の大きさを取得する関数
	tnl::Vector3& get_stageDisplaySize_();		// ステージを表示する範囲を取得
	tnl::Vector3& get_stageCutNumber_();		// ステージの分割数を取得
	int& get_stageHeightBase_();					// 足場の基本の高さを取得


private :

	std::vector<std::vector<int>> stageData_;	// csvファイルから読み込む用

	int mapchipSize_;							// マップチップの一辺の大きさ
	tnl::Vector3 stageDisplaySize_;				// ステージを表示する範囲(カメラ範囲)の大きさ
	tnl::Vector3 stageCutNumber_;				// ステージの分割数
	int stageHeightBase_;						// ステージの足場の基本の高さ

	// ステージのマップ(数値)
	std::vector<std::vector<MAPCHIP>> stageMap_Data_;

	// ステージのマップ(クラス)
	std::vector<std::vector<MapChipBase*>> stageMap_Obj_;



	//std::vector<std::vector<int>> s_map;

	//
	int block_gpc_ = GraphicManager::GetInstance()->loadGraph("graphics/mygame/earth.png");

	//int dirtgpc = LoadGraph("graphics/mygame/earth.png");

	
};


