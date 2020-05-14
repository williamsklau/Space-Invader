#pragma once

#include <chrono>
#include <thread>
#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

#include "CBase4618.h"
#include "CShip.h"
#include "CInvader.h"
#include "CMissile.h"

#define msDelay_fps 1000/60
#define game_height 1000
#define game_width 1000

using namespace std;

/**
*
* @brief Runs and updates invader games. Inherits from CBase4618
*
* Checks and updates the position and status of all objects
*
* @author William Lau
*
*/
class CSpaceInvaderGame : public CBase4618
{
private:
	CShip ship;
	vector <CInvader> invader;
	vector <CMissile> missile_ship;
	vector <CMissile> missile_invader;
	int score = 0;
	double start_t = 0; ///< Holds the start time of draw(). Used for FPS control and ball velocity control
	double freq; ///< Holds the frequency value of CPU
	double elapsed_t = 0; ///< Holds time of when draw() finishes running. Used for FPS control and ball velocity control
	cv::Point2f joystick;  ///< Coordinate from joystick input. Scaled from 0.0-1.0
	enum {PUSH1 = 32, PUSH2 = 33 }; ///< emunerators used
	bool resetFlag = 0, missileFlag = 0;
public:
	CSpaceInvaderGame();
	void update();
	void draw();
	void createInvader();
	void reset();
	void endgame();
};

