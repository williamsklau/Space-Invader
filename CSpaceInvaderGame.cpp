/*
TO DO LIST:

debounce pushbutton

*/


#include "stdafx.h"
#include "CSpaceInvaderGame.h"

using namespace std;

CSpaceInvaderGame::CSpaceInvaderGame() {
	// initiate objects
	_msp.init_com(5);
	_canvas = cv::Mat::zeros(game_height, game_width, CV_8UC3);
	freq = cv::getTickFrequency();

	createInvader();
	
}

void CSpaceInvaderGame::update() {
	int testNum = 1;

	_msp.get_joystick(joystick.x, joystick.y);
	resetFlag = _msp.get_button(PUSH1);
	missileFlag = _msp.get_button(PUSH2);

	// move ship
	ship.set_pos(cv::Point(game_width*joystick.x, game_height-60));

	// create missile_invader
	missile_invader.push_back(CMissile());
	if (invader.size() > 0) {
		missile_invader[missile_invader.size() - 1].set_pos(invader[(cv::getTickCount() % invader.size())].get_pos() + Point2f(12, 10));
		missile_invader[missile_invader.size() - 1].set_vel(Point2f(0, 30));
	}
	

	// push1 -> create missile_ship
	if (missileFlag == 1) {
		cout << "missile!\n";

		missile_ship.push_back(CMissile());
		missile_ship[missile_ship.size() - 1].set_pos(ship.get_pos() + Point2f(25,-10));
	}

	// check invader wall collision
	for (int count_wall = 0; count_wall < invader.size(); count_wall++) {
		if (invader[count_wall].collide_wall(_canvas.size()) == 1) {
				//cout << "invader" << count_wall << " = " << invader[count_wall].get_pos() << endl;
			for (int count_changeDir = 0; count_changeDir < invader.size(); count_changeDir++) {
				invader[count_changeDir].changeDir();
			}
			break;
		}
	}

	// check missile wall/invader/ collision
	for (int count_missile = 0; count_missile < missile_ship.size(); count_missile++) {
		if (missile_ship[count_missile].collide_wall(_canvas.size()) == 1) { 
			missile_ship.erase(missile_ship.begin() + count_missile);
		}

		for (int count_invade_check = 0; count_invade_check < invader.size(); count_invade_check++) {
			if (missile_ship.size() > 0 && invader.size() > 0 && invader[count_invade_check].collide(missile_ship[count_missile]) == 1) {
				missile_ship.erase(missile_ship.begin() + count_missile);
				invader.erase(invader.begin() + count_invade_check);
				score += 10;
			}
		}
}

	// check missile->ship/wall collision
	for (int count_missile_invade = 0; count_missile_invade < missile_invader.size(); count_missile_invade++) {
		// check for wall
		if (missile_invader[count_missile_invade].collide_wall(_canvas.size()) == 1) {
			missile_invader.erase(missile_invader.begin() + count_missile_invade);
		}

		for (int count_ship_check = 0; count_ship_check < invader.size(); count_ship_check++) {
			if (missile_invader.size() > 0 && ship.collide(missile_invader[count_missile_invade]) == 1) {
				int ship_lives = 0;
				missile_invader.erase(missile_invader.begin() + count_missile_invade);
				ship_lives = ship.get_lives() - 1;
				ship.set_lives(ship_lives);
			}
		}

	}

	// move invaders
	for (int count_invade = 0; count_invade < invader.size(); count_invade++) {
		invader[count_invade].move();
	}

	// move missile_ship
	for (int count_missile = 0; count_missile < missile_ship.size(); count_missile++) {
		missile_ship[count_missile].move();
	}

	// move missile_invader
	for (int count_missile = 0; count_missile < missile_invader.size(); count_missile++) {
		missile_invader[count_missile].move();
	}


	// push 2 -> reset game
	if (resetFlag == 1) {
		cout << "reset!\n";
		reset();
	}
	
}

void CSpaceInvaderGame::draw() {
	// Set update rate
	auto end_time = chrono::system_clock::now() + chrono::milliseconds(msDelay_fps);
	start_t = cv::getTickCount();

	update();

	// endgame 
	if (ship.get_lives() <= 0 || invader.size()  <= 0) {
		endgame();
	}

	// Draw ship
	ship.draw(_canvas);

	// Draw invader 
	for (int count_invader = 0; count_invader < invader.size(); count_invader++) {
		invader[count_invader].draw(_canvas);
	}

	// Draw missile_ship
	for (int count_missile = 0; count_missile < missile_ship.size(); count_missile++) {
		missile_ship[count_missile].draw(_canvas);
	}
	
	// Draw missile_invader
	for (int count_missile_invader = 0; count_missile_invader < missile_invader.size(); count_missile_invader++) {
		missile_invader[count_missile_invader].draw(_canvas);

	}


	// Display FPS, score, life
	//cv::putText(_canvas, to_string(1 / elapsed_t), cv::Point(800, 30), cv::FONT_HERSHEY_SIMPLEX, 0.5, cvScalar(250, 250, 250), 1, CV_AA);
	cv::putText(_canvas, "Score: " + to_string(score), cv::Point(100, 30), cv::FONT_HERSHEY_SIMPLEX, 0.5, cvScalar(250, 250, 250), 1, CV_AA);
	cv::putText(_canvas, "Life: " + to_string(ship.get_lives()), cv::Point(500, 30), cv::FONT_HERSHEY_SIMPLEX, 0.5, cvScalar(250, 250, 250), 1, CV_AA);


	cv::imshow("Image", _canvas);
	cv::waitKey(1);

	// Clear screen
	_canvas = cv::Mat::zeros(game_height, game_width, CV_8UC3);

	this_thread::sleep_until(end_time);
	elapsed_t = (cv::getTickCount() - start_t) / freq;

}

void CSpaceInvaderGame::createInvader() { 

	for (int invaderCol = 0; invaderCol < 5; invaderCol++) {
		for (int invaderRow = 0; invaderRow < 3; invaderRow++) {
			invader.push_back(CInvader());
			invader[invader.size()-1].set_pos(Point2f(invaderRow * 75 + 100, invaderCol * 50 + 100));
		}
	}
}

void CSpaceInvaderGame::reset() {
	score = 0;
	ship.set_lives(3);

	invader.clear();
	missile_ship.clear();

	createInvader();

}

void CSpaceInvaderGame::endgame() {
	missile_ship.clear();
	missile_invader.clear();

	cv::putText(_canvas, "Game Over", cv::Point(300, 400), cv::FONT_HERSHEY_SIMPLEX, 2, cvScalar(250, 250, 250), 1, CV_AA);
}