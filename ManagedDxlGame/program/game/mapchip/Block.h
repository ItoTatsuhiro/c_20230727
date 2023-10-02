#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../base/MapChipBase.h"

class Block : public MapChipBase {
public :

	Block(const tnl::Vector3& pos, MAPCHIP chipType);
	~Block() {};

	// オブジェクトに接触した際の処理
	void onCollision_() override;

private :


};
