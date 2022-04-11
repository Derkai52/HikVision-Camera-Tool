#include "debug/camera_parms_debug.h"


//^ ********************************** 海康MV系列相机参数初始化 ************************************ //
// 相机参数滑动条参数初始化
// 因为无法修改滑动条步长。为了保证实际控制步长在小数点后4位。进行了 *1000 和 /1000的操作。
char TrackbarName[50];

// Warning: 需要根据相机实际情况获取最大值,暂因SDK原因无法获得
const double exposureTime_slider_max = 20000; // 限制曝光最大值为20000
int exposureTime_slider = 5000; // 曝光初始值
double exposureTime;

double gain_slider_max = 17; // 限制 gain 最大值为15
int gain_slider = 10;
double gain;

const double gammas_slider_max = 2 * 1000; // 限制正常使用范围限制(0~2)  gammas 最大值为4
int gammas_slider = 1 * 1000;
double gammas;

// 白平衡
const int balanceRatioRed_slider_max = 3000; // 限制正常使用范围限制(0~3000)  bug:需要加一个自动白平衡选项
int balanceRatioRed_slider = 1400;
int balanceRatioRed;

const int balanceRatioGreen_slider_max = 3000; // 限制正常使用范围限制(0~3000)  bug:需要加一个自动白平衡选项
int balanceRatioGreen_slider = 1000;
int balanceRatioGreen;

const int balanceRatioBlue_slider_max = 3000; // 限制正常使用范围限制(0~3000)  bug:需要加一个自动白平衡选项
int balanceRatioBlue_slider = 2000;
int balanceRatioBlue;


static void exposureTrackbar(int, void *p_handle) {
    int nRet = 0;
    exposureTime = exposureTime_slider;
    nRet = MV_CC_SetExposureTime(p_handle, exposureTime);
    if (MV_OK != nRet) {
        printf("Set ExposureTime fail! nRet [0x%x] 或检查曝光模式\n", nRet);
    }
}

static void gainTrackbar(int, void *p_handle) {
    int nRet = 0;
    gain = gain_slider;
    nRet = MV_CC_SetGain(p_handle, gain);
    if (MV_OK != nRet) {
        printf("Set Gain fail! nRet [0x%x] 或检查Gain模式\n", nRet);
    }
}

static void gammasTrackbar(int, void *p_handle) {
    int nRet = 0;
    gammas = (double) gammas_slider / 1000;
    nRet = MV_CC_SetGamma(p_handle, gammas);
    if (MV_OK != nRet) {
        printf("Set Gammas fail! nRet [0x%x] 或检查Gamma模式\n", nRet);
    }
}

static void balanceRatioRedTrackbar(int, void *p_handle) {
    int nRet = 0;
    balanceRatioRed = balanceRatioRed_slider;
    nRet = MV_CC_SetBalanceRatioRed(p_handle, balanceRatioRed);
    if (MV_OK != nRet) {
        printf("Set BalanceRatioRed fail! nRet [0x%x] 或检查白平衡模式\n", nRet);
    }
}

static void balanceRatioGreenTrackbar(int, void *p_handle) {
    int nRet = 0;
    balanceRatioGreen = balanceRatioGreen_slider;
    nRet = MV_CC_SetBalanceRatioGreen(p_handle, balanceRatioGreen);
    if (MV_OK != nRet) {
        printf("Set BalanceRatioGreen fail! nRet [0x%x] 或检查白平衡模式\n", nRet);
    }
}

static void balanceRatioBlueTrackbar(int, void *p_handle) {
    int nRet = 0;
    balanceRatioBlue = balanceRatioBlue_slider;
    nRet = MV_CC_SetBalanceRatioBlue(p_handle, balanceRatioBlue);
    if (MV_OK != nRet) {
        printf("Set balanceRatioBlue fail! nRet [0x%x] 或检查白平衡模式\n", nRet);
    }
}


void debugcam(void *p_handle, MV_CC_DEVICE_INFO *pDeviceInfo) {
    string window_name = "Debug-Tool"; // 输入窗口名即可附加在窗口上，若无同名窗口则新建该窗口
    namedWindow(window_name); // warning: 关闭一次窗口后。应当设置窗口不可被手动关闭
    resizeWindow(window_name, 500, 500);


    // BUG:暂时没有找到海康设备获取硬件参数值有效范围。所以针对不同设备预设置不同参数。详情请参照海康官网设备信息。
    // 新设备请在下面添加即可。下面仅为基本参数，可根据实际情况添加
    // Warning: 建议更改。此处是强行进行了转换后的比较。(原先是unsigned char* 和 const char*)
    if (!strcmp(reinterpret_cast<const char *>(pDeviceInfo->SpecialInfo.stUsb3VInfo.chModelName),"MV-CA016-10UC")) {
        gain_slider_max = 17; // 限制 gain 最大值为17  // bug:需要根据相机实际情况获取最大值
        gain_slider = 10;

    } else if (!strcmp(reinterpret_cast<const char *>(pDeviceInfo->SpecialInfo.stUsb3VInfo.chModelName),"MV-CA013-21UC")) {
        gain_slider_max = 15; // 限制 gain 最大值为15  // bug:需要根据相机实际情况获取最大值
        gain_slider = 7;
    }

    sprintf(TrackbarName, "ExposureTime (Max:%.4lf us)", exposureTime_slider_max);
    createTrackbar(TrackbarName, window_name, &exposureTime_slider, exposureTime_slider_max, exposureTrackbar, p_handle); // 曝光时间
    exposureTrackbar(exposureTime_slider, 0);

    sprintf(TrackbarName, "Gain(Max:%.4lf)", gain_slider_max);
    createTrackbar(TrackbarName, window_name, &gain_slider, gain_slider_max, gainTrackbar, p_handle); // gain增益值
    gainTrackbar(gain_slider, 0); // Warning：建议按实际情况控制步长

    sprintf(TrackbarName, "Gamma (Max:%.4lf dB)", gammas_slider_max / 1000);
    createTrackbar(TrackbarName, window_name, &gammas_slider, gammas_slider_max, gammasTrackbar, p_handle);
    gammasTrackbar(gammas_slider, 0); // Warning：步长控制在小数点后1位

    // 白平衡
    sprintf(TrackbarName, "BalanceRatioRed (Max:%d)", balanceRatioRed_slider_max);
    createTrackbar(TrackbarName, window_name, &balanceRatioRed_slider, balanceRatioRed_slider_max,
                   balanceRatioRedTrackbar, p_handle);
    balanceRatioRedTrackbar(balanceRatioRed_slider, 0);

    sprintf(TrackbarName, "BalanceRatioGreen (Max:%d)", balanceRatioGreen_slider_max);
    createTrackbar(TrackbarName, window_name, &balanceRatioGreen_slider, balanceRatioGreen_slider_max,
                   balanceRatioGreenTrackbar, p_handle);
    balanceRatioGreenTrackbar(balanceRatioGreen_slider, 0);

    sprintf(TrackbarName, "BalanceRatioBlue (Max:%d)", balanceRatioBlue_slider_max);
    createTrackbar(TrackbarName, window_name, &balanceRatioBlue_slider, balanceRatioBlue_slider_max,
                   balanceRatioBlueTrackbar, p_handle);
    balanceRatioBlueTrackbar(balanceRatioBlue_slider, 0);
}