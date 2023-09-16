#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/GraphicManager.h"
#include "../base/SceneBase.h"
#include "../object/Player.h"
#include "../object/Stage.h"


class ScenePlay : public SceneBase {
public :
	ScenePlay();
	~ScenePlay();

	void update(float delta_time);
	void draw();

	// �I�u�W�F�N�g�̕\���͈͂��擾����p�̊֐�
	tnl::Vector3 get_PLAY_AREA_SIZE_MAX();		// �I�u�W�F�N�g�̕\���͈͂̍ő�l���擾����֐�
	tnl::Vector3 get_PLAY_AREA_SIZE_MIN();		// �I�u�W�F�N�g�̕\���͈͂̍ŏ��l���擾����֐�

private :
	// �V�[���؂�ւ��p
	bool seqIdle(const float delta_time);
	tnl::Sequence<ScenePlay> sequence_ = tnl::Sequence<ScenePlay>(this, &ScenePlay::seqIdle);

	// �v���C���[�𐶐�����p�̃|�C���^�ϐ�
	Player* player_ = nullptr;

	// 
	Stage* stage_ = nullptr;

	// �v���C���[���̃I�u�W�F�N�g��\��������ۂ̕\���͈�
	const tnl::Vector3 PLAY_AREA_SIZE_MAX = { 1000, 720, 0 };		// �v���C���[���̃I�u�W�F�N�g��\��������ۂ̍ő�ʒu
	const tnl::Vector3 PLAY_AREA_SIZE_MIN = { 0, 0, 0 };			// �v���C���[���̃I�u�W�F�N�g��\��������ۂ̍ŏ��ʒu

	// �����蔻��p
	void hitCheck();

};
