#include <stdio.h>
#include <pthread.h>
#include <opencv2/opencv.hpp>
#include "MvErrorDefine.h"
#include "CameraParams.h"
#include "MvCameraControl.h"

#ifndef HIKVISION_CAMERA_TOOL_TEST_H
#define HIKVISION_CAMERA_TOOL_TEST_H

namespace camera
{
    //************************ 相机参数表 ************************************/
    enum CamerProperties
    {
        CAP_PROP_FRAMERATE_ENABLE,  //采集帧率可调
        CAP_PROP_FRAMERATE,         //采集帧率
        CAP_PROP_BURSTFRAMECOUNT,   //外部单次触发采集帧数
        CAP_PROP_HEIGHT,            //图像高度
        CAP_PROP_WIDTH,             //图像宽度

        CAP_PROP_EXPOSURE_MODE,     //曝光模式(0:手动 1：一次 2：连续)
        CAP_PROP_EXPOSURE_TIME,     //曝光时间
        CAP_PROP_GAMMA_ENABLE,      //伽马因子可调
        CAP_PROP_GAMMA,             //伽马因子
        CAP_PROP_GAINAUTO,          //Gain增益模式(0:手动 1：一次 2：连续)
        CAP_PROP_GAIN,              //Gain增益
        CAP_PROP_SATURATION_ENABLE, //饱和度可调
        CAP_PROP_SATURATION,        //饱和度
        CAP_PROP_BALANCEWHITE_MODE, //白平衡模式(0:手动 1：一次 2：连续)

        CAP_PROP_OFFSETX,           //X偏置
        CAP_PROP_OFFSETY,           //Y偏置
        CAP_PROP_TRIGGER_MODE,      //外部触发
        CAP_PROP_TRIGGER_SOURCE,    //触发源
        CAP_PROP_LINE_SELECTOR      //触发线

    };

    //^ ********************************** 海康相机类 ************************************ //
    class HikCamera
    {
    public:
        ~HikCamera();

        //*********** 相机初始化 ******************/
        void Init(bool debug_flag, const std::string &config_path, const std::string &intrinsic_para_file_path, std::chrono::_V2::steady_clock::time_point time_start);
        //********** 相机工作线程 ******************/
        static void *HKWorkThread(void *arg);
        //********** 输出设备信息 ******************/
        bool PrintDeviceInfo(MV_CC_DEVICE_INFO *pstMVDevInfo);
        //********** 输出相机参数信息 **************/
        bool CamInfoShow();
        //********** 设置相机参数 *****************/
        bool set(camera::CamerProperties type, float value);
        //********** 恢复相机默认参数 **************/
        bool reset();
        //********** 读相机的原始图像 **************/
        void ReadImg(cv::Mat &image);
        //********** 对相机调参并实时查看效果 *******/
        static void DebugCam(void *p_handle, MV_CC_DEVICE_INFO *pDeviceInfo);
        //********** 相机畸变矫正 *****************/
        bool undistProcess(cv::Mat src);
        bool readParams();
        struct CameraCalibrationStruct {
            float fx, fy, u0, v0;                 // 相机内参矩阵
            float k_1, k_2, p_1, p_2, k_3;        // 相机畸变矩阵
            CameraCalibrationStruct() { // 内参矩阵(缺省值)
                fx = 1.8133723144531250e+03f;
                fy = 1.8104567871093750e+03f;
                u0 = 7.2068243408203125e+02f;
                v0 = 5.5575854492187500e+02f;
                k_1 = -1.0287012904882431e-01f;
                k_2 = 4.7102910280227661e-01f;
                p_1 = -1.7599905550014228e-04f;
                p_2 = -2.8243704582564533e-04f;
                k_3 = -1.1573969125747681e+00f;
            }
        };
        CameraCalibrationStruct readCalibrationData(const std::string &filename);
        //********** 相机畸变矫正 *****************/
        //采集一张图像更新一次时间戳
        bool UpdateTimestampOffset(std::chrono::_V2::steady_clock::time_point time_start);
        //读取相机时间戳
        int Get_TIMESTAMP();

    private:
        void *handle;            // 相机操作句柄
        std::string CameraConfigFilePath; // 相机参数配置文件路径
        std::string CameraIntrinsicParaFilePath; // 相机内参文件路径
        pthread_t nThreadID;     // 相机工作线程
        std::chrono::_V2::steady_clock::time_point time_start; // 相机初始化时间戳

        //********** 相机数据 **************/
        cv::Mat K = cv::Mat::eye(cv::Size(3, 3), CV_32FC1);
        cv::Mat R;
        cv::Mat discoeff = cv::Mat::eye(cv::Size(1, 5), CV_32FC1);

        //********** 海康相机参数表(缺省值) **************/
        int nRet;
        int width = 1280;
        int height = 960;
        int Offset_x = 0;
        int Offset_y = 0;
        bool FrameRateEnable = false;
        float FrameRate = 100.0;
        int BurstFrameCount = 1;

        int ExposureMode = 0;
        int ExposureTime = 5000;
        bool GammaEnable = true;
        float Gamma = 0.7;
        int GainAuto = 2;
        float Gain = 15.0;
        bool SaturationEnable = false;
        int Saturation = 128;
        int BalanceWhiteMode = 0;
        int BalanceRatio_Red = 1400;
        int BalanceRatio_Green = 1000;
        int BalanceRatio_Blue = 2000;

        int TriggerMode = 1;
        int TriggerSource = 99;
        int LineSelector = 99;
    };

} // namespace camera

#endif //HIKVISION_CAMERA_TOOL_TEST_H
