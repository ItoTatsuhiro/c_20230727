#pragma once
#include <vector>
#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/GameManager.h"
#include "../base/CharacterBase.h"
#include "../common/AnimManager.h"
#include "../common/GraphicManager.h"


// csv内に記載のある項目のenum class
enum class PLAYER_CSV {
	WIDTH = 0,		// 幅
	HEIGHT,			// 高さ
	START_POS,		// 初期位置
	MOVE_SPEED,		// 移動速度
	JUMP,			// ジャンプ力
	GRAVITY,		// 重力
	HP,				// 体力
	MAX				//項目の数
};

class Player : public CharacterBase {
public :

	Player(tnl::Vector3 PLAY_AREA_SIZE_MAX_, tnl::Vector3 PLAY_AREA_SIZE_MIN_);
	~Player();

	void update(float delta_time) override;
	void draw(float delta_time) override;

	tnl::Vector3 set_play_Area_Size_Max(tnl::Vector3 PLAY_AREA_SIZE_MAX_);		// プレイヤー等のオブジェクトを表示させる際の最大位置を取得する関数
	tnl::Vector3 set_play_Area_Size_Min(tnl::Vector3 PLAY_AREA_SIZE_MIN_);		// プレイヤー等のオブジェクトを表示させる際の最小位置を取得する関数

	// プレイヤーの座標を取得する
	tnl::Vector3& getPlayerPos();
	void setPlayerPos(const tnl::Vector3& newPlayerPos);
	//int& get_playerRadius();

	// プレイヤーの移動速度(移動量)を取得する
	const float& get_move_speed_();

	const int& get_WIDTH();
	const int& get_HEIGHT();

	//// 移動量を取得する関数
	//const tnl::Vector3& get_moveValue_();

	// hpの値を取得する関数
	const float& get_hp_();

	// hpの値を変更する関数
	void set_hp_(const float damage);

	// 被ダメージ時の無敵時間を取得
	const float& get_hitInterval_() { return hitInterval_; }

	// 被ダメージ後の時間
	const float& get_hitIntervalCount_() { return hitIntervalCount_; }

	// 被ダメージ後の時間をsetする関数
	void set_hitIntervalCount_(float time);

	// ジャンプできる最大回数を取得する関数
	const int get_jumpMax_() { return jumpMax_; };

	// ジャンプ回数のカウントを取得する関数
	const int get_jumpCount_() { return jumpCount_; };

	// ジャンプ回数をセットする関数
	void set_jumpCount_(int count);

private :

	// プレイヤーの画像アニメーションの読み込み
	std::vector<int> player_anim_hdl_;

	std::vector < std::vector<tnl::CsvCell>> playerData_;		// プレイヤーのデータを入れる用

	float anim_time_change_ = 0.1f;	// アニメーションを切り替える時間
	float anim_time_count_ = 0;		// アニメーションを再生する時間をカウントする用
	int anim_ctrl_flame_ = 0;		// アニメーションの描画する画像を変更する用

	float anim_size_ = 2.0f;		// アニメーションの大きさの倍率

	float hpMax_ = 1;								// 体力の最大値
	float hp_ = hpMax_;								// 体力

	int hp_gpc_hdl_ = 0;							// 体力を表示する用の画像

	float hitInterval_ = 2.5f;						// 被ダメージ時の無敵時間
	float hitIntervalCount_ = hitInterval_;			// 被ダメージ後の時間

	float hitFlashTime_ = 0.05f;						// 被ダメージ時の点滅の間隔
	float hitFlashTimeCount_ = hitFlashTime_;		// 点滅の間隔をカウントする用

	int jumpMax_ = 1;				// ジャンプできる回数
	int jumpCount_ = 0;				// ジャンプ回数のカウント

	// プレイヤーが表示されているか否か
	bool playerView_ = true;			

	// プレイヤーのHPを表示させる座標
	tnl::Vector3 hp_gpc_pos_ = { 100, 100, 0 };

	// playerの大きさ
	//int player_r = 10;

	void move(float delta_time) override;

	// プレイヤー初期位置
	 tnl::Vector3 startPos_ = { 0, 0, 0 };


	tnl::Vector3 play_Area_Size_Max;		// プレイヤー等のオブジェクトを表示させる際の最大位置
	tnl::Vector3 play_Area_Size_Min;		// プレイヤー等のオブジェクトを表示させる際の最小位置

	int jumpSound_hdl_ = 0;	// ジャンプの効果音

	int damageSound_hdl_ = 0;// ダメージの効果音


};


