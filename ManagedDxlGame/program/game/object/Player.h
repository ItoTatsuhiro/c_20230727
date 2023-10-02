#pragma once
#include <vector>
#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/GameManager.h"
#include "../base/CharacterBase.h"
#include "../common/AnimManager.h"
#include "../common/GraphicManager.h"


// csv���ɋL�ڂ̂��鍀�ڂ�enum class
enum class PLAYER_CSV {
	WIDTH = 0,		// ��
	HEIGHT,			// ����
	START_POS,		// �����ʒu
	MOVE_SPEED,		// �ړ����x
	JUMP,			// �W�����v��
	GRAVITY,		// �d��
	HP,				// �̗�
	MAX				//���ڂ̐�
};

class Player : public CharacterBase {
public :

	Player(tnl::Vector3 PLAY_AREA_SIZE_MAX_, tnl::Vector3 PLAY_AREA_SIZE_MIN_);
	~Player();

	void update(float delta_time) override;
	void draw(float delta_time) override;

	tnl::Vector3 set_play_Area_Size_Max(tnl::Vector3 PLAY_AREA_SIZE_MAX_);		// �v���C���[���̃I�u�W�F�N�g��\��������ۂ̍ő�ʒu���擾����֐�
	tnl::Vector3 set_play_Area_Size_Min(tnl::Vector3 PLAY_AREA_SIZE_MIN_);		// �v���C���[���̃I�u�W�F�N�g��\��������ۂ̍ŏ��ʒu���擾����֐�

	// �v���C���[�̍��W���擾����
	tnl::Vector3& getPlayerPos();
	void setPlayerPos(const tnl::Vector3& newPlayerPos);
	//int& get_playerRadius();

	// �v���C���[�̈ړ����x(�ړ���)���擾����
	const float& get_move_speed_();

	const int& get_WIDTH();
	const int& get_HEIGHT();

	//// �ړ��ʂ��擾����֐�
	//const tnl::Vector3& get_moveValue_();

	// hp�̒l���擾����֐�
	const float& get_hp_();

	// hp�̒l��ύX����֐�
	void set_hp_(const float damage);

	// ��_���[�W���̖��G���Ԃ��擾
	const float& get_hitInterval_() { return hitInterval_; }

	// ��_���[�W��̎���
	const float& get_hitIntervalCount_() { return hitIntervalCount_; }

	// ��_���[�W��̎��Ԃ�set����֐�
	void set_hitIntervalCount_(float time);

	// �W�����v�ł���ő�񐔂��擾����֐�
	const int get_jumpMax_() { return jumpMax_; };

	// �W�����v�񐔂̃J�E���g���擾����֐�
	const int get_jumpCount_() { return jumpCount_; };

	// �W�����v�񐔂��Z�b�g����֐�
	void set_jumpCount_(int count);

private :

	// �v���C���[�̉摜�A�j���[�V�����̓ǂݍ���
	std::vector<int> player_anim_hdl_;

	std::vector < std::vector<tnl::CsvCell>> playerData_;		// �v���C���[�̃f�[�^������p

	float anim_time_change_ = 0.1f;	// �A�j���[�V������؂�ւ��鎞��
	float anim_time_count_ = 0;		// �A�j���[�V�������Đ����鎞�Ԃ��J�E���g����p
	int anim_ctrl_flame_ = 0;		// �A�j���[�V�����̕`�悷��摜��ύX����p

	float anim_size_ = 2.0f;		// �A�j���[�V�����̑傫���̔{��

	float hpMax_ = 1;								// �̗͂̍ő�l
	float hp_ = hpMax_;								// �̗�

	int hp_gpc_hdl_ = 0;							// �̗͂�\������p�̉摜

	float hitInterval_ = 2.5f;						// ��_���[�W���̖��G����
	float hitIntervalCount_ = hitInterval_;			// ��_���[�W��̎���

	float hitFlashTime_ = 0.05f;						// ��_���[�W���̓_�ł̊Ԋu
	float hitFlashTimeCount_ = hitFlashTime_;		// �_�ł̊Ԋu���J�E���g����p

	int jumpMax_ = 1;				// �W�����v�ł����
	int jumpCount_ = 0;				// �W�����v�񐔂̃J�E���g

	// �v���C���[���\������Ă��邩�ۂ�
	bool playerView_ = true;			

	// �v���C���[��HP��\����������W
	tnl::Vector3 hp_gpc_pos_ = { 100, 100, 0 };

	// player�̑傫��
	//int player_r = 10;

	void move(float delta_time) override;

	// �v���C���[�����ʒu
	 tnl::Vector3 startPos_ = { 0, 0, 0 };


	tnl::Vector3 play_Area_Size_Max;		// �v���C���[���̃I�u�W�F�N�g��\��������ۂ̍ő�ʒu
	tnl::Vector3 play_Area_Size_Min;		// �v���C���[���̃I�u�W�F�N�g��\��������ۂ̍ŏ��ʒu

	int jumpSound_hdl_ = 0;	// �W�����v�̌��ʉ�

	int damageSound_hdl_ = 0;// �_���[�W�̌��ʉ�


};


