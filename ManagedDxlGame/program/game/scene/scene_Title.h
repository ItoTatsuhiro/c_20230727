#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../base/SceneBase.h"


class SceneTitle : public SceneBase {
private:
	//�^�C�g����ʂőI�����郁�j���[
	enum TitleSelect {
		TITLE_START,		//�Q�[�����n�߂�I����
		TITLE_EXIT,			//�Q�[�����I������I����
		TITLE_MAX			//�I�����̐�
	};

public:
	int TitleSelect_now = TITLE_START;		//�^�C�g���V�[���Ō��ݑI�𒆂̑I����

	//SceneTitle();
	//~SceneTitle();

	void update(float delta_time) override;

	void draw() override;

	//void title_menu_select();		//�^�C�g����ʂ̑I�����̑I��p

private:
	//�^�C�g���V�[���̃V�[�P���X���`
	tnl::Sequence<SceneTitle> sequence_ = tnl::Sequence<SceneTitle>(this, &SceneTitle::seqIdle);
	bool seqIdle(float delta_time);

	tnl::Vector3
		Title_pos{ 400, 200, 0 },		//�^�C�g���̃e�L�X�g�̕\���ʒu
		Start_pos{ 500, 450, 0 };		//start�̕\���ʒu

	static constexpr int MENU_SPACE = 70;				//�^�C�g�����j���[�̊Ԋu



};
