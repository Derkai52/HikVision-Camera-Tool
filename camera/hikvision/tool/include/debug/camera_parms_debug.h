#ifndef HIKVISION_CAMERA_TOOL_CAMERA_PARMS_DEBUG_H
#define HIKVISION_CAMERA_TOOL_CAMERA_PARMS_DEBUG_H

#include <iostream>
#include <opencv2/highgui.hpp>
#include "MvCameraControl.h"
//#include "hikvision_camera.h"

using namespace std;
using namespace cv;

// 滑动条函数声明
static void exposureTrackbar(int, void *);

static void gainTrackbar(int, void *);

static void gammasTrackbar(int, void *);

static void balanceRatioRedTrackbar(int, void *);

static void balanceRatioGreenTrackbar(int, void *);

static void balanceRatioBlueTrackbar(int, void *);

void debugcam(void *p_handle, MV_CC_DEVICE_INFO *pDeviceInfo);



#endif //HIKVISION_CAMERA_TOOL_CAMERA_PARMS_DEBUG_H
