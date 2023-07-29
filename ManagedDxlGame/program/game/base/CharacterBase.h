#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

class CharacterBase {
public :

	virtual void update(float delta_time) = 0;
	virtual void draw() = 0;

	// キャラクターの座標
	tnl::Vector3 pos_ = { 0, 0, 0 };

protected :

	virtual ~CharacterBase() {};



	// キャラクターの動きに関する関数
	virtual void move(float delta_time) = 0;

	// キャラクターの画面上での移動速度
	float move_speed = 10;

	// y軸の移動量
	float move_y_value = 0;

	// ジャンプ力
	float jump_power = 10;

	// キャラクターにかかる重力(下向きに移動する力)
	const float gravity = 9.8;

	// 落下している時間
	float time_fall = 0;

};