#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../base/MapChipBase.h"

class Block : public MapChipBase {
public :

	Block(const tnl::Vector3& pos, MAPCHIP chipType);
	~Block() {};

	// �I�u�W�F�N�g�ɐڐG�����ۂ̏���
	void onCollision_() override;

private :


};
