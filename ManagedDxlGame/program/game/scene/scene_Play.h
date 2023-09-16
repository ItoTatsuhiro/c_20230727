#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/GraphicManager.h"
#include "../base/SceneBase.h"
#include "../object/Player.h"
#include "../object/Stage.h"


class ScenePlay : public SceneBase {
public :
	ScenePlay();
	~ScenePlay();

	void update(float delta_time);
	void draw();

	// オブジェクトの表示範囲を取得する用の関数
	tnl::Vector3 get_PLAY_AREA_SIZE_MAX();		// オブジェクトの表示範囲の最大値を取得する関数
	tnl::Vector3 get_PLAY_AREA_SIZE_MIN();		// オブジェクトの表示範囲の最小値を取得する関数

private :
	// シーン切り替え用
	bool seqIdle(const float delta_time);
	tnl::Sequence<ScenePlay> sequence_ = tnl::Sequence<ScenePlay>(this, &ScenePlay::seqIdle);

	// プレイヤーを生成する用のポインタ変数
	Player* player_ = nullptr;

	// 
	Stage* stage_ = nullptr;

	// プレイヤー等のオブジェクトを表示させる際の表示範囲
	const tnl::Vector3 PLAY_AREA_SIZE_MAX = { 1000, 720, 0 };		// プレイヤー等のオブジェクトを表示させる際の最大位置
	const tnl::Vector3 PLAY_AREA_SIZE_MIN = { 0, 0, 0 };			// プレイヤー等のオブジェクトを表示させる際の最小位置

	// 当たり判定用
	void hitCheck();

};
