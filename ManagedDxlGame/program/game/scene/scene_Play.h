#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/GraphicManager.h"
#include "../common/ScoreManager.h"
#include "../base/SceneBase.h"
#include "scene_Result.h"
#include "../object/Player.h"
#include "../object/Stage.h"
#include "../stage/BackGround.h"

class ScenePlay : public SceneBase {
public :
	ScenePlay();
	~ScenePlay();

	void update(float delta_time);
	void draw(float delta_time);

	// �I�u�W�F�N�g�̕\���͈͂��擾����p�̊֐�
	tnl::Vector3 get_PLAY_AREA_SIZE_MAX();		// �I�u�W�F�N�g�̕\���͈͂̍ő�l���擾����֐�
	tnl::Vector3 get_PLAY_AREA_SIZE_MIN();		// �I�u�W�F�N�g�̕\���͈͂̍ŏ��l���擾����֐�


private :
	// �V�[���؂�ւ��p
	bool seqIdle(const float delta_time);
	tnl::Sequence<ScenePlay> sequence_ = tnl::Sequence<ScenePlay>(this, &ScenePlay::seqIdle);

	// �v���C���[�𐶐�����p�̃|�C���^�ϐ�
	Player* player_ = nullptr;
	// �X�e�[�W�̃|�C���^�ϐ�
	Stage* stage_ = nullptr;

	BackGround* background_ = nullptr;

	

	// �v���C���[���̃I�u�W�F�N�g��\��������ۂ̕\���͈�
	const tnl::Vector3 PLAY_AREA_SIZE_MAX = { DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, 0 };		// �v���C���[���̃I�u�W�F�N�g��\��������ۂ̍ő�ʒu
	const tnl::Vector3 PLAY_AREA_SIZE_MIN = { 0, 0, 0 };			// �v���C���[���̃I�u�W�F�N�g��\��������ۂ̍ŏ��ʒu

	// �����蔻��p
	void hitCheck();

	// �v���C�V�[���̏I�����̏���
	void sceneplayFin_();

	int playBGM_hdl_ = 0;	// BGM


};
