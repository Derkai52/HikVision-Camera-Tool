#include <stdio.h>
#include <pthread.h>
#include <opencv2/opencv.hpp>
#include "MvErrorDefine.h"
#include "CameraParams.h"
#include "MvCameraControl.h"

namespace camera
{
    unsigned int g_nPayloadSize = 0; // 初始化分配空间
    cv::Mat frame;                   // 获得的Mat类型图像
    bool frame_empty = 0;            // 空图像数
    pthread_mutex_t mutex;           // 互斥锁


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
    class Camera
    {
    public:
        Camera();
        ~Camera();

        //********** 相机工作线程 ******************/
        static void *HKWorkThread(void *p_handle);
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

    private:
        void *handle; // 相机操作句柄
        pthread_t nThreadID;

        //********** 相机参数表(同上) **************/
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

    //^ ********************************** 相机初始化 ************************************ //
    Camera::Camera()
    {
        handle = NULL;

        //****************** 1、读取待设置的摄像头参数默认值 ************************/
        // yaml文件未给出时生效
        this->width = 1440;
        this->height = 1080;
        this->FrameRateEnable = true;
        this->FrameRate = 100;
        this->BurstFrameCount = 1; // 一次触发采集的帧数
        this->ExposureMode = 0;
        this->ExposureTime = 10000;
        this->GammaEnable = true;
        this->Gamma = 0.7;
        this->GainAuto = 0;
        this->Gain = 15;
        this->SaturationEnable = true;
        this->Saturation = 128;
        this->BalanceWhiteMode = 0;
        this->BalanceRatio_Red = 1400;
        this->BalanceRatio_Green = 1000;
        this->BalanceRatio_Blue = 2000;
        this->Offset_x = 0;
        this->Offset_y = 0;
        this->TriggerMode = 1;
        this->TriggerSource = 2;
        this->LineSelector = 2;


        //****************** 2、枚举设备 **************************/
        MV_CC_DEVICE_INFO_LIST stDeviceList;
        memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
        nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);
        if (MV_OK != nRet)
        {
            printf("MV_CC_EnumDevices fail! nRet [%x]\n", nRet);
            exit(-1);
        }
        unsigned int nIndex = 0;
        if (stDeviceList.nDeviceNum > 0)
        {
            for (int i = 0; i < stDeviceList.nDeviceNum; i++)
            {
                printf("[device %d]:\n", i);
                MV_CC_DEVICE_INFO *pDeviceInfo = stDeviceList.pDeviceInfo[i];
                if (NULL == pDeviceInfo)
                {
                    break;
                }
                PrintDeviceInfo(pDeviceInfo);
            }
        }
        else
        {
            printf("Find No Devices!\n");
            exit(-1);
        }


        //***************** 3、选择设备并创建句柄 *******************/
        nRet = MV_CC_CreateHandle(&handle, stDeviceList.pDeviceInfo[0]);
        if (MV_OK != nRet)
        {
            printf("MV_CC_CreateHandle fail! nRet [%x]\n", nRet);
            exit(-1);
        }


        //****************** 4、打开设备 **************************/
        nRet = MV_CC_OpenDevice(handle);
        if (MV_OK != nRet)
        {
            printf("MV_CC_OpenDevice fail! nRet [%x]\n", nRet);
            exit(-1);
        }


        //****************** 5、获取有效载荷大小 *******************/
        MVCC_INTVALUE stParam;  //  Get payload size
        memset(&stParam, 0, sizeof(MVCC_INTVALUE));
        nRet = MV_CC_GetIntValue(handle, "PayloadSize", &stParam);
        if (MV_OK != nRet) {
            printf("Get PayloadSize fail! nRet [0x%x]\n", nRet);
        }
        g_nPayloadSize = stParam.nCurValue;


        //****************** 6、相机参数设置 **************************/
        //设置 yaml 文件里面的配置
        this->set(CAP_PROP_FRAMERATE_ENABLE, FrameRateEnable);
        if (FrameRateEnable){
            this->set(CAP_PROP_FRAMERATE, FrameRate);}
        // this->set(CAP_PROP_BURSTFRAMECOUNT, BurstFrameCount);
        this->set(CAP_PROP_HEIGHT, height);
        this->set(CAP_PROP_WIDTH, width);
        this->set(CAP_PROP_OFFSETX, Offset_x);
        this->set(CAP_PROP_OFFSETY, Offset_y);
        this->set(CAP_PROP_EXPOSURE_MODE, ExposureMode);
        this->set(CAP_PROP_EXPOSURE_TIME, ExposureTime);
        this->set(CAP_PROP_GAMMA_ENABLE, GammaEnable);
        if (GammaEnable){
            this->set(CAP_PROP_GAMMA, Gamma);}
        this->set(CAP_PROP_GAINAUTO, GainAuto);
        this->set(CAP_PROP_GAIN, Gain);
        this->set(CAP_PROP_BALANCEWHITE_MODE, BalanceWhiteMode);
        // this->set(CAP_PROP_TRIGGER_MODE, TriggerMode);
        // this->set(CAP_PROP_TRIGGER_SOURCE, TriggerSource);
        // this->set(CAP_PROP_LINE_SELECTOR, LineSelector);
        this->set(CAP_PROP_SATURATION_ENABLE, SaturationEnable);
        if (SaturationEnable){
            this->set(CAP_PROP_SATURATION, Saturation);}


        //********** 设置相机触发模式 **********/
        nRet = MV_CC_SetEnumValue(handle, "TriggerMode", 0); // 软触发
        if (MV_OK == nRet)
        {
            printf("set TriggerMode OK!\n");
        }
        else
        {
            printf("MV_CC_SetTriggerMode fail! nRet [%x]\n", nRet);
        }

        //********** 设置采集像素格式 **********/
        nRet = MV_CC_SetEnumValue(handle, "PixelFormat", PixelType_Gvsp_RGB8_Packed); // 目前 RGB
        if (MV_OK == nRet)
        {
            printf("set PixelFormat OK ! value = RGB\n");
        }
        else
        {
            printf("MV_CC_SetPixelFormat fail! nRet [%x]\n", nRet);
        }
        MVCC_ENUMVALUE t = {0};
        nRet = MV_CC_GetEnumValue(handle, "PixelFormat", &t);
        if (MV_OK == nRet)
        {
            printf("PixelFormat :%d\n", t.nCurValue); // 35127316
        }
        else
        {
            printf("get PixelFormat fail! nRet [%x]\n", nRet);
        }

        //********** 7、相机取图 **********/
        nRet = MV_CC_StartGrabbing(handle); // 开始取流
        if (MV_OK != nRet)
        {
            printf("MV_CC_StartGrabbing fail! nRet [%x]\n", nRet);
            exit(-1);
        }
        nRet = pthread_mutex_init(&mutex, NULL); //初始化互斥量
        if (nRet != 0)
        {
            perror("pthread_create failed\n");
            exit(-1);
        }
        nRet = pthread_create(&nThreadID, NULL, HKWorkThread, handle); // 开启取图线程
        if (nRet != 0)
        {
            printf("camera thread create failed.ret = %d\n", nRet);
            exit(-1);
        }
    }

    //^ ********************************** 关闭相机 ************************************ //
    Camera::~Camera()
    {
        int nRet;
        pthread_join(nThreadID, NULL);

        // 停止取流
        nRet = MV_CC_StopGrabbing(handle);
        if (MV_OK != nRet)
        {
            printf("MV_CC_StopGrabbing fail! nRet [%x]\n", nRet);
            exit(-1);
        }
        printf("MV_CC_StopGrabbing succeed.\n");

        // 关闭设备
        nRet = MV_CC_CloseDevice(handle);
        if (MV_OK != nRet)
        {
            printf("MV_CC_CloseDevice fail! nRet [%x]\n", nRet);
            exit(-1);
        }
        printf("MV_CC_CloseDevice succeed.\n");

        // 销毁句柄
        nRet = MV_CC_DestroyHandle(handle);
        if (MV_OK != nRet)
        {
            printf("MV_CC_DestroyHandle fail! nRet [%x]\n", nRet);
            exit(-1);
        }
        printf("MV_CC_DestroyHandle succeed.\n");

        // 销毁互斥量
        pthread_mutex_destroy(&mutex);
    }

    //^ ********************************** 相机配置设置 ************************************ //
    bool Camera::set(CamerProperties type, float value)
    {
        switch (type)
        {
            case CAP_PROP_FRAMERATE_ENABLE:
            {
                nRet = MV_CC_SetBoolValue(handle, "AcquisitionFrameRateEnable", value); //帧率控制使能
                if (MV_OK == nRet)
                {
                    printf("set AcquisitionFrameRateEnable OK! value=%f\n",value);
                }
                else
                {
                    printf("Set AcquisitionFrameRateEnable Failed! nRet = [%x]\n\n", nRet);
                }
                break;
            }
            case CAP_PROP_FRAMERATE:
            {
                nRet = MV_CC_SetFloatValue(handle, "AcquisitionFrameRate", value); //帧率控制量
                if (MV_OK == nRet)
                {
                    printf("set AcquisitionFrameRate OK! value=%f\n",value);
                }
                else
                {
                    printf("Set AcquisitionFrameRate Failed! nRet = [%x]\n\n", nRet);
                }
                break;
            }
            case CAP_PROP_BURSTFRAMECOUNT:
            {
                nRet = MV_CC_SetIntValue(handle, "AcquisitionBurstFrameCount", value); //单次触发采集帧数
                if (MV_OK == nRet)
                {
                    printf("set AcquisitionBurstFrameCount OK!\n");
                }
                else
                {
                    printf("Set AcquisitionBurstFrameCount Failed! nRet = [%x]\n\n", nRet);
                }
                break;
            }
            case CAP_PROP_HEIGHT:
            {
                nRet = MV_CC_SetIntValue(handle, "Height", value); //图像高度
                if (MV_OK == nRet)
                {
                    printf("set Height OK!\n");
                }
                else
                {
                    printf("Set Height Failed! nRet = [%x]\n\n", nRet);
                }
                break;
            }
            case CAP_PROP_WIDTH:
            {
                nRet = MV_CC_SetIntValue(handle, "Width", value); //图像宽度
                if (MV_OK == nRet)
                {
                    printf("set Width OK!\n");
                }
                else
                {
                    printf("Set Width Failed! nRet = [%x]\n\n", nRet);
                }
                break;
            }
            case CAP_PROP_OFFSETX:
            {
                nRet = MV_CC_SetIntValue(handle, "OffsetX", value); //图像X偏移
                if (MV_OK == nRet)
                {
                    printf("set Offset X OK!\n");
                }
                else
                {
                    printf("Set Offset X Failed! nRet = [%x]\n\n", nRet);
                }
                break;
            }
            case CAP_PROP_OFFSETY:
            {
                nRet = MV_CC_SetIntValue(handle, "OffsetY", value); //图像Y偏移
                if (MV_OK == nRet)
                {
                    printf("set Offset Y OK!\n");
                }
                else
                {
                    printf("Set Offset Y Failed! nRet = [%x]\n\n", nRet);
                }
                break;
            }
            case CAP_PROP_EXPOSURE_MODE:
            {
                nRet = MV_CC_SetExposureAutoMode(handle, ExposureMode);
                if (MV_OK == nRet)
                {
                    printf("set ExposureMode OK! value=%f\n",value);
                }
                else
                {
                    printf("Set ExposureMode Failed! nRet = [%x]\n\n", nRet);
                }
                break;
            }
            case CAP_PROP_EXPOSURE_TIME:
            {
                nRet = MV_CC_SetFloatValue(handle, "ExposureTime", value); //曝光时间
                if (MV_OK == nRet)
                {
                    printf("set ExposureTime OK! value=%f\n",value);
                }
                else
                {
                    printf("Set ExposureTime Failed! nRet = [%x]\n\n", nRet);
                }
                break;
            }
            case CAP_PROP_GAMMA_ENABLE:
            {
                nRet = MV_CC_SetBoolValue(handle, "GammaEnable", value); //伽马因子是否可调  默认不可调（false）
                if (MV_OK == nRet)
                {
                    printf("set GammaEnable OK! value=%f\n",value);
                }
                else
                {
                    printf("Set GammaEnable Failed! nRet = [%x]\n\n", nRet);
                }
                break;
            }
            case CAP_PROP_GAMMA:
            {
                nRet = MV_CC_SetFloatValue(handle, "Gamma", value); //伽马因子
                if (MV_OK == nRet)
                {
                    printf("set Gamma OK! value=%f\n",value);
                }
                else
                {
                    printf("Set Gamma Failed! nRet = [%x]\n\n", nRet);
                }
                break;
            }
            case CAP_PROP_GAINAUTO:
            {
                nRet = MV_CC_SetEnumValue(handle, "GainAuto", value); //增益模式 (0：手动 1：一次 2：连续)
                if (MV_OK == nRet)
                {
                    printf("set GainAuto OK! value=%f\n",value);
                }
                else
                {
                    printf("Set GainAuto Failed! nRet = [%x]\n\n", nRet);
                }
                break;
            }
            case CAP_PROP_GAIN:
            {
                nRet = MV_CC_SetGain(handle, Gain);
                if (MV_OK == nRet)
                {
                    printf("set Gain OK! value=%f\n",Gain);
                }
                else
                {
                    printf("Set GainAuto Failed! nRet = [%x]\n\n", nRet);
                }
                break;
            }
            case CAP_PROP_SATURATION_ENABLE:
            {
                nRet = MV_CC_SetBoolValue(handle, "SaturationEnable", value); //饱和度是否可调 默认不可调(false)
                if (MV_OK == nRet)
                {
                    printf("set SaturationEnable OK! value=%f\n",value);
                }
                else
                {
                    printf("Set SaturationEnable Failed! nRet = [%x]\n\n", nRet);
                }
                break;
            }
            case CAP_PROP_SATURATION:
            {
                nRet = MV_CC_SetIntValue(handle, "Saturation", value); //饱和度 默认128 (0~255)
                if (MV_OK == nRet)
                {
                    printf("set Saturation OK! value=%f\n",value);
                }
                else
                {
                    printf("Set Saturation Failed! nRet = [%x]\n\n", nRet);
                }
                break;
            }
            case CAP_PROP_BALANCEWHITE_MODE:
            {
                //********** 设置白平衡 **********/
                nRet = MV_CC_SetEnumValue(handle, "BalanceWhiteAuto", BalanceWhiteMode);
                if(BalanceWhiteMode==0){
                    int rgb[3] = {this->BalanceRatio_Red, this->BalanceRatio_Green, this->BalanceRatio_Blue};
                    for (int i = 0; i < 3; i++)
                    {
                        nRet = MV_CC_SetEnumValue(handle, "BalanceRatioSelector", i); // R:0 G:1 B:2
                        nRet = MV_CC_SetIntValue(handle, "BalanceRatio", rgb[i]);
                    }
                }
                if (MV_OK == nRet)
                {
                    printf("set BalanceRatio OK! value: RED=%d  Green=%d  Blue=%d\n",this->BalanceRatio_Red, this->BalanceRatio_Green, this->BalanceRatio_Blue);
                }
                else
                {
                    printf("Set BalanceRatio Failed! nRet = [%x]\n\n", nRet);
                }
            }

            case CAP_PROP_TRIGGER_MODE:
            {
                nRet = MV_CC_SetEnumValue(handle, "TriggerMode", value); //触发模式
                if (MV_OK == nRet)
                {
                    printf("set TriggerMode OK!\n");
                }
                else
                {
                    printf("Set TriggerMode Failed! nRet = [%x]\n\n", nRet);
                }
                break;
            }
            case CAP_PROP_TRIGGER_SOURCE:
            {
                nRet = MV_CC_SetEnumValue(handle, "TriggerSource", value); //触发源
                if (MV_OK == nRet)
                {
                    printf("set TriggerSource OK!\n");
                }
                else
                {
                    printf("Set TriggerSource Failed! nRet = [%x]\n\n", nRet);
                }
                break;
            }
            case CAP_PROP_LINE_SELECTOR:
            {
                nRet = MV_CC_SetEnumValue(handle, "LineSelector", value); //触发线
                if (MV_OK == nRet)
                {
                    printf("set LineSelector OK!\n");
                }
                else
                {
                    printf("Set LineSelector Failed! nRet = [%x]\n\n", nRet);
                }
                break;
            }
            default:
                return 0;
        }
        return nRet;
    }

    //^ ********************************** 重置相机配置 ************************************ //
    bool Camera::reset()
    {
        nRet = this->set(CAP_PROP_FRAMERATE_ENABLE, FrameRateEnable);
        nRet = this->set(CAP_PROP_FRAMERATE, FrameRate) || nRet;
        // nRet = this->set(CAP_PROP_BURSTFRAMECOUNT, BurstFrameCount) || nRet;
        nRet = this->set(CAP_PROP_HEIGHT, height) || nRet;
        nRet = this->set(CAP_PROP_WIDTH, width) || nRet;
        nRet = this->set(CAP_PROP_OFFSETX, Offset_x) || nRet;
        nRet = this->set(CAP_PROP_OFFSETY, Offset_y) || nRet;
        nRet = this->set(CAP_PROP_EXPOSURE_MODE, ExposureMode) || nRet;
        nRet = this->set(CAP_PROP_EXPOSURE_TIME, ExposureTime) || nRet;
        nRet = this->set(CAP_PROP_GAMMA_ENABLE, GammaEnable) || nRet;
        nRet = this->set(CAP_PROP_GAMMA, Gamma) || nRet;
        nRet = this->set(CAP_PROP_GAINAUTO, GainAuto) || nRet;
        nRet = this->set(CAP_PROP_GAIN, Gain) || nRet;
        nRet = this->set(CAP_PROP_SATURATION_ENABLE, SaturationEnable) || nRet;
        nRet = this->set(CAP_PROP_SATURATION, Saturation) || nRet;
        nRet = this->set(CAP_PROP_TRIGGER_MODE, TriggerMode) || nRet;
        nRet = this->set(CAP_PROP_TRIGGER_SOURCE, TriggerSource) || nRet;
        nRet = this->set(CAP_PROP_LINE_SELECTOR, LineSelector) || nRet;
        return nRet;
    }

    //^ ********************************** 输出设备信息 ************************************ //
    bool Camera::PrintDeviceInfo(MV_CC_DEVICE_INFO *pstMVDevInfo)
    {
        if (NULL == pstMVDevInfo)
        {
            printf("%s\n", "The Pointer of pstMVDevInfoList is NULL!");
            return false;
        }
        if (pstMVDevInfo->nTLayerType == MV_GIGE_DEVICE)
        {
            printf("%s %x\n", "nCurrentIp:", pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp);                 //当前IP
            printf("%s %s\n\n", "chUserDefinedName:", pstMVDevInfo->SpecialInfo.stGigEInfo.chUserDefinedName); //用户定义名
        }
        else if (pstMVDevInfo->nTLayerType == MV_USB_DEVICE)
        {
            printf("UserDefinedName:%s\n\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName);
        }
        else
        {
            printf("Not support.\n");
        }
        return true;
    }

    //^ ********************************** 显示图像属性 ************************************ //
    bool Camera::CamInfoShow()
    {
        // 数据类型详见海康工业相机常用节点数据类型
        MVCC_INTVALUE stParam;
        MVCC_FLOATVALUE fValue = {0};
        MVCC_ENUMVALUE stTriggerMode = {0};
        printf("\n------------------------------------------------\n");
        // 查看相机采集帧率
        MV_CC_GetFloatValue(handle, "ResultingFrameRate", &fValue);
        printf("图像采集帧率:%f FPS\n", fValue.fCurValue);
        // 查看曝光时间
        MV_CC_GetFloatValue(handle, "ExposureTime", &fValue) || nRet;
        printf("曝光时间:%f us\n", fValue.fCurValue);
        // 查看Gain增益值
        MV_CC_GetFloatValue(handle, "Gain", &fValue) || nRet;
        printf("Gain :%f\n", fValue.fCurValue);
        // 查看Gamma
        MV_CC_GetFloatValue(handle, "Gamma", &fValue) || nRet;
        printf("Gamma:%f\n", fValue.fCurValue);
        // 查看亮度值
        MV_CC_GetIntValue(handle, "Brightness", &stParam) || nRet;
        printf("亮度 :%d\n", stParam.nCurValue);
        // 查看白平衡值
        MV_CC_GetIntValue(handle, "BalanceRatio", &stParam) || nRet;
        printf("白平衡值:%d\n", stParam.nCurValue);
        // 查看色度
        MV_CC_GetIntValue(handle, "Hue", &stParam) || nRet;
        printf("色度 :%d\n", stParam.nCurValue);
        // 查看传输速率
        MV_CC_GetIntValue(handle, "DeviceConnectionSpeed", &stParam) || nRet;
        printf("传输速率 :%d Mbps\n", stParam.nCurValue);
        // 查看连接选择
        MV_CC_GetIntValue(handle, "DeviceLinkSelector", &stParam) || nRet;
        printf("连接选择 :%d Mbps\n", stParam.nCurValue);
        // 查看链路速度
        MV_CC_GetIntValue(handle, "DeviceLinkSpeed", &stParam) || nRet;
        printf("链路速度 :%d Mbps\n", stParam.nCurValue);
        // 查看像素格式
        MV_CC_GetEnumValue(handle, "PixelFormat", &stTriggerMode) || nRet;
        printf("像素格式:%d\n", stTriggerMode.nCurValue);
        // 查看像素尺寸
        MV_CC_GetEnumValue(handle, "PixelSize", &stTriggerMode) || nRet;
        printf("像素尺寸:%d Bit\n", stTriggerMode.nCurValue);

        printf("\n------------------------------------------------\n");
        return nRet;
    }

    //^ ********************************** 相机取图 ************************************ //
    void Camera::ReadImg(cv::Mat &image)
    {

        pthread_mutex_lock(&mutex);  // 线程加锁
        if (frame_empty)
        {
            image = cv::Mat();
        }
        else
        {
            image = camera::frame.clone();
            frame_empty = 1;
        }
        pthread_mutex_unlock(&mutex);  // 释放线程锁
    }

    //^ ********************************** 相机工作线程 ************************************ //
    void *Camera::HKWorkThread(void *p_handle)
    {
        double start;
        int nRet;
        unsigned char *m_pBufForDriver = (unsigned char *)malloc(sizeof(unsigned char) * g_nPayloadSize);
        unsigned char *m_pBufForSaveImage = (unsigned char *)malloc(g_nPayloadSize);
        MV_FRAME_OUT_INFO_EX stImageInfo = {0};
        MV_CC_PIXEL_CONVERT_PARAM stConvertParam = {0};
        cv::Mat tmp;
        int image_empty_count = 0; //空图帧数
        while (true)
        {
            start = static_cast<double>(cv::getTickCount()); // 开始计时
            nRet = MV_CC_GetOneFrameTimeout(p_handle, m_pBufForDriver, g_nPayloadSize, &stImageInfo, 15);
            if (nRet != MV_OK)
            {
                if (++image_empty_count > 100)
                {
                    printf("The Number of Faild Reading Exceed The Set Value!\n");
                    exit(-1);
                }
                continue;
            }
            image_empty_count = 0; //空图帧数
            //转换图像格式为BGR8

            stConvertParam.nWidth = stImageInfo.nWidth;                 //ch:图像宽 | en:image width
            stConvertParam.nHeight = stImageInfo.nHeight;               //ch:图像高 | en:image height
            stConvertParam.pSrcData = m_pBufForDriver;                  //ch:输入数据缓存 | en:input data buffer
            stConvertParam.nSrcDataLen = g_nPayloadSize;                //ch:输入数据大小 | en:input data size
            stConvertParam.enDstPixelType = PixelType_Gvsp_BGR8_Packed; //ch:输出像素格式 | en:output pixel format     //! 输出格式 RGB
            stConvertParam.pDstBuffer = m_pBufForSaveImage;             //ch:输出数据缓存 | en:output data buffer
            stConvertParam.nDstBufferSize = g_nPayloadSize;             //ch:输出缓存大小 | en:output buffer size
            stConvertParam.enSrcPixelType = stImageInfo.enPixelType;    //ch:输入像素格式 | en:input pixel format      //! 输入格式 RGB
            MV_CC_ConvertPixelType(p_handle, &stConvertParam);
            pthread_mutex_lock(&mutex);
            camera::frame = cv::Mat(stImageInfo.nHeight, stImageInfo.nWidth, CV_8UC3, m_pBufForSaveImage).clone(); //tmp.clone();
            frame_empty = 0;
            pthread_mutex_unlock(&mutex); // 释放线程锁
            double time = ((double)cv::getTickCount() - start) / cv::getTickFrequency();

            //************************************* 取消注释可测试相机取图 ********************************//
//            std::cout << "HK_camera,Time:" << time << "\tFPS:" << 1 / time << std::endl;
//            if (frame.empty()) {
//                continue;
//            }
//            cv::imshow("HK vision",frame);
//            cv::waitKey(1);

        }
        free(m_pBufForDriver);
        free(m_pBufForSaveImage);
        return 0;
    }

} // namespace camera

