#include <string>
#include <vector>
#include "Stage.h"
//#include "../../dxlib_ext/dxlib_ext.h"
//#include "../common/GameManager.h"


Stage::Stage() {

	int STAGE_DATA = static_cast<int>(GameManager::CSV_NAME::STAGE_DATA);		// ステージに関する値を入れる用
	//std::string a = GameManager::GetInstance()->csvAddress[STAGE_DATA][0];
	stageData_ = tnl::LoadCsv<int>( GameManager::GetInstance()->csvAddress[STAGE_DATA][0] );



	// 読み込んだデータをそれぞれの変数に代入
	mapchipSize_ = stageData_[0][1];
	stageDisplaySize_ = tnl::Vector3((float)stageData_[1][1], (float)stageData_[1][2], 0);
	stageCutNumber_ = tnl::Vector3((float)stageData_[2][1], (float)stageData_[2][2], 0);
	stageHeightBase_ = stageData_[3][1];

	//int numRow = 2;
	//int numCal = 10;

	for (int i = 0; i < stageCutNumber_.y; ++i) {
		std::vector<MAPCHIP> rows;
		for (int j = 0; j < stageCutNumber_.x; ++j) {
			//rows.emplace_back(1);
			
			if (i == stageHeightBase_ - 1) {

				rows.emplace_back(MAPCHIP::BLOCK);

			}
			else {

				rows.emplace_back(MAPCHIP::AIR);

			}
		}
		stageMap_Data_.emplace_back(std::move(rows));
	}

	// チャンクデータに入れる
	stageMap_Chunk_Data_.emplace_back(stageMap_Data_);


	for (int y = 0; y < stageCutNumber_.y; ++y) {
		std::vector<MapChipBase*> rows;
		for (int x = 0; x < stageCutNumber_.x; ++x) {

			switch (stageMap_Data_[y][x]) {
			case MAPCHIP::AIR:

				// 0の時nullptrを挿入
				rows.emplace_back(nullptr);

			break;
			case MAPCHIP::BLOCK:

				// 1のときblockのクラスを作成
				rows.emplace_back(new Block( tnl::Vector3(mapchipSize_ * (1 / 2 + x), mapchipSize_ * (1 / 2 + y), 0), MAPCHIP::BLOCK));

			break;
			}

		}

		// 
		stageMap_Obj_.emplace_back(std::move(rows));
	}

	// stageMap_Obj_をlistに追加
	stageMap_Chunk_Obj_.emplace_back(stageMap_Obj_);

	//for (int i = 0; i < stageCutNumber_.x; ++i) {
	//	stageMap_Data_[stageHeightBase_][i] = MAPCHIP::BLOCK;
	//}

}

void Stage::update(float delta_time) {

	auto it = stageMap_Chunk_Obj_.begin();

	

}

void Stage::draw() {

	//for (int i = 0; i < stageCutNumber_.x; ++i) {
	//	for (int j = 0; j < stageCutNumber_.y; ++j) {

	//		/*if (stageMap_Data_[i][j] == MAPCHIP::BLOCK) {

	//			DrawGraph(j * mapchipSize_, i * mapchipSize_, dirtgpc, true);
	//			DrawStringEx(300, 300, -1, "あああ");
	//		}*/
	//		if(s_map)

	//	}
	//}

	// チップの描画
	for (int y = 0; y < stageCutNumber_.y; ++y) {
		for (int x = 0; x < stageCutNumber_.x; ++x) {
			if (stageMap_Obj_[y][x] != nullptr) {
				DrawRotaGraph(stageMap_Obj_[y][x]->getPos_().x, stageMap_Obj_[y][x]->getPos_().y, 1.0f, 0, block_gpc_, true);
				//DrawStringEx(300, 300, -1, "あああ");
			}
		}
	}
}

std::vector<std::vector<MAPCHIP>>& Stage::get_stageMap_Data_() {
	return stageMap_Data_;
}

std::vector<std::vector<MapChipBase*>>& Stage::get_stageMap_Obj_() {
	return stageMap_Obj_;
}

int& Stage::get_mapchipSize_() {
	return mapchipSize_;
}

tnl::Vector3& Stage::get_stageDisplaySize_() {
	return stageDisplaySize_;
}

tnl::Vector3& Stage::get_stageCutNumber_() {
	return stageCutNumber_;
}

int& Stage::get_stageHeightBase_() {
	return stageHeightBase_;
}