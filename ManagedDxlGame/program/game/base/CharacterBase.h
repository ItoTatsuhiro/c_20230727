#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

class CharacterBase {
public :

	virtual void update(float delta_time) = 0;
	virtual void draw() = 0;

	// キャラクターの座標
	tnl::Vector3 pos_ = { 0, 0, 0 };

	// 移動前の座標を取得する関数
	const tnl::Vector3& get_posPrev_();

	// 移動量を取得する関数
	const tnl::Vector3& get_moveValue_();

	// 移動量を設定する関数
	void set_moveValue_(const tnl::Vector3& newMoveVal);

	// 落下時間をリセットする関数
	void reset_timeFall_();

protected :

	tnl::Vector3 posPrev_;		// 移動前の座標

	virtual ~CharacterBase() {};



	// キャラクターの動きに関する関数
	virtual void move(float delta_time) = 0;

	// キャラクターの画面上での移動速度
	float move_speed = 10;

	// 移動量
	tnl::Vector3 moveValue_ = {};

	// ジャンプ力
	float jump_power = 10;

	// キャラクターにかかる重力(下向きに移動する力)
	const float gravity = 9.8f;

	// 落下している時間
	float timeFall_ = 0;

};