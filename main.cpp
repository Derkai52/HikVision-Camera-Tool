#include <iostream>
#include "opencv2/opencv.hpp"
#include "hikvision_camera.h"
#include "calibration/cameraCalibration.h"

using namespace std;
using namespace cv;
using namespace camera;

HikCamera MVS_cap; // 创建一个相机对象

int main() {
    Mat src;
    const string camera_config_path = HIK_CONFIG_FILE_PATH"/camera_config.yaml";  // 相机配置文件路径
    const string intrinsic_para_path = HIK_CALI_FILE_PATH"/caliResults/calibCameraData.yml"; // 相机内参文件路径
    //    CCalibration::cameraCali(); // 相机标定示例(取消注释即可使用)
    auto time_start = std::chrono::steady_clock::now(); // 记录相机初始化时间戳

    MVS_cap.Init(true, camera_config_path, intrinsic_para_path, time_start);  // 初始化相机
    MVS_cap.CamInfoShow(); // 显示图像参数信息
    while (true) {
        MVS_cap.ReadImg(src); // 相机取图
        if (src.empty()) { // 相机开启线程需要一定时间
            continue;
        }
        //  MVS_cap.undistProcess(src); // 相机畸变矫正示例(取消注释即可使用)
        cout << "相机触发时间戳序列: "<< MVS_cap.Get_TIMESTAMP() << endl;
        cv::resize(src, src, cv::Size(640,480));
        cv::imshow("HikCamera_GetImage", src);
        cv::waitKey(1);
    }
    return 0;
}