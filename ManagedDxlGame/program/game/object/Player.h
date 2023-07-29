#pragma once
#include "../base/CharacterBase.h"
#include "../object/Player.h"

class Player : public CharacterBase {
public :

	Player(tnl::Vector3 PLAY_AREA_SIZE_MAX_, tnl::Vector3 PLAY_AREA_SIZE_MIN_);
	~Player();

	void update(float delta_time) override;
	void draw() override;

	tnl::Vector3 set_play_Area_Size_Max(tnl::Vector3 PLAY_AREA_SIZE_MAX_);		// �v���C���[���̃I�u�W�F�N�g��\��������ۂ̍ő�ʒu���擾����֐�
	tnl::Vector3 set_play_Area_Size_Min(tnl::Vector3 PLAY_AREA_SIZE_MIN_);		// �v���C���[���̃I�u�W�F�N�g��\��������ۂ̍ŏ��ʒu���擾����֐�

protected :

	// player�̑傫��
	int player_r = 10;

	void move(float delta_time) override;

	// �v���C���[�����ʒu
	const tnl::Vector3 PLAYER_START_POS = { 100, 650, 0 };


	tnl::Vector3 play_Area_Size_Max;		// �v���C���[���̃I�u�W�F�N�g��\��������ۂ̍ő�ʒu
	tnl::Vector3 play_Area_Size_Min;		// �v���C���[���̃I�u�W�F�N�g��\��������ۂ̍ŏ��ʒu


};


// �ȉ���CharacterBase�̃����o�[�ϐ��A�֐���

// �L�����N�^�[�̍��W
//tnl::Vector3 pos_ = { 0, 0, 0 };

// �L�����N�^�[�̓����Ɋւ���֐�
//virtual void move(float delta_time) = 0;

// �L�����N�^�[�̉�ʏ�ł̈ړ����x
//float move_speed = 10;

// y���̈ړ���
//float move_y_value;

// �W�����v��
//float jump_power = 10;

// �L�����N�^�[�ɂ�����d��(�������Ɉړ������)
//const float gravity = 9.8;

// �������Ă��鎞��
//float time_fall = 0;
