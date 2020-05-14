#include "stdafx.h"
#include "CBase4618.h"

#include <chrono>
#include <thread>
#include <conio.h>

using namespace std;

void CBase4618::run() {
	
	char quit_ch;

	do {
			draw();
	} while (cv::waitKey(1) != 'q');

}