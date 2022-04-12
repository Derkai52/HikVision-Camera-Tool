#ifndef HIKVISION_CAMERA_TOOL_CAMERA_PARMS_DEBUG_H
#define HIKVISION_CAMERA_TOOL_CAMERA_PARMS_DEBUG_H

#include <iostream>
#include <opencv2/highgui.hpp>
#include "MvCameraControl.h"

using namespace std;
using namespace cv;

// 滑动条函数声明

void exposureTrackbar(int, void *);

void gainTrackbar(int, void *);

void gammasTrackbar(int, void *);

void balanceRatioRedTrackbar(int, void *);

void balanceRatioGreenTrackbar(int, void *);

void balanceRatioBlueTrackbar(int, void *);

void debugcam(void *p_handle, MV_CC_DEVICE_INFO *pDeviceInfo);



#endif //HIKVISION_CAMERA_TOOL_CAMERA_PARMS_DEBUG_H
