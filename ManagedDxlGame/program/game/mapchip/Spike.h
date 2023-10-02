#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../base/MapChipBase.h"

class Spike : public MapChipBase {
public:

	Spike(const tnl::Vector3& pos, MAPCHIP chipType);
	~Spike() {};

	void onCollision_() override;

private:


};