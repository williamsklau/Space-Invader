#include "stdafx.h"
#include "CMissile.h"

CMissile::CMissile() {
	_lives = 1;
	_vel = Point2f(0, -missileSpeed);
	_shape = Rect(_pos.x, _pos.y, 2, 5);
}