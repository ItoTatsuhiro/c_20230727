#pragma once
#include "../../dxlib_ext/dxlib_ext.h"



// マップチップに使用する用の定数
enum class MAPCHIP {
	AIR,			// 0：配置なし
	BLOCK,			// 1：地面
	SPIKE,			// 2：障害物(棘)
	MAX				// マップチップの種類の総数
};


class MapChipBase {
public :

	MapChipBase( const tnl::Vector3& pos, MAPCHIP chipType);
	virtual ~MapChipBase();

	// 当たり判定の有無を取得する
	bool& getCollision();

	// 座標を取得する
	tnl::Vector3& getPos_();

	// 座標を変更する関数
	void setPos_(const tnl::Vector3& newPos);

	// ダメージの有無を取得する関数
	const bool& get_has_damage_();

	// ダメージの値を取得する関数
	const float& get_damageVal_();

	// チップの種類を取得するための関数
	MAPCHIP get_chipType_();

	// オブジェクトと接触した際の処理
	virtual void onCollision_() = 0 {};


protected :

	MAPCHIP chipType_ = MAPCHIP::AIR;	// チップの種類
	bool collision_ = true;		// 当たり判定の有無
	bool has_damage_ = false;	// 接触時のダメージの有無
	float damageVal_ = 0;		// ダメージの値
	tnl::Vector3 pos_;			// 配置されている座標


};

