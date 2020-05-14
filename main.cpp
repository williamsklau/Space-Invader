////////////////////////////////////////////////////////////////
// ELEX 4618 Lab 6
////////////////////////////////////////////////////////////////
// ISSUES:
// 
////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <string>
#include <iostream>
#include <thread>

#include "CSpaceInvaderGame.h"
#include "Serial.h" // Must include Windows.h after Winsock2.h, so Serial must include after Client/Server

// OpenCV Include
#include "opencv.hpp"

// OpenCV Library
#pragma comment(lib,".\\opencv\\lib\\opencv_world310d.lib")

void main(){
	CSpaceInvaderGame game;
	game.run();
}