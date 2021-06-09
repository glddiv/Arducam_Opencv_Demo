#pragma once

#if defined(linux)
#include "Arducam_SDK/ArduCamLib.h"
#include <unistd.h>
#endif

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#include "ArduCamlib.h"
#endif

#include <opencv2/opencv.hpp>
#include <thread>
#include <time.h>
#include <iostream>
#include <thread>
#include <string>
#include "arducam_config_parser.h"
#include "Utils.h"
#include "Semaphore.hpp"

class ArducamCamera {
public:
	ArducamCamera(){}
	~ArducamCamera() {}

	bool openCamera(std::string fname, int index = 0);
	void closeCamera();

	void start();
	void stop();

	bool read(ArduCamOutData* &frameData);
	void returnFrameBuffer();

	int setCtrl(std::string name, int64_t val);

private:
	void capture();

private:
	Semaphore captureSem;
	std::thread captureThread;
	ArduCamHandle handle = nullptr;
	ArduCamCfg cameraCfg = {};
	volatile bool _running = false;

};
