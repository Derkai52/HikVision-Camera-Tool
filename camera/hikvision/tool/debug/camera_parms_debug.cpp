//#include "camera_parms_debug.h"
//#include "hikvision_camera.h"
//
//namespace camera
//{
//    //^ ********************************** 海康MV系列相机参数初始化 ************************************ //
//    // 相机参数滑动条参数初始化
//    // 因为无法修改滑动条步长。为了保证实际控制步长在小数点后4位。进行了 *1000 和 /1000的操作。
//    char TrackbarName[50];
//
//    // Warning: 建议使用宏定义精简代码，优化代码结构
//    const double exposureTime_slider_max = 20000; // 限制曝光最大值为20000
//    int exposureTime_slider = 5000; // 曝光初始值
//    double exposureTime;
//
//    double gain_slider_max = 17; // 限制 gain 最大值为15  // bug:需要根据相机实际情况获取最大值 // Warning:没有使用const。使用宏定义永久解决此隐患。(因为不同设备的最大值不同)
//    int gain_slider = 10;
//    double gain;
//
//    const double gammas_slider_max = 2 * 1000; // 限制正常使用范围限制(0~2)  gammas 最大值为4  // bug:需要根据相机实际情况获取最大值
//    int gammas_slider = 1 * 1000;
//    double gammas;
//
//    // 白平衡
//    const int balanceRatioRed_slider_max = 3000; // 限制正常使用范围限制(0~3000)  bug:需要加一个自动白平衡选项
//    int balanceRatioRed_slider = 1400;
//    int balanceRatioRed;
//
//    const int balanceRatioGreen_slider_max = 3000; // 限制正常使用范围限制(0~3000)  bug:需要加一个自动白平衡选项
//    int balanceRatioGreen_slider = 1000;
//    int balanceRatioGreen;
//
//    const int balanceRatioBlue_slider_max = 3000; // 限制正常使用范围限制(0~3000)  bug:需要加一个自动白平衡选项
//    int balanceRatioBlue_slider = 2000;
//    int balanceRatioBlue;
//
//
//    static void exposureTrackbar(int, void *) {
//        int nRet = 0;
//        exposureTime = exposureTime_slider;
//        MV_CC_SetExposureTime(HikCamera::handle, exposureTime);
//        if (MV_OK != nRet) {
//            printf("Set ExposureTime fail! nRet [0x%x]\n", nRet);
//        }
//        CamInfoShow(handle); // Warning: 应当是一个统一的接口调用而不是每个回调函数都写一遍。以下同等。
//    }
//
//    static void gainTrackbar(int, void *) {
//        int nRet = 0;
//        gain = gain_slider;
//        MV_CC_SetGain(handle, gain);
//        if (MV_OK != nRet) {
//            printf("Set Gain fail! nRet [0x%x]\n", nRet);
//        }
//        CamInfoShow(handle); // Warning
//    }
//
//    static void gammasTrackbar(int, void *) {
//        int nRet = 0;
//        gammas = (double) gammas_slider / 1000;
//        MV_CC_SetGamma(handle, gammas);
//        if (MV_OK != nRet) {
//            printf("Set Gammas fail! nRet [0x%x]\n", nRet);
//        }
//        CamInfoShow(handle); // Warning
//    }
//
//    static void balanceRatioRedTrackbar(int, void *) {
//        int nRet = 0;
//        balanceRatioRed = balanceRatioRed_slider;
//        MV_CC_SetBalanceRatioRed(handle, balanceRatioRed);
//        if (MV_OK != nRet) {
//            printf("Set BalanceRatioRed fail! nRet [0x%x]\n", nRet);
//        }
//        CamInfoShow(handle); // Warning
//    }
//
//    static void balanceRatioGreenTrackbar(int, void *) {
//        int nRet = 0;
//        balanceRatioGreen = balanceRatioGreen_slider;
//        MV_CC_SetBalanceRatioGreen(handle, balanceRatioGreen);
//        if (MV_OK != nRet) {
//            printf("Set BalanceRatioGreen fail! nRet [0x%x]\n", nRet);
//        }
//        CamInfoShow(handle); // Warning
//    }
//
//    static void balanceRatioBlueTrackbar(int, void *) {
//        int nRet = 0;
//        balanceRatioBlue = balanceRatioBlue_slider;
//        MV_CC_SetBalanceRatioBlue(handle, balanceRatioBlue);
//        if (MV_OK != nRet) {
//            printf("Set balanceRatioBlue fail! nRet [0x%x]\n", nRet);
//        }
//        CamInfoShow(handle); // Warning
//    }
//
//};