#pragma once

#include "CGameObject.h"

#define invaderSpeed 8

/**
*
* @brief Child class of CGameObject. Holds method run() which calls pure virtual methods update() & draw() when 'q' is not pressed.
*
* Sets size and shape of missile
*
* @author William Lau
*
*/
class CInvader : public CGameObject
{
private:
public:
	CInvader();
	void changeDir();
};

