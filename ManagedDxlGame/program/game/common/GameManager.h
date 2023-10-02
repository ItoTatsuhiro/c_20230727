#pragma once
#include <vector>
#include <string>
#include "../../dxlib_ext/dxlib_ext.h"
#include <vector>
#include "GraphicManager.h"
#include "AnimManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "../base/SceneBase.h"



class GameManager {
public :

	static GameManager* instance_;
	static GameManager* GetInstance_(SceneBase* start_scene = nullptr);

	void update(float delta_time);

	// �V�[���؂�ւ��p�֐�
	void changeScene(SceneBase* next_scene);

	std::vector<std::vector<std::string>> csvAddress;		// �ǂݍ���csv�t�@�C���̃A�h���X���i�[����p

	void Load_CsvAddress();			// �ǂݍ���csv�t�@�C���̃A�h���X���i�[����csv�t�@�C����ǂݍ��ފ֐�


	// csv�t�@�C���̃A�h���X
	enum class CSV_NAME {	
		GRAPH_ADDRESS,		// �摜�̕ۑ���̃A�h���X�p
		CHARACTER_BASE,		// �L�����N�^�[�x�[�X�p
		PLAYER_DATA,		// �v���C���[�Ɋւ���l������p
		STAGE_DATA,			// �X�e�[�W�Ɋւ���l������p
		CSV_MAX				// CSV�t�@�C���̐�


	}csv_name;

	//CSV_NAME csv_name = GameManager::CSV_NAME::GRAPH_ADDRESS;



private :

	GameManager(SceneBase* start_scene);

	SceneBase* now_scene_ = nullptr;
	SceneBase* next_scene_ = nullptr;

};
