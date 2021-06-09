// ArduCam_test.cpp : Defines the entry point for the console application.
//
#ifdef linux
#include "Arducam_SDK/ArduCamLib.h"
#include <unistd.h>
#include <termios.h>
#endif

#ifdef _WIN32
#include <Windows.h>
#include "ArduCamlib.h"
#include <io.h>
#include <direct.h> 
#include <conio.h>
#endif
#include <opencv2/opencv.hpp>
#include <thread>
#include <time.h>
#include <iostream>
#include <istream>
#include <string>
#include "Utils.h"
#include "Arducam.hpp"

using namespace std;
using namespace cv;

void delay_ms(int mills) {
#ifdef linux
	usleep(mills * 1000);
#endif
#ifdef _WIN32
	Sleep(mills);
#endif
}

static void display_fps(int index) {
	static thread_local int frame_count = 0;
	static thread_local time_t start = time(NULL);

	frame_count++;

	time_t end = time(NULL);
	if (end - start >= 1) {
		start = end;
		std::cout << "camera: "<< index <<  ", fps: " << frame_count << std::endl;
		frame_count = 0;
	}
}

void display(ArducamCamera *camera, int index) {
	while (true) {
		ArduCamOutData* frameData;
		if (!camera->read(frameData)) {
			std::cout << "read frame failed." << std::endl;
			continue;
		}
		// cv::Mat rawImage = UnpackRaw10(frameData, 2);
		cv::Mat image = ConvertImage(frameData);
		camera->returnFrameBuffer();

        std::cout << "time: " << frameData->u64Time << std::endl;
		// rawImage.convertTo(rawImage, CV_16UC1, 64);
		// cv::Mat image;
		// cv::cvtColor(rawImage, image, cv::COLOR_BayerGB2BGR);
		if (!image.data) {
			std::cout << "No image data" << std::endl;
			continue;
		}
		display_fps(index);

		double scale = 640.0 / image.cols;
		cv::resize(image, image,
			cv::Size(), scale, scale, cv::INTER_LINEAR);

		std::string name = "ArduCam";
		name += std::to_string(index);
		cv::imshow(name, image);

		int key = -1;
		key = cv::waitKey(1);
		if (key == 'q')
			break;
	}

	camera->stop();

	camera->closeCamera();
}


// #define CAMERA1
int main(int argc,char **argv)
{
	const char * config_file_name;
	if(argc > 1){
		config_file_name = argv[1];
	}else{
		showHelp();
		return 0;
	}


	ArducamCamera *camera = new ArducamCamera();
	
	if (!camera->openCamera(config_file_name, 0)) {
		std::cout << "Failed to open camera." << std::endl;
		return 0;
	}

#if defined(CAMERA1)
	ArducamCamera *camera1 = new ArducamCamera();
	if (!camera1->openCamera(config_file_name, 1)) {
		std::cout << "Failed to open camera." << std::endl;
		return 0;
	}
#endif

	camera->start();
	camera->setCtrl("setFramerate", 30);
	camera->setCtrl("setExposure", 1600);
	camera->setCtrl("setGain", 0);
	std::thread camera_display(display, camera, 0);

#if defined(CAMERA1)
	camera1->start();
	std::thread camera_display1(display, camera1, 1);
#endif

	camera_display.join();
#if defined(CAMERA1)
	camera_display1.join();
#endif
	return 0;
}


