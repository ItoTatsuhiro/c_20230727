#pragma once
#include "../base/CharacterBase.h"
#include "../object/Player.h"

class Player : public CharacterBase {
public :

	Player(tnl::Vector3 PLAY_AREA_SIZE_MAX_, tnl::Vector3 PLAY_AREA_SIZE_MIN_);
	~Player();

	void update(float delta_time) override;
	void draw() override;

	tnl::Vector3 set_play_Area_Size_Max(tnl::Vector3 PLAY_AREA_SIZE_MAX_);		// プレイヤー等のオブジェクトを表示させる際の最大位置を取得する関数
	tnl::Vector3 set_play_Area_Size_Min(tnl::Vector3 PLAY_AREA_SIZE_MIN_);		// プレイヤー等のオブジェクトを表示させる際の最小位置を取得する関数

	// プレイヤーの座標を取得する
	tnl::Vector3& getPlayerPos();
	void setPlayerPos(const tnl::Vector3& newPlayerPos);
	//int& get_playerRadius();

	// プレイヤーの移動速度(移動量)を取得する
	const float& get_move_speed_();

	const float& get_WIDTH();
	const float& get_HEIGHT();

	//// 移動量を取得する関数
	//const tnl::Vector3& get_moveValue_();

private :

	static constexpr int WIDTH = 64;
	static constexpr int HEIGHT = WIDTH * 2;

	// playerの大きさ
	//int player_r = 10;

	void move(float delta_time) override;

	// プレイヤー初期位置
	const tnl::Vector3 PLAYER_START_POS = { 100, 100, 0 };


	tnl::Vector3 play_Area_Size_Max;		// プレイヤー等のオブジェクトを表示させる際の最大位置
	tnl::Vector3 play_Area_Size_Min;		// プレイヤー等のオブジェクトを表示させる際の最小位置

	
};


// 以下はCharacterBaseのメンバー変数、関数等

// キャラクターの座標
//tnl::Vector3 pos_ = { 0, 0, 0 };

// キャラクターの動きに関する関数
//virtual void move(float delta_time) = 0;

// キャラクターの画面上での移動速度
//float move_speed = 10;

// y軸の移動量
//float moveValue_;

// ジャンプ力
//float jump_power = 10;

// キャラクターにかかる重力(下向きに移動する力)
//const float gravity = 9.8;

// 落下している時間
//float timeFall_ = 0;
