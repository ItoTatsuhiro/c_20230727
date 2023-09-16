#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

class CharacterBase {
public :

	virtual void update(float delta_time) = 0;
	virtual void draw() = 0;

	// �L�����N�^�[�̍��W
	tnl::Vector3 pos_ = { 0, 0, 0 };

	// �ړ��O�̍��W���擾����֐�
	const tnl::Vector3& get_posPrev_();

	// �ړ��ʂ��擾����֐�
	const tnl::Vector3& get_moveValue_();

	// �ړ��ʂ�ݒ肷��֐�
	void set_moveValue_(const tnl::Vector3& newMoveVal);

	// �������Ԃ����Z�b�g����֐�
	void reset_timeFall_();

protected :

	tnl::Vector3 posPrev_;		// �ړ��O�̍��W

	virtual ~CharacterBase() {};



	// �L�����N�^�[�̓����Ɋւ���֐�
	virtual void move(float delta_time) = 0;

	// �L�����N�^�[�̉�ʏ�ł̈ړ����x
	float move_speed = 10;

	// �ړ���
	tnl::Vector3 moveValue_ = {};

	// �W�����v��
	float jump_power = 10;

	// �L�����N�^�[�ɂ�����d��(�������Ɉړ������)
	const float gravity = 9.8f;

	// �������Ă��鎞��
	float timeFall_ = 0;

};