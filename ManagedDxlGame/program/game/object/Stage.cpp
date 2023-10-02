#include <string>
#include <vector>
#include "Stage.h"
//#include "../../dxlib_ext/dxlib_ext.h"
//#include "../common/GameManager.h"


Stage::Stage() {

	int STAGE_DATA = static_cast<int>(GameManager::CSV_NAME::STAGE_DATA);		// �X�e�[�W�Ɋւ���l������p
	//std::string a = GameManager::GetInstance_()->csvAddress[STAGE_DATA][0];
	stageData_ = tnl::LoadCsv<int>( GameManager::GetInstance_()->csvAddress[static_cast<int>(GameManager::CSV_NAME::STAGE_DATA)][0] );


	// �ǂݍ��񂾃f�[�^�����ꂼ��̕ϐ��ɑ��
	mapchipSize_ = stageData_[0][1];
	stageDisplaySize_ = tnl::Vector3((float)stageData_[1][1], (float)stageData_[1][2], 0);
	//stageCutNumber_ = tnl::Vector3((float)stageData_[2][1], (float)stageData_[2][2], 0);
	stageCutNumber_ = tnl::Vector3(DXE_WINDOW_WIDTH / mapchipSize_ + 1.0f, DXE_WINDOW_HEIGHT / mapchipSize_ + 1.0f, 0);
	stageHeightBase_ = stageData_[3][1];
	spikeInterval_min_ = stageData_[4][1];
	spikeInterval_width_ = stageData_[5][1];
	spikeHeight_min_ = stageData_[6][1];
	spikeHeight_max_ = stageData_[6][2];

	// �`�����N���m�F������W��������
	chunkCheckPosX_ = - mapchipSize_ / 2;

	block_gpc_ = GraphicManager::GetInstance_()->loadGraph_(GRAPHIC_TYPE::BLOCK);		// �n�ʂ̉摜�̓ǂݍ���
	// �j(��Q��)�̉摜�̏�����
	spike_gpc_ = GraphicManager::GetInstance_()->loadGraph_(GRAPHIC_TYPE::SPIKE);		// ��Q��(�j)�̉摜�̓ǂݍ���

	makeStageChunk_();		// �X�e�[�W�̃`�����N�𐶐�

}

void Stage::update(float delta_time) {

	// �X�e�[�W���X�N���[������֐��̌Ăяo��
	scrollStage_(stageScrollSpeed_);

}

void Stage::draw() {


	auto it = stageMap_Chunk_Obj_.begin();
	
	// �`�b�v�̕`��
	while (it != stageMap_Chunk_Obj_.end()) {
		for (int y = 0; y < stageCutNumber_.y; ++y) {
			for (int x = 0; x < stageCutNumber_.x; ++x) {
				if ((*it)[y][x] != nullptr) {

					switch ((*it)[y][x]->get_chipType_()) {
					case MAPCHIP::BLOCK :

						DrawRotaGraph((*it)[y][x]->getPos_().x, (*it)[y][x]->getPos_().y, 2.0f, 0, block_gpc_, true);
						//DrawStringEx(300, 300, -1, "������");
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

					// ���W�ɃX�N���[���ʂ����Z
					(*it)[y][x]->setPos_((*it)[y][x]->getPos_() - scrollVolume);



					if (x == 0) {
						// �`�����N�𐶐��A��������t���O��false�ɂ���
						if ((*it)[y][x]->getPos_().x <= chunkCheckPosX_ && makeChunkFlag_ == true) {
							makeStageChunk_();
							makeChunkFlag_ = false;
							continue;
						}
					}
					if (x == stageCutNumber_.x - 1) {
						// �`�����N���폜�A��������t���O��true�ɂ���		
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

	tnl::Vector3 posMax{ 0,0,0 };		// ���ɑ��݂��Ă���`�b�v�̒��ł̍ő�̍��W

	// �ǉ�����X�e�[�W�̃}�b�v(���l)
	std::vector<std::vector<MAPCHIP>> stageMap_Data_Ex;
	// �ǉ�����X�e�[�W�̃}�b�v(�N���X)
	std::vector<std::vector<MapChipBase*>> stageMap_Obj_Ex;


	// ���݂��Ă���`�b�v�̒�����ő�̍��W���擾���鏈��
	auto it = stageMap_Chunk_Obj_.begin();
	while (it != stageMap_Chunk_Obj_.end()) {
		// ���݂̍ő�l�����傫���Ƃ��ő�̍��W���X�V����
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

	// �X�e�[�W�̐��l�f�[�^��z��ɓ����
	for (int y = 0; y < stageCutNumber_.y; ++y) {
		std::vector<MAPCHIP> rows;		// �z��ɓ����p��vector
		for (int x = 0; x < stageCutNumber_.x; ++x) {

			// �n�ʂ𐶐����鍂���̎��n�ʂ̐��l������
			if (y == stageHeightBase_) {
				rows.emplace_back(MAPCHIP::BLOCK);
			}
			// �����łȂ��Ƃ������Ȃ��Ƃ��̐��l������
			else {
				rows.emplace_back(MAPCHIP::AIR);
			}
		}
		// 1�s����z��ɓ����
		stageMap_Data_Ex.emplace_back(std::move(rows));
	}

	if (posMax.x != 0) {
		makeSpike_(stageMap_Data_Ex);
	}

	// �`�����N�f�[�^�ɓ����
	stageMap_Chunk_Data_.emplace_back(stageMap_Data_Ex);


	for (int y = 0; y < stageCutNumber_.y; ++y) {
		std::vector<MapChipBase*> rows;
		for (int x = 0; x < stageCutNumber_.x; ++x) {

			switch (stageMap_Data_Ex[y][x]) {
			case MAPCHIP::AIR :
				// MAPCHIP::AIR�̎�nullptr��}��
				rows.emplace_back(nullptr);
				break;

			case MAPCHIP::BLOCK :
				// MAPCHIP::BLOCK�̂Ƃ�block�̃N���X���쐬
				rows.emplace_back(new Block(tnl::Vector3(posMax.x + mapchipSize_ * (1 / 2 + x), mapchipSize_ * (1 / 2 + y), 0), MAPCHIP::BLOCK));
				break;
			case MAPCHIP::SPIKE :
				// MAPCHIP::BLOCK�̂Ƃ�block�̃N���X���쐬
				rows.emplace_back(new Spike(tnl::Vector3(posMax.x + mapchipSize_ * (1 / 2 + x), mapchipSize_ * (1 / 2 + y), 0), MAPCHIP::SPIKE));
				break;
			}
		}
		// �z��ɓ����
		stageMap_Obj_Ex.emplace_back(std::move(rows));
	}


	// stageMap_Obj_��list�ɒǉ�
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
