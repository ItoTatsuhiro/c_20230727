#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/GameManager.h"
#include "../common/GraphicManager.h"
#include "../common/SoundManager.h"
#include "../base/SceneBase.h"
#include "scene_Play.h"
#include "../stage/BackGround.h"
//#include "../object/Player.h"

class SceneTitle : public SceneBase {
private:
	//�^�C�g����ʂőI�����郁�j���[
	enum class TitleSelect {
		TITLE_START,		//�Q�[�����n�߂�I����
		TITLE_EXIT,			//�Q�[�����I������I����
		TITLE_MAX			//�I�����̐�
	};

public:

	SceneTitle();
	~SceneTitle();

	TitleSelect Select_now = TitleSelect::TITLE_START;		//�^�C�g���V�[���Ō��ݑI�𒆂̑I����

	//SceneTitle();
	//~SceneTitle();

	void update(float delta_time) override;

	void draw(float delta_time) override;

	//void title_menu_select();		//�^�C�g����ʂ̑I�����̑I��p

private:
	//�^�C�g���V�[���̃V�[�P���X���`
	tnl::Sequence<SceneTitle> sequence_ = tnl::Sequence<SceneTitle>(this, &SceneTitle::seqIdle);
	bool seqIdle(float delta_time);

	tnl::Vector3
		Title_pos{ 250, 250, 0 },		//�^�C�g���̃e�L�X�g�̕\���ʒu
		Start_pos{ 400, 550, 0 };		//start�̕\���ʒu

	static constexpr int MENU_SPACE = 400;				//�^�C�g�����j���[�̊Ԋu

	BackGround* background_ = nullptr;

	int titleBGM_hdl_ = 0;
};
