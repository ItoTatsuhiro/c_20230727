#include <string>
#include <vector>
#include "Stage.h"
//#include "../../dxlib_ext/dxlib_ext.h"
//#include "../common/GameManager.h"


Stage::Stage() {

	int STAGE_DATA = static_cast<int>(GameManager::CSV_NAME::STAGE_DATA);		// ステージに関する値を入れる用
	//std::string a = GameManager::GetInstance_()->csvAddress[STAGE_DATA][0];
	stageData_ = tnl::LoadCsv<int>( GameManager::GetInstance_()->csvAddress[static_cast<int>(GameManager::CSV_NAME::STAGE_DATA)][0] );


	// 読み込んだデータをそれぞれの変数に代入
	mapchipSize_ = stageData_[0][1];
	stageDisplaySize_ = tnl::Vector3((float)stageData_[1][1], (float)stageData_[1][2], 0);
	//stageCutNumber_ = tnl::Vector3((float)stageData_[2][1], (float)stageData_[2][2], 0);
	stageCutNumber_ = tnl::Vector3(DXE_WINDOW_WIDTH / mapchipSize_ + 1.0f, DXE_WINDOW_HEIGHT / mapchipSize_ + 1.0f, 0);
	stageHeightBase_ = stageData_[3][1];
	spikeInterval_min_ = stageData_[4][1];
	spikeInterval_width_ = stageData_[5][1];
	spikeHeight_min_ = stageData_[6][1];
	spikeHeight_max_ = stageData_[6][2];

	// チャンクを確認する座標を初期化
	chunkCheckPosX_ = - mapchipSize_ / 2;

	block_gpc_ = GraphicManager::GetInstance_()->loadGraph_(GRAPHIC_TYPE::BLOCK);		// 地面の画像の読み込み
	// 針(障害物)の画像の初期化
	spike_gpc_ = GraphicManager::GetInstance_()->loadGraph_(GRAPHIC_TYPE::SPIKE);		// 障害物(針)の画像の読み込み

	makeStageChunk_();		// ステージのチャンクを生成

}

void Stage::update(float delta_time) {

	// ステージをスクロールする関数の呼び出し
	scrollStage_(stageScrollSpeed_);

}

void Stage::draw() {


	auto it = stageMap_Chunk_Obj_.begin();
	
	// チップの描画
	while (it != stageMap_Chunk_Obj_.end()) {
		for (int y = 0; y < stageCutNumber_.y; ++y) {
			for (int x = 0; x < stageCutNumber_.x; ++x) {
				if ((*it)[y][x] != nullptr) {

					switch ((*it)[y][x]->get_chipType_()) {
					case MAPCHIP::BLOCK :

						DrawRotaGraph((*it)[y][x]->getPos_().x, (*it)[y][x]->getPos_().y, 2.0f, 0, block_gpc_, true);
						//DrawStringEx(300, 300, -1, "あああ");
						break;

					case MAPCHIP::SPIKE :

						DrawRotaGraph((*it)[y][x]->getPos_().x, (*it)[y][x]->getPos_().y, 2.0f, 0, spike_gpc_, true);


					}
				}
			}
		}
		++it;
	}
}

std::vector<std::vector<MAPCHIP>>& Stage::get_stageMap_Data_() {
	return stageMap_Data_;
}

std::vector<std::vector<MapChipBase*>>& Stage::get_stageMap_Obj_() {
	return stageMap_Obj_;
}

std::list<std::vector<std::vector<MapChipBase*>>>& Stage::get_stageMap_Chunk_Obj_() {
	return stageMap_Chunk_Obj_;
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

void Stage::scrollStage_(const tnl::Vector3 scrollVolume) {

	auto it = stageMap_Chunk_Obj_.begin();



	while (it != stageMap_Chunk_Obj_.end()) {
		
		for (int y = 0; y < stageCutNumber_.y; ++y) {
			for (int x = 0; x < stageCutNumber_.x; ++x) {

				if ((*it)[y][x] != nullptr) {

					// 座標にスクロール量を加算
					(*it)[y][x]->setPos_((*it)[y][x]->getPos_() - scrollVolume);



					if (x == 0) {
						// チャンクを生成、生成するフラグをfalseにする
						if ((*it)[y][x]->getPos_().x <= chunkCheckPosX_ && makeChunkFlag_ == true) {
							makeStageChunk_();
							makeChunkFlag_ = false;
							continue;
						}
					}
					if (x == stageCutNumber_.x - 1) {
						// チャンクを削除、生成するフラグをtrueにする		
						if ((*it)[y][x]->getPos_().x <= chunkCheckPosX_ && makeChunkFlag_ == false) {
							++it;
							deleteStageChunk_();
							makeChunkFlag_ = true;
							continue;
						}
					}
				}
			}
		}
		++it;
	}

}

void Stage::makeStageChunk_() {

	int chunkWidth = DXE_WINDOW_WIDTH;
	int chunkHeight = DXE_WINDOW_HEIGHT;

	tnl::Vector3 posMax{ 0,0,0 };		// 既に存在しているチップの中での最大の座標

	// 追加するステージのマップ(数値)
	std::vector<std::vector<MAPCHIP>> stageMap_Data_Ex;
	// 追加するステージのマップ(クラス)
	std::vector<std::vector<MapChipBase*>> stageMap_Obj_Ex;


	// 存在しているチップの中から最大の座標を取得する処理
	auto it = stageMap_Chunk_Obj_.begin();
	while (it != stageMap_Chunk_Obj_.end()) {
		// 現在の最大値よりも大きいとき最大の座標を更新する
		for (int y = 0; y < stageCutNumber_.y; ++y) {
			if ((*it)[y][stageCutNumber_.x - 1] != nullptr) {
				if (posMax.x < (*it)[y][stageCutNumber_.x - 1]->getPos_().x) {
					posMax = (*it)[y][stageCutNumber_.x - 1]->getPos_();
				}
			}
		}
		++it;
	}
	if (stageMap_Chunk_Obj_.begin() == stageMap_Chunk_Obj_.end()) {
		posMax = { 0, 0, 0 };
	}

	// ステージの数値データを配列に入れる
	for (int y = 0; y < stageCutNumber_.y; ++y) {
		std::vector<MAPCHIP> rows;		// 配列に入れる用のvector
		for (int x = 0; x < stageCutNumber_.x; ++x) {

			// 地面を生成する高さの時地面の数値を入れる
			if (y == stageHeightBase_) {
				rows.emplace_back(MAPCHIP::BLOCK);
			}
			// そうでないとき何もないときの数値を入れる
			else {
				rows.emplace_back(MAPCHIP::AIR);
			}
		}
		// 1行分を配列に入れる
		stageMap_Data_Ex.emplace_back(std::move(rows));
	}

	if (posMax.x != 0) {
		makeSpike_(stageMap_Data_Ex);
	}

	// チャンクデータに入れる
	stageMap_Chunk_Data_.emplace_back(stageMap_Data_Ex);


	for (int y = 0; y < stageCutNumber_.y; ++y) {
		std::vector<MapChipBase*> rows;
		for (int x = 0; x < stageCutNumber_.x; ++x) {

			switch (stageMap_Data_Ex[y][x]) {
			case MAPCHIP::AIR :
				// MAPCHIP::AIRの時nullptrを挿入
				rows.emplace_back(nullptr);
				break;

			case MAPCHIP::BLOCK :
				// MAPCHIP::BLOCKのときblockのクラスを作成
				rows.emplace_back(new Block(tnl::Vector3(posMax.x + mapchipSize_ * (1 / 2 + x), mapchipSize_ * (1 / 2 + y), 0), MAPCHIP::BLOCK));
				break;
			case MAPCHIP::SPIKE :
				// MAPCHIP::BLOCKのときblockのクラスを作成
				rows.emplace_back(new Spike(tnl::Vector3(posMax.x + mapchipSize_ * (1 / 2 + x), mapchipSize_ * (1 / 2 + y), 0), MAPCHIP::SPIKE));
				break;
			}
		}
		// 配列に入れる
		stageMap_Obj_Ex.emplace_back(std::move(rows));
	}


	// stageMap_Obj_をlistに追加
	stageMap_Chunk_Obj_.emplace_back(stageMap_Obj_Ex);

}

void Stage::deleteStageChunk_() {

	auto it = stageMap_Chunk_Obj_.begin();



	while (it != stageMap_Chunk_Obj_.end()) {

		for (int y = 0; y < stageCutNumber_.y; ++y) {
			if ((*it)[y][stageCutNumber_.x - 1] != nullptr) {
				if ((*it)[y][stageCutNumber_.x - 1]->getPos_().x <= chunkCheckPosX_) {

					for (auto& it_row : *it) {
						for (auto& it_chip : it_row) {
							delete it_chip;
							it_chip = nullptr;
						}
					}

					//delete (*it);
					it = stageMap_Chunk_Obj_.erase(it);
					continue;
				}
			}
		}
		++it;
	}
}



void Stage::makeSpike_(std::vector<std::vector<MAPCHIP>>& stageMapData) {


		for (int x = 0; x < stageCutNumber_.x; ++x) {
			for (int y = 0; y < stageCutNumber_.y; ++y) {
				if (x < stageCutNumber_.x && y < stageCutNumber_.y) {
					tnl::DebugTrace("x = %d, y = %d\n", x, y);
					if (stageMapData[y][x] == MAPCHIP::BLOCK) {

						int interval = rand() % spikeInterval_width_ + spikeInterval_min_;
						int height = rand() % spikeHeight_max_ + spikeHeight_min_;

						for (int h = 1; h <= height; ++h) {
							if (h < stageCutNumber_.y) {
								if (y - h < stageCutNumber_.y && x + height < stageCutNumber_.x) {
									stageMapData[y - h][x + height] = MAPCHIP::SPIKE;
								}
							}
						}

						x += interval;
					}
				}
			}
		}
		
}
