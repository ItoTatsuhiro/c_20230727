#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

class CharacterBase {
public :

	virtual void update(float delta_time) = 0;
	virtual void draw() = 0;

	// �L�����N�^�[�̍��W
	tnl::Vector3 pos_ = { 0, 0, 0 };

protected :

	virtual ~CharacterBase() {};



	// �L�����N�^�[�̓����Ɋւ���֐�
	virtual void move(float delta_time) = 0;

	// �L�����N�^�[�̉�ʏ�ł̈ړ����x
	float move_speed = 10;

	// y���̈ړ���
	float move_y_value = 0;

	// �W�����v��
	float jump_power = 10;

	// �L�����N�^�[�ɂ�����d��(�������Ɉړ������)
	const float gravity = 9.8;

	// �������Ă��鎞��
	float time_fall = 0;

};