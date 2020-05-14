#include "stdafx.h"
#include "CGameObject.h"

#include <iostream>
#include <string>

using namespace std;

CGameObject::CGameObject() {
	freq = cv::getTickFrequency();
}

void CGameObject::move() {
	//start_t = cv::getTickCount();
	//elapsed_t = (cv::getTickCount() - start_t) / freq;
	_pos += _vel;
}

bool CGameObject::collide(CGameObject& obj) {
	if (_shape.contains(obj.get_pos()) || _shape.contains(obj.get_pos() + Point2f(_shape.width, 0)))
		return 1;
	else
		return 0;
}

bool CGameObject::collide_wall(Size board) {
	if (_shape.x + _shape.width > board.width || 
		_shape.x < 0 || 
		_shape.y > board.height || 
		_shape.y + _shape.height < 0)

		return 1;
	else
		return 0;
}

void CGameObject::hit() {

}

void CGameObject::draw(Mat& im) {
	//cout << _pos << endl;
	//cout << _shape << endl << endl;
 	_shape.x = _pos.x;
	_shape.y = _pos.y;
	cv::rectangle(im, _shape, cv::Scalar(255, 255, 255), cv::FILLED, cv::LINE_AA);
}