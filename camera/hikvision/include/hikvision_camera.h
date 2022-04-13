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
        void Init();
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



    private:
        void *handle;            // 相机操作句柄
        std::string config_yaml; // 相机参数配置文件路径
        pthread_t nThreadID;     // 相机工作线程

        //********** 海康相机参数表(同上) **************/
        int nRet;
        int width;
        int height;
        int Offset_x;
        int Offset_y;
        bool FrameRateEnable;
        int FrameRate;
        int BurstFrameCount;

        int ExposureMode;
        int ExposureTime;
        bool GammaEnable;
        float Gamma;
        int GainAuto;
        float Gain;
        bool SaturationEnable;
        int Saturation;
        int BalanceWhiteMode;
        int BalanceRatio_Red;
        int BalanceRatio_Green;
        int BalanceRatio_Blue;

        int TriggerMode;
        int TriggerSource;
        int LineSelector;


    };

} // namespace camera

#endif //HIKVISION_CAMERA_TOOL_TEST_H
