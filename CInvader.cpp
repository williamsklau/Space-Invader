#include "stdafx.h"
#include "CInvader.h"

CInvader::CInvader() {
	_lives = 1;
	_vel = Point2f(invaderSpeed, 0);
	_shape = Rect(_pos.x, _pos.y, 25, 25);
}

void CInvader::changeDir() {
	_vel.x *= -1;
	_pos.x += 2 * _vel.x;
	_pos.y += 10;
}