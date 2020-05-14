#pragma once

#include "opencv.hpp"

using namespace cv;


/**
*
* @brief Parent class of CShip, CMissile, CInvader.
*
* Holds common methods and variables of pertinent objects.
*
* @author William Lau
*
*/
class CGameObject {
protected:
	Point2f _pos;
	Point2f _vel;
	Rect _shape;
	int _lives;
	double start_t = 0; ///< Holds the start time of draw(). Used for FPS control and ball velocity control
	double freq; ///< Holds the frequency value of CPU
	double elapsed_t = 0; ///< Holds time of when draw() finishes running. Used for FPS control and ball velocity control

public:
	CGameObject();
	void move();
	bool collide(CGameObject& obj);
	bool collide_wall(Size board);
	void hit();
	void draw(Mat& im);

	// Setters & getters
	int get_lives() { return _lives; }
	void set_lives(int lives) { _lives = lives; }
	void set_pos(Point2f pos) { _pos = pos; }
	void set_vel(Point2f vel) { _vel = vel; }
	Point2f get_pos() { return _pos; }
};