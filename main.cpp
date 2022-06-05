#include <iostream>
#include "opencv2/opencv.hpp"
#include "hikvision_camera.h"
#include "calibration/cameraCalibration.h"

using namespace std;
using namespace cv;
using namespace camera;

HikCamera MVS_cap; // 创建了一个相机对象

int main() {
    Mat src;
//  CCalibration::cameraCali(); // 相机标定示例
    MVS_cap.Init();        // 初始化相机
    MVS_cap.CamInfoShow(); // 显示图像参数信息
    while (true) {
        MVS_cap.ReadImg(src); // 相机取图
        if (src.empty()) { // 相机开启线程需要一定时间
            continue;
        }
        MVS_cap.undistProcess(src);
//        cv::imshow("HikCamera_GetImage", src);
        cv::waitKey(1);
    }
    return 0;
}