#pragma once
#include "../base/SceneBase.h"
#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/GameManager.h"
#include "../common/ScoreManager.h"
#include "scene_Title.h"
#include "scene_Play.h"
#include "../stage/BackGround.h"

// ���U���g�V�[���̕\���t�F�[�Y�̓��e
enum class RESULT_DIS_PHASE {
	TITLE,				// ���U���g�̃^�C�g��
	NOW_SCORE,			// �擾�����X�R�A
	HIGH_SCORE,			// �ߋ��ō��X�R�A
	COMMAND,			// ���U���g�̑���R�}���h
	MAX					// �\���t�F�[�Y��
};

// ���U���g�V�[���̃R�}���h�̓��e
enum class RESULT_COMMAND {
	RESTART,			// ���X�^�[�g
	TITLE,				// �^�C�g���֖߂�
	MAX					// �R�}���h�̐�
};

class SceneResult : public SceneBase {
public:

	SceneResult();
	~SceneResult() {};

	void update(float delta_time);
	void draw(float delta_time);

private:

	// �V�[���؂�ւ��p
	bool seqIdle(const float delta_time);
	tnl::Sequence<SceneResult> sequence_ = tnl::Sequence<SceneResult>(this, &SceneResult::seqIdle);

	int nowScore_ = 0;			// ����̃v���C�Ŏ擾�����X�R�A
	int highScore_ = 0;			// ����܂łł̍ō��X�R�A


	tnl::Vector3 resultTextPos_{ 450, 200, 0 };
	tnl::Vector3 nowScorePos_{ 500, 350, 0 };
	tnl::Vector3 highScorePos_{ 500, 450, 0 };


	tnl::Vector3 commandRestartPos_{ 400, 550, 0 };
	tnl::Vector3 commandReturnTitlePos_{ 750, 550, 0 };

	RESULT_COMMAND selectCommand_ = RESULT_COMMAND::RESTART;

	float textDisplayTimeInterval_ = 1.0f;		// ���U���g��ʂł̃e�L�X�g��\������Ԋu
	float textDisplayTimeCount_ = 0;			// ���U���g�V�[���ł̌o�ߎ��Ԃ�\������Ԋu

	// �n�C�X�R�A�̕\���̐F�̕ϐ��A�ʏ펞�ƃn�C�X�R�A�X�V���ɐF��ς�����
	int textColor_highScore_ = 0;				
												

	int textDisplayPhase_ = 0;					// �e�L�X�g�̕\���i�K

	BackGround* background_ = nullptr;

	int resultBGM_hdl_ = 0;
	int resultDis_hdl_ = 0;
};