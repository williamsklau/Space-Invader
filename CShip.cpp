#include "stdafx.h"
#include "CShip.h"

CShip::CShip() {
	_lives = 3;
	_shape = Rect(_pos.x, _pos.y, 50, 15);
}
