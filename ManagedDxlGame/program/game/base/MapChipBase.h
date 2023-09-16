#pragma once
#include "../../dxlib_ext/dxlib_ext.h"



// マップチップに使用する用の定数
enum class MAPCHIP {
	AIR,			// 0：配置なし
	BLOCK,			// 1：地面
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



protected :

	MAPCHIP chipType_ = MAPCHIP::AIR;	// チップの種類
	bool collision_ = true;		// 当たり判定の有無
	tnl::Vector3 pos_;			// 配置されている座標


};

