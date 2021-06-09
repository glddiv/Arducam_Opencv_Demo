#pragma once
#ifndef _ARDUCAM_UTILS_H_
#define _ARDUCAM_UTILS_H_
#include <iostream>
#include "ArduCamLib.h"
#include <opencv2/opencv.hpp>

extern bool save_raw;
extern int color_mode;
extern ArduCamCfg cameraCfg;
void showHelp();
bool camera_initFromFile(std::string filename, ArduCamHandle &cameraHandle, ArduCamCfg &cameraCfg, int index = 0);
cv::Mat ConvertImage(ArduCamOutData* frameData);
cv::Mat UnpackRaw10(ArduCamOutData* frameData, int drop_row = 0);
#endif // !
