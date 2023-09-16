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

	//// �}�b�v�`�b�v�Ɏg�p����p�̒萔
	//enum class Mstage_display_size_APCHIP {
	//	AIR,			// 0�F�z�u�Ȃ�
	//	BLOCK,			// 1�F�n��
	//	MAX				// �}�b�v�`�b�v�̑���
	//};

	// �X�e�[�W�̃}�b�v���擾����p
	std::vector<std::vector<MAPCHIP>>& get_stageMap_Data_();

	std::vector<std::vector<MapChipBase*>>& get_stageMap_Obj_();


	int& get_mapchipSize_();					// �}�b�v�`�b�v�̈�ӂ̑傫�����擾����֐�
	tnl::Vector3& get_stageDisplaySize_();		// �X�e�[�W��\������͈͂��擾
	tnl::Vector3& get_stageCutNumber_();		// �X�e�[�W�̕��������擾
	int& get_stageHeightBase_();					// ����̊�{�̍������擾


private :

	std::vector<std::vector<int>> stageData_;	// csv�t�@�C������ǂݍ��ޗp

	int mapchipSize_;							// �}�b�v�`�b�v�̈�ӂ̑傫��
	tnl::Vector3 stageDisplaySize_;				// �X�e�[�W��\������͈�(�J�����͈�)�̑傫��
	tnl::Vector3 stageCutNumber_;				// �X�e�[�W�̕�����
	int stageHeightBase_;						// �X�e�[�W�̑���̊�{�̍���

	// �X�e�[�W�̃}�b�v(���l)
	std::vector<std::vector<MAPCHIP>> stageMap_Data_;

	// �X�e�[�W�̃}�b�v(�N���X)
	std::vector<std::vector<MapChipBase*>> stageMap_Obj_;



	//std::vector<std::vector<int>> s_map;

	//
	int block_gpc_ = GraphicManager::GetInstance()->loadGraph("graphics/mygame/earth.png");

	//int dirtgpc = LoadGraph("graphics/mygame/earth.png");

	
};


