
#ifndef _MV_CAMERA_CTRL_H_
#define _MV_CAMERA_CTRL_H_

#include "MvErrorDefine.h"
#include "CameraParams.h"

/**
*  @brief  动态库导入导出定义
*  @brief  Import and export definition of the dynamic library 
*/
#ifndef MV_CAMCTRL_API

    #if (defined (_WIN32) || defined(WIN64))
        #if defined(MV_CAMCTRL_EXPORTS)
            #define MV_CAMCTRL_API __declspec(dllexport)
        #else
            #define MV_CAMCTRL_API __declspec(dllimport)
        #endif
    #else
        #ifndef __stdcall
            #define __stdcall
        #endif

        #if defined(MV_CAMCTRL_EXPORTS)
            #define  MV_CAMCTRL_API __attribute__((visibility("default")))
        #else
            #define  MV_CAMCTRL_API
        #endif
    #endif

#endif

#ifndef IN
    #define IN
#endif

#ifndef OUT
    #define OUT
#endif

#ifdef __cplusplus
extern "C" {
#endif 

/************************************************************************/
/* 相机的基本指令和操作                                         		*/
/* HikCamera basic instructions and operations                             */
/************************************************************************/
/************************************************************************
 *  @fn     MV_CC_GetSDKVersion()
 *  @brief  获取SDK版本号
 *  @param  
 *  @return 始终返回4字节版本号 |主    |次    |修正  |  测试|
                                 8bits  8bits  8bits  8bits 
								 
 *  @fn     MV_CC_GetSDKVersion()
 *  @brief  Get SDK Version
 *  @param  
 *  @return Always return 4 Bytes of version number |Main    |Sub    |Rev  |  Test|
                                                     8bits  8bits  8bits  8bits 
 ************************************************************************/
MV_CAMCTRL_API unsigned int __stdcall MV_CC_GetSDKVersion();

/************************************************************************
 *  @fn     MV_CC_EnumerateTls()
 *  @brief  获取支持的传输层
 *  @return 支持的传输层编号 
 
 *  @fn     MV_CC_EnumerateTls()
 *  @brief  Get supported Transport Layer
 *  @return Supported Transport Layer number
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_EnumerateTls();

/************************************************************************
 *  @fn     MV_CC_EnumDevices()
 *  @brief  枚举设备
 *  @param  nTLayerType            [IN]           枚举传输层
 *  @param  pstDevList             [OUT]          设备列表
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_CC_EnumDevices()
 *  @brief  Enumerate Device
 *  @param  nTLayerType            [IN]           Enumerate TLs
 *  @param  pstDevList             [OUT]          Device List
 *  @return Success, return MV_OK. Failure, return error code 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_EnumDevices(IN unsigned int nTLayerType, IN OUT MV_CC_DEVICE_INFO_LIST* pstDevList);

/************************************************************************
 *  @fn     MV_CC_EnumDevicesEx()
 *  @brief  根据厂商名字枚举设备
 *  @param  nTLayerType            [IN]           枚举传输层
 *  @param  pstDevList             [OUT]          设备列表
 *  @param  pManufacturerName      [IN]           厂商名字
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_CC_EnumDevicesEx()
 *  @brief  Enumerate device according to manufacture name
 *  @param  nTLayerType            [IN]           Transmission layer of enumeration
 *  @param  pstDevList             [OUT]          Device list
 *  @param  pManufacturerName      [IN]           Manufacture Name
 *  @return Success, return MV_OK. Failure, return error code 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_EnumDevicesEx(IN unsigned int nTLayerType, IN OUT MV_CC_DEVICE_INFO_LIST* pstDevList, IN const char* pManufacturerName);

/************************************************************************
 *  @fn     MV_CC_IsDeviceAccessible()
 *  @brief  设备是否可达
 *  @param  pstDevInfo             [IN]           设备信息结构体
 *  @param  nAccessMode            [IN]           访问权限
 *  @return 可达，返回true；不可达，返回false 
 
 *  @fn     MV_CC_IsDeviceAccessible()
 *  @brief  Is the device accessible
 *  @param  pstDevInfo             [IN]           Device Information Structure
 *  @param  nAccessMode            [IN]           Access Right
 *  @return Access, return true. Not access, return false
 ************************************************************************/
MV_CAMCTRL_API bool __stdcall MV_CC_IsDeviceAccessible(IN MV_CC_DEVICE_INFO* pstDevInfo, IN unsigned int nAccessMode);

/************************************************************************
 *  @fn     MV_CC_SetSDKLogPath()
 *  @brief  设置SDK日志路径（如果日志服务MvLogServer已启用，则该接口无效）
 *  @param  pSDKLogPath             [IN]           SDK日志路径
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_CC_SetSDKLogPath()
 *  @brief  Set SDK log path
 *  @param  pSDKLogPath             [IN]           SDK log path
 *  @return Access, return true. Not access, return false
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetSDKLogPath(IN const char * pSDKLogPath);

/************************************************************************
 *  @fn     MV_CC_CreateHandle()
 *  @brief  创建设备句柄
 *  @param  handle                 [OUT]          句柄地址
 *  @param  pstDevInfo             [IN]           设备信息结构体
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_CC_CreateHandle()
 *  @brief  Create Device Handle
 *  @param  handle                 [OUT]          Handle Address
 *  @param  pstDevInfo             [IN]           Device Information Structure
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_CreateHandle(OUT void ** handle, IN const MV_CC_DEVICE_INFO* pstDevInfo);

/************************************************************************
 *  @fn     MV_CC_CreateHandleWithoutLog
 *  @brief  创建设备句柄，不生成日志
 *  @param  handle                 [OUT]          句柄地址
 *  @param  pstDevInfo             [IN]           设备信息结构体
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_CC_CreateHandleWithoutLog
 *  @brief  Create Device Handle without log
 *  @param  handle                 [OUT]          Handle Address
 *  @param  pstDevInfo             [IN]           Device Information Structure
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_CreateHandleWithoutLog(OUT void ** handle, IN const MV_CC_DEVICE_INFO* pstDevInfo);

/************************************************************************
 *  @fn     MV_CC_DestroyHandle()
 *  @brief  销毁设备句柄
 *  @param  handle                 [IN]          句柄
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_CC_DestroyHandle()
 *  @brief  Destroy Device Handle
 *  @param  handle                 [IN]          Handle
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_DestroyHandle(IN void * handle);

/************************************************************************
 *  @fn     MV_CC_OpenDevice()
 *  @brief  打开设备
 *  @param  handle                 [IN]          句柄
 *  @param  nAccessMode            [IN]          访问权限
 *  @param  nSwitchoverKey         [IN]          切换访问权限时的密钥
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_CC_OpenDevice()
 *  @brief  Open Device
 *  @param  handle                 [IN]          Handle
 *  @param  nAccessMode            [IN]          Access Right
 *  @param  nSwitchoverKey         [IN]          Switch key of access right
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
#ifndef __cplusplus
MV_CAMCTRL_API int __stdcall MV_CC_OpenDevice(IN void* handle, IN unsigned int nAccessMode, IN unsigned short nSwitchoverKey);
#else
MV_CAMCTRL_API int __stdcall MV_CC_OpenDevice(IN void* handle, IN unsigned int nAccessMode = MV_ACCESS_Exclusive, IN unsigned short nSwitchoverKey = 0);
#endif

/***********************************************************************
 *  @fn         MV_CC_CloseDevice
 *  @brief      关闭相机
 *  @param       handle                 [IN]          句柄
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_CC_CloseDevice
 *  @brief      Close Device
 *  @param      handle                 [IN]          Handle
 *  @return     Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_CloseDevice(IN void* handle);

/***********************************************************************
 *  @fn         MV_CC_IsDeviceConnected
 *  @brief      判断相机是否处于连接状态
 *  @param      handle                 [IN]          句柄
 *  @return     设备处于连接状态，返回true；没连接或失去连接，返回false
 
 *  @fn         MV_CC_IsDeviceConnected
 *  @brief      Is The Device Connected
 *  @param      handle                 [IN]          Handle
 *  @return     Connected, return true. Not Connected or DIsconnected, return false
 ***********************************************************************/
MV_CAMCTRL_API bool __stdcall MV_CC_IsDeviceConnected(IN void* handle);

/***********************************************************************
 *  @fn         MV_CC_RegisterImageCallBackEx
 *  @brief      注册图像数据回调，chunk
 *  @param       handle                 [IN]          句柄
 *  @param       cbOutput               [IN]          回调函数指针
 *  @param       pUser                  [IN]          用户自定义变量
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_CC_RegisterImageCallBackEx
 *  @brief      register image data callback, chunk
 *  @param       handle                 [IN]          Handle
 *  @param       cbOutput               [IN]          Callback function pointer
 *  @param       pUser                  [IN]          User defined variable
 *  @return      Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_RegisterImageCallBackEx(void* handle, 
                                                         void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser),
                                                         void* pUser);

/***********************************************************************
 *  @fn         MV_CC_RegisterImageCallbackForRGB
 *  @brief      注册图像数据回调，RGB
 *  @param       handle                 [IN]          句柄
 *  @param       cbOutput               [IN]          回调函数指针
 *  @param       pUser                  [IN]          用户自定义变量
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_CC_RegisterImageCallbackForRGB
 *  @brief      register image data callback, RGB
 *  @param       handle                 [IN]          Handle
 *  @param       cbOutput               [IN]          Callback function pointer
 *  @param       pUser                  [IN]          User defined variable
 *  @return      Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_RegisterImageCallBackForRGB(void* handle, 
                                                         void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser),
                                                         void* pUser);

/***********************************************************************
 *  @fn         MV_CC_RegisterImageCallbackForBGR
 *  @brief      注册图像数据回调，BGR
 *  @param       handle                 [IN]          句柄
 *  @param       cbOutput               [IN]          回调函数指针
 *  @param       pUser                  [IN]          用户自定义变量
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_CC_RegisterImageCallbackForBGR
 *  @brief      register image data callback, BGR
 *  @param       handle                 [IN]          Handle
 *  @param       cbOutput               [IN]          Callback function pointer
 *  @param       pUser                  [IN]          User defined variable
 *  @return      Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_RegisterImageCallBackForBGR(void* handle, 
                                                         void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser),
                                                         void* pUser);

/***********************************************************************
 *  @fn         MV_CC_StartGrabbing
 *  @brief      开始取流
 *  @param       handle                 [IN]          句柄
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_CC_StartGrabbing
 *  @brief      Start Grabbing
 *  @param      handle                 [IN]          Handle
 *  @return     Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_StartGrabbing(IN void* handle);

/***********************************************************************
 *  @fn         MV_CC_StopGrabbing
 *  @brief      停止取流
 *  @param       handle                 [IN]          句柄
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_CC_StopGrabbing
 *  @brief      Stop Grabbing
 *  @param      handle                 [IN]          Handle
 *  @return     Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_StopGrabbing(IN void* handle);

/***********************************************************************
 *  @fn         MV_CC_GetImageForRGB
 *  @brief      获取一帧RGB数据，此函数为查询式获取，每次调用查询内部
                缓存有无数据，有数据则范围数据，无数据返回错误码
 *  @param       handle                 [IN]          句柄
 *  @param       pData                  [OUT]         图像数据接收指针
 *  @param       nDataSize              [IN]          接收缓存大小
 *  @param       pFrameInfo             [OUT]         图像信息结构体
 *  @param       nMsec                  [IN]          等待超时时间
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_CC_GetImageForRGB
 *  @brief      Get one frame of RGB data, this function is using query to get data, 
                query whether the internal cache has data, return data if there has, return error code if no data
 *  @param       handle                 [IN]          Handle
 *  @param       pData                  [OUT]         Recevied image data pointer
 *  @param       nDataSize              [IN]          Recevied buffer size
 *  @param       pFrameInfo             [OUT]         Image information structure
 *  @param       nMsec                  [IN]          Waiting timeout
 *  @return      Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetImageForRGB(IN void* handle, IN OUT unsigned char * pData , IN unsigned int nDataSize, IN OUT MV_FRAME_OUT_INFO_EX* pFrameInfo, int nMsec);

/***********************************************************************
 *  @fn         MV_CC_GetImageForBGR
 *  @brief      获取一帧BGR数据，此函数为查询式获取，每次调用查询内部
                缓存有无数据，有数据则范围数据，无数据返回错误码
 *  @param       handle                 [IN]          句柄
 *  @param       pData                  [OUT]         图像数据接收指针
 *  @param       nDataSize              [IN]          接收缓存大小
 *  @param       pFrameInfo             [OUT]         图像信息结构体
 *  @param       nMsec                  [IN]          等待超时时间
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_CC_GetImageForBGR
 *  @brief      Get one frame of BGR data, this function is using query to get data, 
                query whether the internal cache has data, return data if there has, return error code if no data
 *  @param       handle                 [IN]          Handle
 *  @param       pData                  [OUT]         Recevied image data pointer
 *  @param       nDataSize              [IN]          Recevied buffer size
 *  @param       pFrameInfo             [OUT]         Image information structure
 *  @param       nMsec                  [IN]          Waiting timeout
 *  @return      Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetImageForBGR(IN void* handle, IN OUT unsigned char * pData , IN unsigned int nDataSize, IN OUT MV_FRAME_OUT_INFO_EX* pFrameInfo, int nMsec);

/***********************************************************************
*  @fn         MV_CC_GetImageBuffer
*  @brief      采用超时机制获取一帧图片，SDK内部等待直到有数据时返回，
此接口可以增加取流平稳性，适合用于对平稳性要求较高的场合（与MV_CC_Display不能同时使用）
*  @param       handle                 [IN]          句柄
*  @param       pFrame                 [OUT]         图像数据首地址和图像信息
*  @param       nMsec                  [IN]          等待超时时间，输入INFINITE时表示无限等待，直到收到一帧数据或者停止取流
*  @return 成功，返回MV_OK；错误，返回错误码

*  @fn         MV_CC_GetImageBuffer
*  @brief      Timeout mechanism is used to get image, and the SDK waits inside until the data is returned,
this interface can increase the flow stability, and is suitable for occasions with higher stability requirements
*  @param       handle                 [IN]          Handle
*  @param       pFrame                 [OUT]         Pointer of recevied image data and info
*  @param       nMsec                  [IN]          Waiting timeout
*  @return      Success, return MV_OK. Failure, return error code
***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetImageBuffer(IN void* handle, OUT MV_FRAME_OUT* pFrame, IN unsigned int nMsec);

/***********************************************************************
*  @fn         MV_CC_FreeImageBuffer
*  @brief      释放图像缓存(此接口用于释放不再使用的图像缓存，与MV_CC_GetImageBuffer配套使用)
*  @param       handle                 [IN]          句柄
*  @param       pFrame                 [IN]          图像数据和信息接收指针
*  @return 成功，返回MV_OK；错误，返回错误码

*  @fn         MV_CC_FreeImageBuffer
*  @brief      Free image buffer(this interface can free image buffer, used with MV_CC_GetImageBuffer)
*  @param       handle                 [IN]          Handle
*  @param       pFrame                 [IN]          Pointer of recevied image data and info
*  @return      Success, return MV_OK. Failure, return error code
***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_FreeImageBuffer(IN void* handle, IN MV_FRAME_OUT* pFrame);

/***********************************************************************
 *  @fn         MV_CC_GetOneFrameTimeout
 *  @brief      采用超时机制获取一帧图片，SDK内部等待直到有数据时返回，
                此接口可以增加取流平稳性，适合用于对平稳性要求较高的场合
 *  @param       handle                 [IN]          句柄
 *  @param       pData                  [OUT]         图像数据接收指针
 *  @param       nDataSize              [IN]          接收缓存大小
 *  @param       pFrameInfo             [OUT]         图像信息结构体
 *  @param       nMsec                  [IN]          等待超时时间
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_CC_GetOneFrameTimeout
 *  @brief      Timeout mechanism is used to get image, and the SDK waits inside until the data is returned,
                this interface can increase the flow stability, and is suitable for occasions with higher stability requirements
 *  @param       handle                 [IN]          Handle
 *  @param       pData                  [OUT]         Recevied image data pointer
 *  @param       nDataSize              [IN]          Recevied buffer size
 *  @param       pFrameInfo             [OUT]         Image information structure
 *  @param       nMsec                  [IN]          Waiting timeout
 *  @return      Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetOneFrameTimeout(IN void* handle, IN OUT unsigned char * pData , IN unsigned int nDataSize, IN OUT MV_FRAME_OUT_INFO_EX* pFrameInfo, unsigned int nMsec);

/***********************************************************************
 *  @fn         MV_CC_Display
 *  @brief      显示图像，注册显示窗口，内部自动显示（与MV_CC_GetImageBuffer不能同时使用）
 *  @param       handle                 [IN]          句柄
 *  @param       hWnd                   [IN]          显示窗口句柄
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_CC_Display
 *  @brief      Display one frame image, register display window, automatic display internally
 *  @param      handle                 [IN]          Handle
 *  @param      hWnd                   [IN]          Display Window Handle
 *  @return     Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_Display(IN void* handle, void* hWnd);

/***********************************************************************
 *  @fn         MV_CC_DisplayOneFrame
 *  @brief      显示一帧图像
 *  @param       handle                 [IN]          句柄
 *  @param       pDisplayInfo           [IN]          图像信息
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_CC_DisplayOneFrame
 *  @brief      Display one frame image
 *  @param      handle                 [IN]          Handle
 *  @param      pDisplayInfo           [IN]          Frame Info
 *  @return     Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_DisplayOneFrame(IN void* handle, IN MV_DISPLAY_FRAME_INFO* pDisplayInfo);

/***********************************************************************
 *  @fn         MV_CC_SetImageNodeNum
 *  @brief      设置SDK内部图像缓存节点个数，范围[1, 30]，在抓图前调用
 *  @param       handle                 [IN]          句柄
 *  @param       nNum                   [IN]          缓存节点个数
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_CC_SetImageNodeNum
 *  @brief      Set the number of the internal image cache nodes in SDK, in the range [1, 30], to be called before the capture
 *  @param      handle                 [IN]          Handle
 *  @param      nNum                   [IN]          Image Node Number
 *  @return     Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetImageNodeNum(IN void* handle, unsigned int nNum);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetImageInfo(IN void* handle, IN OUT MV_IMAGE_BASIC_INFO* pstInfo);
 *  @brief  获取图像基本信息
 *  @param  void* handle                     [IN]        相机句柄
 *  @param  MV_IMAGE_BASIC_INFO* pstInfo     [IN][OUT]   返回给调用者有关相机图像基本信息结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 *  
 *          参考 CameraParam.h 中的 MV_IMAGE_BASIC_INFO 定义
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetImageInfo(IN void* handle, IN OUT MV_IMAGE_BASIC_INFO* pstInfo);
 *  @brief  Get basic information of image
 *  @param  void* handle                     [IN]        Handle
 *  @param  MV_IMAGE_BASIC_INFO* pstInfo     [IN][OUT]   Structure pointer of image basic information
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to the definition of MV_IMAGE_BASIC_INFO in CameraParam.h
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetImageInfo(IN void* handle, IN OUT MV_IMAGE_BASIC_INFO* pstInfo);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetDeviceInfo(IN void* handle, IN OUT MV_CC_DEVICE_INFO* pstDevInfo);
 *  @brief  获取设备信息
 *  @param  void* handle                     [IN]        相机句柄
 *  @param  MV_CC_DEVICE_INFO* pstDevInfo    [IN][OUT]   返回给调用者有关相机设备信息结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 *  
 *          参考 CameraParam.h 中的 MV_CC_DEVICE_INFO 定义
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetDeviceInfo(IN void* handle, IN OUT MV_CC_DEVICE_INFO* pstDevInfo);
 *  @brief  Get device information
 *  @param  void* handle                     [IN]        Handle
 *  @param  MV_CC_DEVICE_INFO* pstDevInfo    [IN][OUT]   Structure pointer of device information
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to the definition of MV_CC_DEVICE_INFO in CameraParam.h
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetDeviceInfo(IN void * handle, IN OUT MV_CC_DEVICE_INFO* pstDevInfo);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetAllMatchInfo(IN void* handle, IN OUT MV_ALL_MATCH_INFO* pstInfo);
 *  @brief  获取各种类型的信息
 *  @param  void* handle                     [IN]        相机句柄
 *  @param  MV_ALL_MATCH_INFO* pstInfo       [IN][OUT]   返回给调用者有关相机各种类型的信息结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 *  
 *          参考 CameraParam.h 中的 MV_ALL_MATCH_INFO 定义
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetAllMatchInfo(IN void* handle, IN OUT MV_ALL_MATCH_INFO* pstInfo);
 *  @brief  Get various type of information
 *  @param  void* handle                     [IN]        Handle
 *  @param  MV_ALL_MATCH_INFO* pstInfo       [IN][OUT]   Structure pointer of various type of information
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to the definition of MV_ALL_MATCH_INFO in CameraParam.h
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetAllMatchInfo(IN void* handle, IN OUT MV_ALL_MATCH_INFO* pstInfo);


/************************************************************************/
/* 设置和获取相机参数的万能接口                                 		*/
/* General interface for getting and setting camera parameters          */
/************************************************************************/
/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetIntValue(IN void* handle,
                                                           IN const char* strKey,
                                                           OUT MVCC_INTVALUE *pIntValue);
 *  @brief  获取Integer属性值
 *  @param  void* handle                [IN]        相机句柄
 *  @param  char* strKey                [IN]        属性键值，如获取宽度信息则为"Width"
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机属性结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetIntValue(IN void* handle,
                                                           IN const char* strKey,
                                                           OUT MVCC_INTVALUE *pIntValue);
 *  @brief  Get Integer value
 *  @param  void* handle                [IN]        Handle
 *  @param  char* strKey                [IN]        Key value, for example, using "Width" to get width
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of camera features
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetIntValue(IN void* handle,IN const char* strKey,OUT MVCC_INTVALUE *pIntValue);

/************************************************************************/
/* 设置和获取相机参数的万能接口                                 		*/
/* General interface for getting and setting camera parameters          */
/************************************************************************/
/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetIntValueEx(IN void* handle,
                                                           IN const char* strKey,
                                                           OUT MVCC_INTVALUE *pIntValue);
 *  @brief  获取Integer属性值
 *  @param  void* handle                [IN]        相机句柄
 *  @param  char* strKey                [IN]        属性键值，如获取宽度信息则为"Width"
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机属性结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetIntValueEx(IN void* handle,
                                                           IN const char* strKey,
                                                           OUT MVCC_INTVALUE *pIntValue);
 *  @brief  Get Integer value
 *  @param  void* handle                [IN]        Handle
 *  @param  char* strKey                [IN]        Key value, for example, using "Width" to get width
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of camera features
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetIntValueEx(IN void* handle,IN const char* strKey,OUT MVCC_INTVALUE_EX *pIntValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetIntValue(IN void* handle,
                                                           IN const char* strKey,
                                                           IN unsigned int nValue);
 *  @brief  设置Integer型属性值
 *  @param  void* handle                [IN]        相机句柄
 *  @param  char* strKey                [IN]        属性键值，如获取宽度信息则为"Width"
 *          const unsigned int nValue   [IN]        想要设置的相机的属性值
 *  @return 成功,返回MV_OK,失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetIntValue(IN void* handle,
                                                           IN const char* strKey,
                                                           IN unsigned int nValue);
 *  @brief  Set Integer value
 *  @param  void* handle                [IN]        Handle
 *  @param  char* strKey                [IN]        Key value, for example, using "Width" to set width
 *          const unsigned int nValue   [IN]        Feature value to set
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetIntValue(IN void* handle,IN const char* strKey,IN unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetIntValueEx(IN void* handle,
                                                           IN const char* strKey,
                                                           IN int64_t nValue);
 *  @brief  设置Integer型属性值
 *  @param  void* handle                [IN]        相机句柄
 *  @param  char* strKey                [IN]        属性键值，如获取宽度信息则为"Width"
 *          const int64_t nValue   [IN]        想要设置的相机的属性值
 *  @return 成功,返回MV_OK,失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetIntValueEx(IN void* handle,
                                                           IN const char* strKey,
                                                           IN int64_t nValue);
 *  @brief  Set Integer value
 *  @param  void* handle                [IN]        Handle
 *  @param  char* strKey                [IN]        Key value, for example, using "Width" to set width
 *          const int64_t nValue   [IN]        Feature value to set
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetIntValueEx(IN void* handle,IN const char* strKey,IN int64_t nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetEnumValue(IN void* handle,
                                                            IN const char* strKey,
                                                            OUT MVCC_ENUMVALUE *pEnumValue);
 *  @brief  获取Enum属性值
 *  @param  void* handle                   [IN]        相机句柄
 *  @param  char* strKey                   [IN]        属性键值，如获取像素格式信息则为"PixelFormat"
 *  @param  MVCC_ENUMVALUE* pEnumValue     [IN][OUT]   返回给调用者有关相机属性结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetEnumValue(IN void* handle,
                                                            IN const char* strKey,
                                                            OUT MVCC_ENUMVALUE *pEnumValue);
 *  @brief  Get Enum value
 *  @param  void* handle                   [IN]        Handle
 *  @param  char* strKey                   [IN]        Key value, for example, using "PixelFormat" to get pixel format
 *  @param  MVCC_ENUMVALUE* pEnumValue     [IN][OUT]   Structure pointer of camera features
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetEnumValue(IN void* handle,IN const char* strKey,OUT MVCC_ENUMVALUE *pEnumValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetEnumValue(IN void* handle,
                                                            IN const char* strKey,
                                                            IN unsigned int nValue);
 *  @brief  设置Enum型属性值
 *  @param  void* handle                [IN]        相机句柄
 *  @param  char* strKey                [IN]        属性键值，如获取像素格式信息则为"PixelFormat"
 *          const unsigned int nValue   [IN]        想要设置的相机的属性值
 *  @return 成功,返回MV_OK,失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetEnumValue(IN void* handle,
                                                            IN const char* strKey,
                                                            IN unsigned int nValue);
 *  @brief  Set Enum value
 *  @param  void* handle                [IN]        Handle
 *  @param  char* strKey                [IN]        Key value, for example, using "PixelFormat" to set pixel format
 *          const unsigned int nValue   [IN]        Feature value to set
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetEnumValue(IN void* handle,IN const char* strKey,IN unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetEnumValueByString(IN void* handle,
                                                            IN const char* strKey,
                                                            IN const char* sValue);
 *  @brief  设置Enum型属性值
 *  @param  void* handle                [IN]        相机句柄
 *  @param  char* strKey                [IN]        属性键值，如获取像素格式信息则为"PixelFormat"
 *          char* sValue                [IN]        想要设置的相机的属性字符串
 *  @return 成功,返回MV_OK,失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetEnumValue(IN void* handle,
                                                            IN const char* strKey,
                                                            IN const char* sValue);
 *  @brief  Set Enum value
 *  @param  void* handle                [IN]        Handle
 *  @param  char* strKey                [IN]        Key value, for example, using "PixelFormat" to set pixel format
 *          char* sValue                [IN]        Feature String to set
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetEnumValueByString(IN void* handle,IN const char* strKey,IN const char* sValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetFloatValue(IN void* handle,
                                                             IN const char* strKey,
                                                             OUT MVCC_FLOATVALUE *pFloatValue);
 *  @brief  获取Float属性值
 *  @param  void* handle                     [IN]        相机句柄
 *  @param  char* strKey                     [IN]        属性键值
 *  @param  MVCC_FLOATVALUE *pFloatValue     [IN][OUT]   返回给调用者有关相机属性结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetFloatValue(IN void* handle,
                                                             IN const char* strKey,
                                                             OUT MVCC_FLOATVALUE *pFloatValue);
 *  @brief  Get Float value
 *  @param  void* handle                     [IN]        Handle
 *  @param  char* strKey                     [IN]        Key value
 *  @param  MVCC_FLOATVALUE *pFloatValue     [IN][OUT]   Structure pointer of camera features
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetFloatValue(IN void* handle,IN const char* strKey,OUT MVCC_FLOATVALUE *pFloatValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetFloatValue(IN void* handle,
                                                             IN const char* strKey,
                                                             IN float fValue);
 *  @brief  设置float型属性值
 *  @param  void* handle                [IN]        相机句柄
 *  @param  char* strKey                [IN]        属性键值
 *          float fValue                [IN]        想要设置的相机的属性值
 *  @return 成功,返回MV_OK,失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetFloatValue(IN void* handle,
                                                             IN const char* strKey,
                                                             IN float fValue);
 *  @brief  Set float value
 *  @param  void* handle                [IN]        Handle
 *  @param  char* strKey                [IN]        Key value
 *          float fValue                [IN]        Feature value to set
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetFloatValue(IN void* handle,IN const char* strKey,IN float fValue);
	
/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetBoolValue(IN void* handle,
                                                            IN const char* strKey,
                                                            OUT bool *pBoolValue);
 *  @brief  获取Boolean属性值
 *  @param  void* handle                     [IN]        相机句柄
 *  @param  char* strKey                     [IN]        属性键值
 *  @param  bool *pBoolValue                 [IN][OUT]   返回给调用者有关相机属性值
 *  @return 成功,返回MV_OK,失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetBoolValue(IN void* handle,
                                                            IN const char* strKey,
                                                            OUT bool *pBoolValue);
 *  @brief  Get Boolean value
 *  @param  void* handle                     [IN]        Handle
 *  @param  char* strKey                     [IN]        Key value
 *  @param  bool *pBoolValue                 [IN][OUT]   Structure pointer of camera features
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetBoolValue(IN void* handle,IN const char* strKey,OUT bool *pBoolValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetBoolValue(IN void* handle,
                                                            IN const char* strKey,
                                                            IN bool bValue);
 *  @brief  设置Boolean型属性值
 *  @param  void* handle                [IN]        相机句柄
 *  @param  char* strKey                [IN]        属性键值
 *          bool bValue                 [IN]        想要设置的相机的属性值
 *  @return 成功,返回MV_OK,失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetBoolValue(IN void* handle,
                                                            IN const char* strKey,
                                                            IN bool bValue);
 *  @brief  Set Boolean value
 *  @param  void* handle                [IN]        Handle
 *  @param  char* strKey                [IN]        Key value
 *          bool bValue                 [IN]        Feature value to set
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetBoolValue(IN void* handle,IN const char* strKey,IN bool bValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetStringValue(IN void* handle,
                                                              IN const char* strKey,
                                                              OUT MVCC_STRINGVALUE *pStringValue);
 *  @brief  获取String属性值
 *  @param  void* handle                       [IN]        相机句柄
 *  @param  char* strKey                       [IN]        属性键值
 *  @param  MVCC_STRINGVALUE *pStringValue     [IN][OUT]   返回给调用者有关相机属性结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetStringValue(IN void* handle,
                                                              IN const char* strKey,
                                                              OUT MVCC_STRINGVALUE *pStringValue);
 *  @brief  Get String value
 *  @param  void* handle                       [IN]        Handle
 *  @param  char* strKey                       [IN]        Key value
 *  @param  MVCC_STRINGVALUE *pStringValue     [IN][OUT]   Structure pointer of camera features
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetStringValue(IN void* handle,IN const char* strKey,OUT MVCC_STRINGVALUE *pStringValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetStringValue(IN void* handle,
                                                              IN const char* strKey,
                                                              IN const char * sValue);
 *  @brief  设置String型属性值
 *  @param  void* handle                  [IN]        相机句柄
 *  @param  char* strKey                  [IN]        属性键值
 *          char * sValue                 [IN]        想要设置的相机的属性值
 *  @return 成功,返回MV_OK,失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetStringValue(IN void* handle,
                                                              IN const char* strKey,
                                                              IN const char * sValue);
 *  @brief  Set String value
 *  @param  void* handle                  [IN]        Handle
 *  @param  char* strKey                  [IN]        Key value
 *          char * sValue                 [IN]        Feature value to set
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetStringValue(IN void* handle,IN const char* strKey,IN const char * sValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetCommandValue(IN void* handle,
                                                               IN const char* strKey);
 *  @brief  设置Command型属性值
 *  @param  void* handle                  [IN]        相机句柄
 *  @param  char* strKey                  [IN]        属性键值
 *  @return 成功,返回MV_OK,失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetCommandValue(IN void* handle,
                                                               IN const char* strKey);
 *  @brief  Set Command value
 *  @param  void* handle                  [IN]        Handle
 *  @param  char* strKey                  [IN]        Key value
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetCommandValue(IN void* handle,IN const char* strKey);

/************************************************************************
 *  @fn     MV_CC_InvalidateNodes
 *  @brief  清除GenICam节点缓存
 *  @param  handle                  [IN]           句柄地址
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn     MV_CC_InvalidateNodes
 *  @brief  Invalidate GenICam Nodes
 *  @param  handle                  [IN]           Handle
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_InvalidateNodes(IN void* handle);


/************************************************************************/
/* 相机参数获取和设置，此模块的所有接口，将逐步废弃，建议用上面的万能接口代替   */
/* Get and set camara parameters, all interfaces of this module will be replaced by general interface*/
/************************************************************************/
/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetWidth(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  获取图像宽度
 *  @param  void* handle                [IN]        相机句柄
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机宽度的信息结构体指针
 *          返回的pstValue结构体的意义
 *                  unsigned int    nCurValue;      // 代表相机当前的宽度值
 *                  unsigned int    nMax;           // 表示相机允许的最大可设置的宽度值
 *                  unsigned int    nMin;           // 表示相机允许的最小可设置的宽度值
 *                  unsigned int    nInc;           // 表示相机设置的宽度增量必须是nInc的倍数，否则无效
 *  @return 成功,返回MV_OK,并获得相应参数信息的结构体, 失败, 返回错误码
 *  
 *          其他整型结构体参数的接口可参照此接口
 
 * @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetWidth(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get image width
 *  @param  void* handle                [IN]        HikCamera Handle
 *          MVCC_INTVALUE* pstValue     [IN][OUT]   Returns the information structure pointer about the camera's width for the caller
 *          The meaning of returns pstValue structure
 *                  unsigned int    nCurValue;      // Represents the current width value of the camera
 *                  unsigned int    nMax;           // Indicates the maximum settable width value allowed by the camera
 *                  unsigned int    nMin;           // Indicates the minimum settable width value allowed by the camera
 *                  unsigned int    nInc;           // Indicates that the width increment set by the camera must be a multiple of nInc, otherwise it is invalid
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
 *          Other Integer structure parameters interface can refer to this interface
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetWidth(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
*  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetWidth(IN void* handle, IN const unsigned int nValue);
*  @brief  设置图像宽度
*  @param  void* handle                [IN]        相机句柄
*          const unsigned int nValue   [IN]        想要设置的相机宽度的值,注意此宽度值必须是MV_CC_GetWidth接口返回的pstValue中的nInc的倍数才能设置成功
*  @return 成功,返回MV_OK,并且相机宽度将会更改为相应值，失败,返回错误码

* @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetWidth(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set image width
 *  @param  void* handle                [IN]        HikCamera Handle
 *          const unsigned int nValue   [IN]        To set the value of the camera width, note that the width value must be a multiple of nInc in the pstValue returned by the MV_CC_GetWidth interface
 *  @return Success, return MV_OK, and the camera width will change to the corresponding value. Failure, return error code
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetWidth(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetHeight(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  获取图像高度
 *  @param  void* handle                [IN]        相机句柄
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机高度的信息结构体指针
 *  @return 成功,返回MV_OK,并将高度信息返回到结构体中，失败,返回错误码
 *  
 *          可参照接口MV_CC_GetWidth
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetHeight(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get image height
 *  @param  void* handle                [IN]        HikCamera handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Return pointer of information structure related to camera height to user
 *  @return Success, return MV_OK, and return height information to the structure. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetHeight(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetHeight(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置图像高度
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        想要设置的相机宽度的值,注意此宽度值必须是MV_CC_GetWidth接口返回的pstValue中的nInc的倍数才能设置成功
 *  @return 成功,返回MV_OK,并且相机高度将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetHeight(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set image height
 *  @param  void* handle                [IN]        HikCamera Handle
 *          const unsigned int nValue   [IN]        HikCamera height value to set, note that this value must be times of nInc of pstValue returned by MV_CC_GetWidth
 *  @return Success, return MV_OK, and the camera height will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetHeight(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetAOIoffsetX(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  获取图像X偏移
 *  @param  void* handle                [IN]        相机句柄
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机X偏移的信息结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 *  
 *          可参照接口MV_CC_GetWidth
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetAOIoffsetX(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get image X offset
 *  @param  void* handle                [IN]        HikCamera Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Return pointer of information structure related to camera X offset to user
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetAOIoffsetX(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetAOIoffsetX(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置图像AOI偏移
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        想要设置的相机AOI的值
 *  @return 成功,返回MV_OK,并且相机AOI偏移将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetAOIoffsetX(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set image X offset
 *  @param  void* handle                [IN]        HikCamera Handle
 *          const unsigned int nValue   [IN]        HikCamera X offset value to set
 *  @return Success, return MV_OK, and the camera X offset will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetAOIoffsetX(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetAOIoffsetY(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  获取图像Y偏移
 *  @param  void* handle                [IN]        相机句柄
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机Y偏移的信息结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 *  
 *          可参照接口MV_CC_GetWidth
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetAOIoffsetY(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get image Y offset
 *  @param  void* handle                [IN]        HikCamera Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Return pointer of information structure related to camera Y offset to user
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetAOIoffsetY(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetAOIoffsetX(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置图像AOI偏移
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        想要设置的相机AOI的值
 *  @return 成功,返回MV_OK,并且相机AOI偏移将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetAOIoffsetY(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set image Y offset
 *  @param  void* handle                [IN]        HikCamera Handle
 *          const unsigned int nValue   [IN]        HikCamera Y offset value to set
 *  @return Success, return MV_OK, and the camera Y offset will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetAOIoffsetY(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetAutoExposureTimeLower(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  获取曝光下限
 *  @param  void* handle                [IN]        相机句柄
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机曝光值下限结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 *  
 *          可参照接口MV_CC_GetWidth
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetAutoExposureTimeLower(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get exposure lower limit
 *  @param  void* handle                [IN]        HikCamera Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Return pointer of information structure related to camera exposure lower to user
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetAutoExposureTimeLower(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetAutoExposureTimeLower(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置曝光值下限
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        想要设置的曝光值下限
 *  @return 成功,返回MV_OK,并且相机曝光下限将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetAutoExposureTimeLower(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set exposure lower limit
 *  @param  void* handle                [IN]        HikCamera Handle
 *          const unsigned int nValue   [IN]        Exposure lower to set
 *  @return Success, return MV_OK, and the camera exposure time lower limit value will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetAutoExposureTimeLower(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetAutoExposureTimeUpper(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  获取曝光上限
 *  @param  void* handle                [IN]        相机句柄
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机曝光值上限结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 *  
 *          可参照接口MV_CC_GetWidth
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetAutoExposureTimeUpper(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get exposure upper limit
 *  @param  void* handle                [IN]        HikCamera Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Return pointer of information structure related to camera exposure upper to user
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetAutoExposureTimeUpper(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetAutoExposureTimeUpper(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置曝光值上限
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        想要设置的曝光值上限
 *  @return 成功,返回MV_OK,并且相机曝光上限将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetAutoExposureTimeUpper(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set exposure upper limit
 *  @param  void* handle                [IN]        HikCamera Handle
 *          const unsigned int nValue   [IN]        Exposure upper to set
 *  @return Success, return MV_OK, and the camera exposure time upper limit value will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetAutoExposureTimeUpper(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetBrightness(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  获取亮度值
 *  @param  void* handle                [IN]        相机句柄
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机亮度结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 *  
 *          可参照接口MV_CC_GetWidth
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetBrightness(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get brightness
 *  @param  void* handle                [IN]        HikCamera Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Return pointer of information structure related to camera brightness to user
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetBrightness(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetBrightness(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置亮度值
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        想要设置的亮度值
 *  @return 成功,返回MV_OK,并且相机亮度将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetBrightness(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set brightness
 *  @param  void* handle                [IN]        HikCamera Handle
 *          const unsigned int nValue   [IN]        Brightness upper to set
 *  @return Success, return MV_OK, and the camera brightness value will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetBrightness(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetFrameRate(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
 *  @brief  获取帧率
 *  @param  void* handle                [IN]        相机句柄
 *          MVCC_FLOATVALUE* pstValue   [IN][OUT]   返回给调用者有关相机帧率的信息结构体指针
 *          返回的pstValue结构体的意义
 *                                      float           fCurValue;      // 表示相机当前的帧率
 *                                      float           fMax;           // 表示相机允许设置的最大帧率
 *                                      float           fMin;           // 表示相机允许设置的最小帧率
 *  @return 成功,返回MV_OK,并获得相应参数信息的结构体, 失败, 返回错误码
 *  
 *          其他浮点型结构体参数的接口可参照此接口
 
 * @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetFrameRate(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
 *  @brief  Get Frame Rate
 *  @param  void* handle                [IN]        HikCamera Handle
 *          MVCC_FLOATVALUE* pstValue   [IN][OUT]   Return pointer of information structure related to camera frame rate to user
 *          The meaning of returns pstValue structure
 *                                      float           fCurValue;      // Indicates the current frame rate of the camera
 *                                      float           fMax;           // Indicates the maximum frame rate allowed by the camera
 *                                      float           fMin;           // Indicates the minimum frame rate allowed by the camera
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
 *          Other interface of Float structure parameters can refer to this interface
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetFrameRate(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetFrameRate(IN void* handle, IN const float fValue);
 *  @brief  设置帧率
 *  @param  void* handle                [IN]        相机句柄
 *          const float fValue          [IN]        想要设置的相机帧率
 *  @return 成功,返回MV_OK,并且相机帧率将会更改为相应值，失败,返回错误码
 
 * @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetFrameRate(IN void* handle, IN const float fValue);
 *  @brief  Set frame rate
 *  @param  void* handle                [IN]        HikCamera Handle
 *          const float fValue          [IN]        HikCamera frame rate to set
 *  @return Success, return MV_OK, and camera frame rate will be changed to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetFrameRate(IN void* handle, IN const float fValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetGain(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
 *  @brief  获取增益
 *  @param  void* handle                [IN]        相机句柄
 *          MVCC_FLOATVALUE* pstValue   [IN][OUT]   返回给调用者有关相机增益的信息结构体指针
 *          返回的pstValue结构体的意义
 *                                      float           fCurValue;      // 表示相机当前的帧率
 *                                      float           fMax;           // 表示相机允许设置的最大帧率
 *                                      float           fMin;           // 表示相机允许设置的最小帧率
 *  @return 成功,返回MV_OK,并获得相应参数信息的结构体, 失败, 返回错误码
 *  
 *          其他浮点型结构体参数的接口可参照此接口
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetGain(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
 *  @brief  Get Gain
 *  @param  void* handle                [IN]        HikCamera Handle
 *          MVCC_FLOATVALUE* pstValue   [IN][OUT]   Return pointer of information structure related to gain to user
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *                                      float           fCurValue;      // HikCamera current gain
 *                                      float           fMax;           // The maximum gain camera allowed
 *                                      float           fMin;           // The minimum gain camera allowed
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
 *          Other interface of Float structure parameters can refer to this interface
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetGain(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetGain(IN void* handle, IN const float fValue);
 *  @brief  设置帧率
 *  @param  void* handle                [IN]        相机句柄
 *          const float fValue          [IN]        想要设置的相机帧率
 *  @return 成功,返回MV_OK,并且相机帧率将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetGain(IN void* handle, IN const float fValue);
 *  @brief  Set Gain
 *  @param  void* handle                [IN]        HikCamera Handle
 *          const float fValue          [IN]        Gain value to set
 *  @return Success, return MV_OK, and the camera gain value will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetGain(IN void* handle, IN const float fValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetExposureTime(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
 *  @brief  获取曝光时间
 *  @param  void* handle                [IN]        相机句柄
 *          MVCC_FLOATVALUE* pstValue   [IN][OUT]   返回给调用者有关相机曝光时间的信息结构体指针
 *          返回的pstValue结构体的意义
 *                                      float           fCurValue;      // 表示相机当前的帧率
 *                                      float           fMax;           // 表示相机允许设置的最大帧率
 *                                      float           fMin;           // 表示相机允许设置的最小帧率
 *  @return 成功,返回MV_OK,并获得相应参数信息的结构体, 失败, 返回错误码
 *  
 *          其他浮点型结构体参数的接口可参照此接口
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetExposureTime(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
 *  @brief  Get exposure time
 *  @param  void* handle                [IN]        HikCamera Handle
 *          MVCC_FLOATVALUE* pstValue   [IN][OUT]   Return pointer of information structure related to exposure time to user
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *                                      float           fCurValue;      // HikCamera current exposure time
 *                                      float           fMax;           // The maximum exposure time camera allowed
 *                                      float           fMin;           // The minimum exposure time camera allowed
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
 *          Other interface of Float structure parameters can refer to this interface
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetExposureTime(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetExposureTime(IN void* handle, IN const float fValue);
 *  @brief  设置曝光时间
 *  @param  void* handle                [IN]        相机句柄
 *          const float fValue          [IN]        想要设置的相机帧率
 *  @return 成功,返回MV_OK,并且相机帧率将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetExposureTime(IN void* handle, IN const float fValue);
 *  @brief  Set exposure time
 *  @param  void* handle                [IN]        HikCamera Handle
 *          const float fValue          [IN]        Exposure time to set
 *  @return Success, return MV_OK, and the camera exposure time value will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetExposureTime(IN void* handle, IN const float fValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetPixelFormat(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  获取像素格式
 *  @param  void* handle                [IN]        相机句柄
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   返回给调用者的有关像素格式的信息结构体指针
 *          返回的pstValue结构体的意义
 *          unsigned int    nCurValue;                              //  相机当前的像素格式，是枚举类型,比如说PixelType_Gvsp_Mono8, 这里获得的是其整型值,具体数值参照PixelType.h的MvGvspPixelType枚举类型
 *          unsigned int    nSupportedNum;                          //  相机支持的像素格式的个数
 *          unsigned int    nSupportValue[MV_MAX_XML_SYMBOLIC_NUM]; //  相机所有支持的像素格式对应的整型值列表，后面要设置像素格式时，参数必须是这个数组中的一种，否则无效
 *  @return 成功,返回MV_OK,并获得相应参数信息的结构体, 失败, 返回错误码
 *  
            其他枚举类型参数接口可参照此接口，有关相应参数的枚举类型对应的整型值请查找PixelType.h 和 CameraParams.h中相应的定义
 
 * @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetPixelFormat(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  Get Pixel Format
 *  @param  void* handle                [IN]        HikCamera Handle
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   Returns the information structure pointer about pixel format for the caller
 *          The meaning of returns pstValue structure
 *          unsigned int    nCurValue;                              //  The current pixel format of the camera, is the enumeration type, such as PixelType_Gvsp_Mono8, here is the integer value, the specific value please refer to MvGvspPixelType enumeration type in PixelType.h
 *          unsigned int    nSupportedNum;                          //  Number of pixel formats supported by the camera
 *          unsigned int    nSupportValue[MV_MAX_XML_SYMBOLIC_NUM]; //  The integer values list correspond to all supported pixel formats of the camera, followed by when set the pixel format, the parameter must be one of this list, otherwise invalid
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
            Other interface of Enumeration structure parameters can refer to this interface, look for the corresponding definition in PixelType.h and CameraParams.h for the integer values of the enum type parameter
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetPixelFormat(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetPixelFormat(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置像素格式
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        要设置的像素格式对应的整型值，调用此接口时可以直接填写枚举值，如MV_CC_SetPixelFormat(m_handle, PixelType_Gvsp_RGB8_Packed);
 *  @return 成功,返回MV_OK,并且相机像素格式将会更改为相应值，失败,返回错误码
 *  
 *          要设置的枚举类型必须是Get接口返回的nSupportValue[MV_MAX_XML_SYMBOLIC_NUM]中的一种，否则会失败
 
 * @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetPixelFormat(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set Pixel Format
 *  @param  void* handle                [IN]        HikCamera Handle
 *          const unsigned int nValue   [IN]        The corresponding integer value for pixel format to be set, when calling this interface can be directly filled in enumeration values, such as MV_CC_SetPixelFormat(m_handle, PixelType_Gvsp_RGB8_Packed);
 *  @return Success, return MV_OK, and the camera pixel format will change to the corresponding value. Failure, return error code
 *  
 *          Other interface of Enumeration structure parameters can refer to this interface, the enumeration type to be set must be one of the nSupportValue [MV_MAX_XML_SYMBOLIC_NUM] returned by the Get interface, otherwise it will fail
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetPixelFormat(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetAcquisitionMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  获取采集模式
 *  @param  void* handle                [IN]        相机句柄
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   返回给调用者的有关采集模式的信息结构体指针
 *  @return 成功,返回MV_OK,并获得相应参数信息的结构体, 失败, 返回错误码
 *  
            可参照接口MV_CC_GetPixelFormat，参考 CameraParam.h 中的 MV_CAM_ACQUISITION_MODE 定义
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetAcquisitionMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  Get acquisition mode
 *  @param  void* handle                [IN]        Handle
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   Structure pointer of acquisition mode
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
            Refer to MV_CC_GetPixelFormat and definition of MV_CAM_ACQUISITION_MODE in CameraParam.h
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetAcquisitionMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetAcquisitionMode(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置像素格式
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        要设置的采集模式对应的整型值
 *  @return 成功,返回MV_OK,并且相机采集模式将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetAcquisitionMode(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set acquisition mode
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Integer value to set corresponding to acquisition mode
 *  @return Success, return MV_OK, and the camera acquisition mode will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetAcquisitionMode(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetGainMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  获取增益模式
 *  @param  void* handle                [IN]        相机句柄
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   返回给调用者的有关增益模式的信息结构体指针
 *  @return 成功,返回MV_OK,并获得相应参数信息的结构体, 失败, 返回错误码
 *  
            可参照接口MV_CC_GetPixelFormat，参考 CameraParam.h 中的 MV_CAM_GAIN_MODE 定义
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetGainMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  Get gain mode
 *  @param  void* handle                [IN]        Handle
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]    Structure pointer of gain mode
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
            Refer to MV_CC_GetPixelFormat and definition of MV_CAM_GAIN_MODE in CameraParam.h
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetGainMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetGainMode(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置增益模式
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        要设置的增益模式对应的整型值
 *  @return 成功,返回MV_OK,并且相机增益模式将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetGainMode(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set gain mode
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Integer value to set corresponding to gain mode
 *  @return Success, return MV_OK, and the camera gain mode will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetGainMode(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetExposureAutoMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  获取自动曝光模式
 *  @param  void* handle                [IN]        相机句柄
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   返回给调用者的有关自动曝光模式的信息结构体指针
 *  @return 成功,返回MV_OK,并获得相应参数信息的结构体, 失败, 返回错误码
 *  
            可参照接口MV_CC_GetPixelFormat，参考 CameraParam.h 中的 MV_CAM_EXPOSURE_AUTO_MODE 定义
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetExposureAutoMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  Get auto exposure mode
 *  @param  void* handle                [IN]        Handle
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   Structure pointer of auto exposure mode
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
            Refer to MV_CC_GetPixelFormat and definition of MV_CAM_EXPOSURE_AUTO_MODE in CameraParam.h
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetExposureAutoMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetExposureAutoMode(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置自动曝光模式
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        要设置的自动曝光模式对应的整型值
 *  @return 成功,返回MV_OK,并且相机自动曝光模式将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetExposureAutoMode(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set auto exposure mode
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Integer value to set corresponding to auto exposure mode
 *  @return Success, return MV_OK, and the camera auto exposure mode will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetExposureAutoMode(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetTriggerMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  获取触发模式
 *  @param  void* handle                [IN]        相机句柄
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   返回给调用者的有关触发模式的信息结构体指针
 *  @return 成功,返回MV_OK,并获得相应参数信息的结构体, 失败, 返回错误码
 *  
            可参照接口MV_CC_GetPixelFormat，参考 CameraParam.h 中的 MV_CAM_TRIGGER_MODE 定义
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetTriggerMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  Get trigger mode
 *  @param  void* handle                [IN]        Handle
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   Structure pointer of trigger mode
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
            Refer to MV_CC_GetPixelFormat and definition of MV_CAM_TRIGGER_MODE in CameraParam.h
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetTriggerMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetTriggerMode(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置触发模式
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        要设置的触发模式对应的整型值
 *  @return 成功,返回MV_OK,并且相机触发模式将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetTriggerMode(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set trigger mode
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Integer value to set corresponding to trigger mode
 *  @return Success, return MV_OK, and the camera trigger mode will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetTriggerMode(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetTriggerDelay(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
 *  @brief  获取触发延时
 *  @param  void* handle                [IN]        相机句柄
 *          MVCC_FLOATVALUE* pstValue   [IN][OUT]   返回给调用者有关相机触发延时的信息结构体指针
 *  @return 成功,返回MV_OK,并获得相应参数信息的结构体, 失败, 返回错误码
 *  
 *          可参照接口MV_CC_GetFrameRate
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetTriggerDelay(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
 *  @brief  Get tigger delay
 *  @param  void* handle                [IN]        Handle
 *          MVCC_FLOATVALUE* pstValue   [IN][OUT]   Structure pointer of trigger delay
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
 *          Refer to MV_CC_GetFrameRate
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetTriggerDelay(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetTriggerDelay(IN void* handle, IN const float fValue);
 *  @brief  设置触发延时
 *  @param  void* handle                [IN]        相机句柄
 *          const float fValue          [IN]        想要设置的相机触发延时
 *  @return 成功,返回MV_OK,并且相机触发延时将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetTriggerDelay(IN void* handle, IN const float fValue);
 *  @brief  Set tigger delay
 *  @param  void* handle                [IN]        Handle
 *          const float fValue          [IN]        Trigger delay to set
 *  @return Success, return MV_OK, and the camera trigger delay will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetTriggerDelay(IN void* handle, IN const float fValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetTriggerSource(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  获取触发源
 *  @param  void* handle                [IN]        相机句柄
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   返回给调用者的有关触发源的信息结构体指针
 *  @return 成功,返回MV_OK,并获得相应参数信息的结构体, 失败, 返回错误码
 *  
            可参照接口MV_CC_GetPixelFormat，参考 CameraParam.h 中的 MV_CAM_TRIGGER_SOURCE 定义
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetTriggerSource(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  Get trigger source
 *  @param  void* handle                [IN]        Handle
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   Structure pointer of trigger source
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
            Refer to MV_CC_GetPixelFormat and definition of MV_CAM_TRIGGER_SOURCE in CameraParam.h
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetTriggerSource(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetTriggerSource(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置触发源
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        要设置的触发源对应的整型值
 *  @return 成功,返回MV_OK,并且相机触发源将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetTriggerSource(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set trigger source
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Integer value to set corresponding to trigger source
 *  @return Success, return MV_OK, and the camera trigger source will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetTriggerSource(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_TriggerSoftwareExecute(IN void* handle);
 *  @brief  软触发一次（接口仅在已选择的触发源为软件触发时有效）
 *  @param  void* handle                [IN]        相机句柄
 *  @return 成功,返回MV_OK, 失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_TriggerSoftwareExecute(IN void* handle);
 *  @brief  Execute software trigger once (this interface only valid when the trigger source is set to software)
 *  @param  void* handle                [IN]        Handle
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_TriggerSoftwareExecute(IN void* handle);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetGammaSelector(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  获取Gamma类型
 *  @param  void* handle                [IN]        相机句柄
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   返回给调用者的有关Gamma类型的信息结构体指针
 *  @return 成功,返回MV_OK,并获得相应参数信息的结构体, 失败, 返回错误码
 *  
            可参照接口MV_CC_GetPixelFormat，参考 CameraParam.h 中的 MV_CAM_GAMMA_SELECTOR 定义
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetGammaSelector(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  Get Gamma mode
 *  @param  void* handle                [IN]        Handle
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   Structure pointer of gamma mode
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
            Refer to MV_CC_GetPixelFormat and definition of MV_CAM_GAMMA_SELECTOR in CameraParam.h
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetGammaSelector(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetGammaSelector(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置Gamma类型
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        要设置的Gamma类型对应的整型值
 *  @return 成功,返回MV_OK,并且相机Gamma类型将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetGammaSelector(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set Gamma mode
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Integer value to set corresponding to gamma mode
 *  @return Success, return MV_OK, and the camera gamma mode will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetGammaSelector(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetGamma(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
 *  @brief  获取Gamma值
 *  @param  void* handle                [IN]        相机句柄
 *          MVCC_FLOATVALUE* pstValue   [IN][OUT]   返回给调用者有关相机Gamma值的信息结构体指针
 *  @return 成功,返回MV_OK,并获得相应参数信息的结构体, 失败, 返回错误码
 *  
 *          可参照接口MV_CC_GetFrameRate
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetGamma(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
 *  @brief  Get Gamma value
 *  @param  void* handle                [IN]        Handle
 *          MVCC_FLOATVALUE* pstValue   [IN][OUT]   Structure pointer of gamma value
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
 *          Refer to MV_CC_GetFrameRate
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetGamma(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetGamma(IN void* handle, IN const float fValue);
 *  @brief  设置Gamma值
 *  @param  void* handle                [IN]        相机句柄
 *          const float fValue          [IN]        想要设置的相机Gamma值
 *  @return 成功,返回MV_OK,并且相机Gamma值将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetGamma(IN void* handle, IN const float fValue);
 *  @brief  Set Gamma value
 *  @param  void* handle                [IN]        Handle
 *          const float fValue          [IN]        Gamma value to set
 *  @return Success, return MV_OK, and the camera gamma value will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetGamma(IN void* handle, IN const float fValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetSharpness(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  获取锐度
 *  @param  void* handle                [IN]        相机句柄
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机锐度结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 *  
 *          可参照接口MV_CC_GetWidth
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetSharpness(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get sharpness
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of sharpness
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetSharpness(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetSharpness(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置锐度
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        想要设置的锐度
 *  @return 成功,返回MV_OK,并且相机锐度将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetSharpness(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set sharpness
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Sharpness to set
 *  @return Success, return MV_OK, and the camera sharpness will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetSharpness(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetHue(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  获取灰度
 *  @param  void* handle                [IN]        相机句柄
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机灰度结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 *  
 *          可参照接口MV_CC_GetWidth
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetHue(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get Hue
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of Hue
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetHue(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetHue(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置灰度
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        想要设置的灰度
 *  @return 成功,返回MV_OK,并且相机灰度将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetHue(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set Hue
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Hue to set
 *  @return Success, return MV_OK, and the camera Hue will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetHue(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetSaturation(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  获取饱和度
 *  @param  void* handle                [IN]        相机句柄
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机饱和度结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 *  
 *          可参照接口MV_CC_GetWidth
 
  *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetSaturation(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get Saturation
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of Saturation
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetSaturation(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetSaturation(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置饱和度
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        想要设置的饱和度
 *  @return 成功,返回MV_OK,并且相机饱和度将会更改为相应值，失败,返回错误码
 
*  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetSaturation(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set Saturation
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Saturation to set
 *  @return Success, return MV_OK, and the camera Saturation will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetSaturation(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetBalanceWhiteAuto(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  获取自动白平衡
 *  @param  void* handle                [IN]        相机句柄
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   返回给调用者的有关自动白平衡的信息结构体指针
 *  @return 成功,返回MV_OK,并获得相应参数信息的结构体, 失败, 返回错误码
 *  
            可参照接口MV_CC_GetPixelFormat，参考 CameraParam.h 中的 MV_CAM_BALANCEWHITE_AUTO 定义
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetBalanceWhiteAuto(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  Get Auto white balance
 *  @param  void* handle                [IN]        Handle
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   Structure pointer of auto white balance
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
            Refer to MV_CC_GetPixelFormat and definition of MV_CAM_BALANCEWHITE_AUTO in CameraParam.h
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetBalanceWhiteAuto(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetBalanceWhiteAuto(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置自动白平衡
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        要设置的自动白平衡对应的整型值
 *  @return 成功,返回MV_OK,并且相机自动白平衡将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetBalanceWhiteAuto(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set Auto white balance
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Integer value to set corresponding to auto white balance
 *  @return Success, return MV_OK, and the camera auto white balance will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetBalanceWhiteAuto(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetBalanceRatioRed(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  获取白平衡 红
 *  @param  void* handle                [IN]        相机句柄
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机白平衡 红结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 *  
 *          可参照接口MV_CC_GetWidth
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetBalanceRatioRed(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get white balance red
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of white balance red
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetBalanceRatioRed(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetBalanceRatioRed(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置白平衡 红
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        想要设置的白平衡 红
 *  @return 成功,返回MV_OK,并且相机白平衡 红将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetBalanceRatioRed(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set white balance red
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        White balance red to set
 *  @return Success, return MV_OK, and the camera white balance red will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetBalanceRatioRed(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetBalanceRatioGreen(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  获取白平衡 绿
 *  @param  void* handle                [IN]        相机句柄
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机白平衡 绿结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 *  
 *          可参照接口MV_CC_GetWidth
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetBalanceRatioGreen(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get white balance green
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of white balance green
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetBalanceRatioGreen(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetBalanceRatioGreen(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置白平衡 绿
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        想要设置的白平衡 绿
 *  @return 成功,返回MV_OK,并且相机白平衡 绿将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetBalanceRatioGreen(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set white balance green
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        White balance green to set
 *  @return Success, return MV_OK, and the camera white balance green will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetBalanceRatioGreen(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetBalanceRatioBlue(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  获取白平衡 蓝
 *  @param  void* handle                [IN]        相机句柄
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机白平衡 蓝结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 *  
 *          可参照接口MV_CC_GetWidth
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetBalanceRatioBlue(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get white balance blue
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of white balance blue
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetBalanceRatioBlue(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetBalanceRatioBlue(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置白平衡 蓝
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        想要设置的白平衡 蓝
 *  @return 成功,返回MV_OK,并且相机白平衡 蓝将会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetBalanceRatioBlue(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set white balance blue
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        White balance blue to set
 *  @return Success, return MV_OK, and the camera white balance blue will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetBalanceRatioBlue(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetFrameSpecInfoAbility(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  获取水印信息内包含的信息类型
 *  @param  void* handle                [IN]        相机句柄
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机水印信息内包含的信息类型结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 *  
 *          可参照接口MV_CC_GetWidth
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetFrameSpecInfoAbility(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get information type included by frame stamp
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of information type included by frame stamp
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetFrameSpecInfoAbility(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetFrameSpecInfoAbility(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置水印信息内包含的信息类型
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        想要设置的水印信息内包含的信息类型
 *  @return 成功,返回MV_OK,并且相机水印信息内包含的信息类型会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetFrameSpecInfoAbility(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set information type included by frame stamp
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Information type included by frame stamp to set
 *  @return Success, return MV_OK, and the camera information type included by frame stamp will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetFrameSpecInfoAbility(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetDeviceUserID(IN void* handle, IN OUT MVCC_STRINGVALUE* pstValue);
 *  @brief  获取设备自定义名字
 *  @param  void* handle                [IN]        相机句柄
 *          MVCC_STRINGVALUE* pstValue  [IN OUT]    返回给调用者有关相机名字结构体指针
 *  @return 成功,返回MV_OK,并且获取到相机的自定义名字，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetDeviceUserID(IN void* handle, IN OUT MVCC_STRINGVALUE* pstValue);
 *  @brief  Get device user defined name
 *  @param  void* handle                [IN]        Handle
 *          MVCC_STRINGVALUE* pstValue  [IN OUT]    Structure pointer of device name
 *  @return Success, return MV_OK, and get the camera user defined name. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetDeviceUserID(IN void* handle, IN OUT MVCC_STRINGVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetDeviceUserID(IN void* handle, IN const char* chValue);
 *  @brief  设置设备自定义名字
 *  @param  void* handle                [IN]        相机句柄
 *          IN const char* chValue      [IN]        设备名字
 *  @return 成功,返回MV_OK,并且设置设备自定义名字，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetDeviceUserID(IN void* handle, IN const char* chValue);
 *  @brief  Set device user defined name
 *  @param  void* handle                [IN]        Handle
 *          IN const char* chValue      [IN]        Device name
 *  @return Success, return MV_OK, and set the camera user defined name. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetDeviceUserID(IN void* handle, IN const char* chValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetBurstFrameCount(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  获取一次触发的帧数
 *  @param  void* handle                [IN]        相机句柄
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机一次触发的帧数结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 *  
 *          可参照接口MV_CC_GetWidth
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetBurstFrameCount(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get frame number trigger by once
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of frame number trigger by once
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetBurstFrameCount(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetBurstFrameCount(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置一次触发的帧数
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        想要设置的一次触发的帧数
 *  @return 成功,返回MV_OK,并且相机一次触发的帧数会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetBurstFrameCount(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set frame number trigger by once
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Frame number trigger by once to set
 *  @return Success, return MV_OK, and the camera frame number trigger by once will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetBurstFrameCount(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetAcquisitionLineRate(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  获取行频
 *  @param  void* handle                [IN]        相机句柄
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机行频结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 *  
 *          可参照接口MV_CC_GetWidth
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetAcquisitionLineRate(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get line rate
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of line rate
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetAcquisitionLineRate(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetAcquisitionLineRate(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置行频
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        想要设置的行频
 *  @return 成功,返回MV_OK,并且相机行频会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetAcquisitionLineRate(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set line rate
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Line rate to set
 *  @return Success, return MV_OK, and the camera line rate will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetAcquisitionLineRate(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetHeartBeatTimeout(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  获取心跳信息
 *  @param  void* handle                [IN]        相机句柄
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机心跳信息结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 *  
 *          可参照接口MV_CC_GetWidth
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetHeartBeatTimeout(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get heartbeat information
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of heartbeat information
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetHeartBeatTimeout(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetHeartBeatTimeout(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置心跳信息
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        想要设置的心跳信息
 *  @return 成功,返回MV_OK,并且相机心跳信息会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_SetHeartBeatTimeout(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set heartbeat information
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Heartbeat information to set
 *  @return Success, return MV_OK, and the camera heartbeat information will change to the corresponding value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetHeartBeatTimeout(IN void* handle, IN const unsigned int nValue);




/************************************************************************/
/* 设备升级 和 寄存器读写 和异常、事件回调                            	*/
/* Device upgrade, register read and write and exception callback       */
/************************************************************************/
// 设备本地升级
// Device Local Upgrade
/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_LocalUpgrade(IN void* handle, 
                                                            const void *pFilePathName);
 *  @brief  设备本地升级
 *  @param  void* handle                  [IN]        相机句柄
 *  @param  void *pFilePathName           [IN]        文件名
 *  @return 成功,返回MV_OK,失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_LocalUpgrade(IN void* handle, 
                                                            const void *pFilePathName);
 *  @brief  Device Local Upgrade
 *  @param  void* handle                  [IN]        HikCamera handle
 *  @param  void *pFilePathName           [IN]        File name
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_LocalUpgrade(IN void* handle, const void *pFilePathName);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetUpgradeProcess(IN void* handle,
                                                                 unsigned int* pnProcess);
 *  @brief  获取升级进度
 *  @param  void* handle                  [IN]        相机句柄
 *  @param  unsigned int* pnProcess       [OUT]       进度接收地址
 *  @return 成功,返回MV_OK,失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetUpgradeProcess(IN void* handle,
                                                                 unsigned int* pnProcess);
 *  @brief  Get Upgrade Progress
 *  @param  void* handle                  [IN]        HikCamera handle
 *  @param  unsigned int* pnProcess       [OUT]       Progress receiving address
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetUpgradeProcess(IN void* handle, unsigned int* pnProcess);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetOptimalPacketSize(IN void* handle);
 *  @brief  获取最佳的packet size，该接口目前只支持GigE相机
 *  @param  void* handle                  [IN]        相机句柄
 *  @return 最佳packetsize
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_CC_GetOptimalPacketSize(IN void* handle);
 *  @brief  Get the optimal Packet Size, Only support GigE HikCamera
 *  @param  void* handle                  [IN]        HikCamera handle
 *  @return Optimal packetsize
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetOptimalPacketSize(IN void* handle);

/************************************************************************
 *  @fn     MV_CC_ReadMemory
 *  @brief  读内存
 *  @param  handle：设备句柄
 *  @param  pBuffer：作为返回值使用，保存读到的内存值（内存值是按照大端模式存储的）
 *  @param  nAddress：待读取的内存地址，该地址可以从设备的Camera.xml文件中获取，形如xxx_RegAddr的xml节点值
                  （设备的Camera.xml文件会在设备打开之后自动生成在应用程序的当前目录中）
 *  @param  nLength：待读取的内存长度
 *  @return 见返回错误码
 
 *  @fn     MV_CC_ReadMemory
 *  @brief  Read Memory
 *  @param  handle: Device Handle
 *  @param  pBuffer: Used as a return value, save the read-in memory value ( Memory value is stored in accordance with the big end model)
 *  @param  nAddress: Memory address to be read, which can be obtained from the HikCamera.xml file of the device, the form xml node value of xxx_RegAddr
                     (HikCamera.xml file of device is automatically generated in the application's current directory after the device is opened)
 *  @param  nLength: Length of the memory to be read
 *  @return Refer to the return error code
*************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_ReadMemory(IN void* handle , void *pBuffer, int64_t nAddress, int64_t nLength);

/************************************************************************
 *  @fn     MV_CC_WriteMemory
 *  @brief  写内存
 *  @param  handle：设备句柄
 *  @param  pBuffer：待写入的内存值（注意内存值要按照大端模式存储）
 *  @param  nAddress：待写入的内存地址，该地址可以从设备的Camera.xml文件中获取，形如xxx_RegAddr的xml节点值
                  （设备的Camera.xml文件会在设备打开之后自动生成在应用程序的当前目录中）
 *  @param  nLength：待写入的内存长度
 *  @return 见返回错误码
 
 *  @fn     MV_CC_WriteMemory
 *  @brief  Write Memory
 *  @param  handle: Device Handle
 *  @param  pBuffer: Memory value to be written ( Note the memory value to be stored in accordance with the big end model)
 *  @param  nAddress: Memory address to be written, which can be obtained from the HikCamera.xml file of the device, the form xml node value of xxx_RegAddr
                     (HikCamera.xml file of device is automatically generated in the application's current directory after the device is opened)
 *  @param  nLength: Length of the memory to be written
 *  @return Refer to the return error code
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_WriteMemory(IN void* handle , const void *pBuffer, int64_t nAddress, int64_t nLength);

// 注册异常消息回调，在打开设备之后调用
// Register exception message callback, call after open device
/************************************************************************
 *  @fn     MV_CC_RegisterExceptionCallBack
 *  @brief  注册异常消息回调，在打开设备之后调用
 *  @param  handle：设备句柄
 *  @param  cbException       [IN]      异常回调函数指针
 *  @param  pUser             [IN]      用户自定义变量
 *  @return 见返回错误码
 
 *  @fn     MV_CC_RegisterExceptionCallBack
 *  @brief  Register Exception Message CallBack, call after open device
 *  @param  handle: Device handle
 *  @param  cbException       [IN]       Exception Message CallBack Function Pointer
 *  @param  pUser             [IN]       User defined variable
 *  @return Refer to error code
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_RegisterExceptionCallBack(IN void* handle, 
                                                             void(__stdcall* cbException)(unsigned int nMsgType, void* pUser),
                                                             void* pUser);

/************************************************************************
 *  @fn     MV_CC_RegisterAllEventCallBack
 *  @brief  注册全部事件回调，在打开设备之后调用,只支持GIGE
 *  @param  handle：设备句柄
 *  @param  cbEvent           [IN]      异常回调函数指针
 *  @param  pUser             [IN]      用户自定义变量
 *  @return 见返回错误码
 
 *  @fn     MV_CC_RegisterEventCallBack
 *  @brief  Register event callback, which is called after the device is opened
 *  @param  handle: Device handel
 *  @param  cbEvent           [IN]      Exception CallBack Function Pointer
 *  @param  pUser             [IN]      User defined variable
 *  @return Refer to error code
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_RegisterAllEventCallBack(void* handle, 
                                                         void(__stdcall* cbEvent)(MV_EVENT_OUT_INFO * pEventInfo, void* pUser),
                                                         void* pUser);

/************************************************************************
 *  @fn     MV_CC_RegisterEventCallBackEx
 *  @brief  注册单个事件回调，在打开设备之后调用,只支持GIGE
 *  @param  handle：设备句柄
 *  @param  pEventName        [IN]      事件名称
 *  @param  cbEvent           [IN]      异常回调函数指针
 *  @param  pUser             [IN]      用户自定义变量
 *  @return 见返回错误码
 
 
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_RegisterEventCallBackEx(void* handle, const char* pEventName,
                                                         void(__stdcall* cbEvent)(MV_EVENT_OUT_INFO * pEventInfo, void* pUser),
                                                         void* pUser);


/************************************************************************/
/* GigEVision 设备独有的接口                                     		*/
/* GigEVision device specific interface                                 */
/************************************************************************/
/************************************************************************
 *  @fn     MV_GIGE_ForceIpEx
 *  @brief  强制IP
 *  @param  handle：设备句柄
 *  @param  nIP               [IN]      设置的IP
 *  @param  nSubNetMask       [IN]      子网掩码
 *  @param  nDefaultGateWay   [IN]      默认网关
 *  @return 见返回错误码
 
 *  @fn     MV_GIGE_ForceIpEx
 *  @brief  Force IP
 *  @param  handle: Device handel
 *  @param  nIP               [IN]      IP to set
 *  @param  nSubNetMask       [IN]      Subnet mask
 *  @param  nDefaultGateWay   [IN]      Default gateway
 *  @return Refer to error code
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_ForceIpEx(IN void* handle, unsigned int nIP, unsigned int nSubNetMask, unsigned int nDefaultGateWay);

/************************************************************************/
/* GigEVision 设备独有的接口                                     */
/************************************************************************/
/************************************************************************
 *  @fn     MV_GIGE_SetIpConfig
 *  @brief  配置IP方式
 *  @param  handle：设备句柄
 *  @param  nType               [IN]      IP类型，见MV_IP_CFG_x
 *  @return 见返回错误码
 
 *  @fn     MV_GIGE_SetIpConfig
 *  @brief  IP configuration method
 *  @param  handle: Device handel
 *  @param  nType               [IN]      IP type, refer to MV_IP_CFG_x
 *  @return Refer to error code
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_SetIpConfig(IN void* handle, unsigned int nType);

/************************************************************************
 *  @fn     MV_GIGE_SetNetTransMode
 *  @brief  设置仅使用某种模式,type: MV_NET_TRANS_x，不设置时，默认优先使用driver
 *  @param  handle：设备句柄
 *  @param  nType               [IN]      网络传输模式，见MV_NET_TRANS_x
 *  @return 见返回错误码
 
 *  @fn     MV_GIGE_SetNetTransMode
 *  @brief  Set to use only one mode,type: MV_NET_TRANS_x. When do not set, priority is to use driver by default
 *  @param  handle: Device handel
 *  @param  nType               [IN]      Net transmission mode, refer to MV_NET_TRANS_x
 *  @return Refer to error code
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_SetNetTransMode(IN void* handle, unsigned int nType);

/************************************************************************
 *  @fn     MV_GIGE_GetNetTransInfo
 *  @brief  获取网络传输信息
 *  @param  handle：设备句柄
 *  @param  pstInfo             [OUT]      信息结构体
 *  @return 见返回错误码
 
 *  @fn     MV_GIGE_GetNetTransInfo
 *  @brief  Get net transmission information
 *  @param  handle: Device handel
 *  @param  pstInfo             [OUT]      Information Structure
 *  @return Refer to error code
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_GetNetTransInfo(IN void* handle, MV_NETTRANS_INFO* pstInfo);

/************************************************************************
 *  @fn     MV_GIGE_SetGvcpTimeout
 *  @brief  设置GVCP命令超时时间
 *  @param  handle                 [IN]           句柄地址
 *  @param  nMillisec              [IN]           超时时间，以毫秒位单位，范围：0-10000
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_GIGE_SetGvcpTimeout
 *  @brief  Set GVCP cammand timeout
 *  @param  handle                 [IN]           Handle
 *  @param  nMillisec              [IN]           Timeout, ms as unit, range: 0-10000
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_SetGvcpTimeout(void* handle, unsigned int nMillisec);

/************************************************************************
 *  @fn     MV_GIGE_SetResend
 *  @brief  设置是否打开重发包支持，及重发包设置
 *  @param  handle                 [IN]           句柄地址
 *  @param  bEnable                [IN]           是否支持重发包
 *  @param  nMaxResendPercent      [IN]           最大重发比
 *  @param  nResendTimeout         [IN]           重发超时时间
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_GIGE_SetResend
 *  @brief  Set whethe to enable resend, and set resend
 *  @param  handle                 [IN]           Handle
 *  @param  bEnable                [IN]           enable resend
 *  @param  nMaxResendPercent      [IN]           Max resend persent
 *  @param  nResendTimeout         [IN]           Resend timeout
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
#ifndef __cplusplus
MV_CAMCTRL_API int __stdcall MV_GIGE_SetResend(void* handle, unsigned int bEnable, unsigned int nMaxResendPercent, unsigned int nResendTimeout);
#else
MV_CAMCTRL_API int __stdcall MV_GIGE_SetResend(void* handle, unsigned int bEnable, unsigned int nMaxResendPercent = 10, unsigned int nResendTimeout = 50);
#endif

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_GIGE_GetGevSCPSPacketSize(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  获取网络包大小
 *  @param  void* handle                [IN]        相机句柄
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机网络包大小结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 *  
 *          可参照接口MV_CC_GetWidth
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_GIGE_GetGevSCPSPacketSize(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get network packet size
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of network packet size
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_GetGevSCPSPacketSize(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_GIGE_SetGevSCPSPacketSize(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置网络包大小
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        想要设置的网络包大小
 *  @return 成功,返回MV_OK,并且相机网络包大小会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_GIGE_SetGevSCPSPacketSize(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set network packet size
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Packet size to set
 *  @return Success, return MV_OK, and change packet size to setting value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_SetGevSCPSPacketSize(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_GIGE_GetGevSCPD(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  获取网络包发送间隔
 *  @param  void* handle                [IN]        相机句柄
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   返回给调用者有关相机网络包发送间隔结构体指针
 *  @return 成功,返回MV_OK,失败,返回错误码
 *  
 *          可参照接口MV_CC_GetWidth
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_GIGE_GetGevSCPD(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get network packet sending delay
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of network packet sending delay
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_GetGevSCPD(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_GIGE_SetGevSCPD(IN void* handle, IN const unsigned int nValue);
 *  @brief  设置网络包发送间隔
 *  @param  void* handle                [IN]        相机句柄
 *          const unsigned int nValue   [IN]        想要设置的网络包发送间隔
 *  @return 成功,返回MV_OK,并且相机网络包发送间隔会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_GIGE_SetGevSCPD(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set network packet sending delay
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Packet delay to set
 *  @return Success, return MV_OK, and change packet delay to setting value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_SetGevSCPD(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_GIGE_GetGevSCDA(IN void* handle, unsigned int* pnIP);
 *  @brief  获取接收端IP地址，0xa9fe0102 表示 169.254.1.2
 *  @param  void* handle                [IN]        相机句柄
 *  @param  unsigned int* pnIP          [IN][OUT]   返回给调用者接收端IP地址
 *  @return 成功,返回MV_OK,失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_GIGE_GetGevSCDA(IN void* handle, unsigned int* pnIP);
 *  @brief  Get receiver IP address, 0xa9fe0102 indicates 169.254.1.2
 *  @param  void* handle                [IN]        Handle
 *  @param  unsigned int* pnIP          [IN][OUT]   Receiver IP address
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_GetGevSCDA(IN void* handle, unsigned int* pnIP);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_GIGE_SetGevSCDA(IN void* handle, unsigned int nIP);
 *  @brief  设置接收端IP地址
 *  @param  void* handle                [IN]        相机句柄
 *          unsigned int nIP            [IN]        想要设置的接收端IP地址
 *  @return 成功,返回MV_OK,并且相机接收端IP地址会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_GIGE_SetGevSCDA(IN void* handle, unsigned int nIP);
 *  @brief  Set receiver IP address
 *  @param  void* handle                [IN]        Handel
 *          unsigned int nIP            [IN]        Receiver IP address to set
 *  @return Success, return MV_OK, and change receiver IP address to setting value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_SetGevSCDA(IN void* handle, unsigned int nIP);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_GIGE_GetGevSCSP(IN void* handle, unsigned int* pnPort);
 *  @brief  获取发送端的端口号
 *  @param  void* handle                [IN]        相机句柄
 *  @param  unsigned int* pnPort        [IN][OUT]   返回给调用者发送端的端口号
 *  @return 成功,返回MV_OK,失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_GIGE_GetGevSCSP(IN void* handle, unsigned int* pnPort);
 *  @brief  Get transmitter port number
 *  @param  void* handle                [IN]        Handle
 *  @param  unsigned int* pnPort        [IN][OUT]   Transmitter port number
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_GetGevSCSP(IN void* handle, unsigned int* pnPort);

/************************************************************************
 *  @fn     MV_CAMCTRL_API int __stdcall MV_GIGE_SetGevSCSP(IN void* handle, unsigned int nPort);
 *  @brief  设置发送端的端口号
 *  @param  void* handle                [IN]        相机句柄
 *          unsigned int nPort          [IN]        想要设置的发送端的端口号
 *  @return 成功,返回MV_OK,并且相机发送端的端口号会更改为相应值，失败,返回错误码
 
 *  @fn     MV_CAMCTRL_API int __stdcall MV_GIGE_SetGevSCSP(IN void* handle, unsigned int nPort);
 *  @brief  Set transmitter port number
 *  @param  void* handle                [IN]        Handle
 *          unsigned int nPort          [IN]        Transmitter port number to set
 *  @return Success, return MV_OK, and change transmitter port number to setting value. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_SetGevSCSP(IN void* handle, unsigned int nPort);

/************************************************************************
 * @fn      MV_GIGE_SetTransmissionType
 * @brief   设置传输模式，可以为单播模式、组播模式等
 * @param   handle                      [IN]       相机句柄
 * @param   stTransmissionType          [IN]       传输模式结构体
 * @return 返回成功或错误码
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_SetTransmissionType(void* handle, MV_TRANSMISSION_TYPE * pstTransmissionType);

/************************************************************************
 * @fn      MV_GIGE_IssueActionCommand
 * @brief   发出动作命令
 * @param   pstActionCmdInfo                   [IN]       动作命令信息 | en:Action Command
 * @param   MV_ACTION_CMD_RESULT_LIST          [OUT]      动作命令返回信息列表 | en:Action Command Result List
 * @return 返回成功或错误码
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_IssueActionCommand(IN MV_ACTION_CMD_INFO* pstActionCmdInfo, OUT MV_ACTION_CMD_RESULT_LIST* pstActionCmdResults);


/************************************************************************/
/* CameraLink 设备独有的接口                                     */
/************************************************************************/
/************************************************************************
 *  @fn     MV_CAML_SetDeviceBauderate
 *  @brief  设置设备波特率
 *  @param  handle：设备句柄
 *  @param  nBaudrate               [IN]      设置的波特率值，数值参考CameraParams.h中宏定义，如#define MV_CAML_BAUDRATE_9600  0x00000001
 *  @return 见返回错误码
 
 *  @fn     MV_CAML_SetDeviceBauderate
 *  @brief  Set device bauderate using one of the CL_BAUDRATE_XXXX value
 *  @param  handle Handle
 *  @param  nBaudrate               [IN]      baud rate to set. Refer to the 'CameraParams.h' for parameter definitions, for example, #define MV_CAML_BAUDRATE_9600  0x00000001
 *  @return Refer to error code
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CAML_SetDeviceBauderate(IN void* handle, unsigned int nBaudrate);

/************************************************************************
 *  @fn     MV_CAML_GetDeviceBauderate
 *  @brief  获取设备波特率
 *  @param  handle：设备句柄
 *  @param  pnCurrentBaudrate               [OUT]      波特率信息指针，数值参考CameraParams.h中宏定义，如#define MV_CAML_BAUDRATE_9600  0x00000001
 *  @return 见返回错误码
 
 *  @fn     MV_CAML_GetDeviceBauderate
 *  @brief  Returns the current device bauderate, using one of the CL_BAUDRATE_XXXX value
 *  @param  handle Handle
 *  @param  pnCurrentBaudrate               [OUT]      Return pointer of baud rate to user. Refer to the 'CameraParams.h' for parameter definitions, for example, #define MV_CAML_BAUDRATE_9600  0x00000001
 *  @return Refer to error code
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CAML_GetDeviceBauderate(IN void* handle,unsigned int* pnCurrentBaudrate);

/************************************************************************
 *  @fn     MV_CAML_GetSupportBauderates
 *  @brief  获取设备与主机间连接支持的波特率
 *  @param  handle：设备句柄
 *  @param  pnBaudrateAblity               [OUT]      支持的波特率信息的指针。所支持波特率的或运算结果，单个数值参考CameraParams.h中宏定义，如#define MV_CAML_BAUDRATE_9600  0x00000001
 *  @return 见返回错误码
 
 *  @fn     MV_CAML_GetSupportBauderates
 *  @brief  Returns supported bauderates of the combined device and host interface
 *  @param  handle Handle
 *  @param  pnBaudrateAblity               [OUT]      Return pointer of the supported bauderates to user. 'OR' operation results of the supported bauderates. Refer to the 'CameraParams.h' for single value definitions, for example, #define MV_CAML_BAUDRATE_9600  0x00000001
 *  @return Refer to error code
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CAML_GetSupportBauderates(IN void* handle,unsigned int* pnBaudrateAblity);

/************************************************************************
 *  @fn     MV_CAML_SetGenCPTimeOut
 *  @brief  设置串口操作等待时长
 *  @param  handle：设备句柄
 *  @param  nMillisec               [IN]      串口操作的等待时长, ms
 *  @return 见返回错误码
 
 *  @fn     MV_CAML_SetGenCPTimeOut
 *  @brief  Sets the timeout for operations on the serial port
 *  @param  handle Handle
 *  @param  nMillisec               [IN]      Timeout in [ms] for operations on the serial port.
 *  @return Refer to error code
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CAML_SetGenCPTimeOut(IN void* handle, unsigned int nMillisec);


/************************************************************************/
/* XML解析树的生成                                                      */
/* XML parse tree generation                                            */
/************************************************************************/
/***********************************************************************
 *  @fn         MV_XML_GetGenICamXML
 *  @brief      获取相机属性树XML
 *  @param       handle                 [IN]          句柄
 *  @param       pData                  [OUT]         图像数据接收指针
 *  @param       nDataSize              [IN]          接收缓存大小
 *  @param       pnDataLen              [OUT]         实际数据大小
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_XML_GetGenICamXML
 *  @brief      Get camera feature tree XML
 *  @param       handle                 [IN]          Handle
 *  @param       pData                  [OUT]         Recevied image buffer pointer
 *  @param       nDataSize              [IN]          Recevied buffer size
 *  @param       pnDataLen              [OUT]         Actual data size
 *  @return Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_XML_GetGenICamXML(IN void* handle, IN OUT unsigned char* pData, IN unsigned int nDataSize, OUT unsigned int* pnDataLen);

/***********************************************************************
 *  @fn         MV_XML_GetRootNode
 *  @brief      获取根节点
 *  @param       handle                 [IN]          句柄
 *  @param       pstNode                [OUT]         根节点信息结构体
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_XML_GetRootNode
 *  @brief      Get root node
 *  @param       handle                 [IN]          Handle
 *  @param       pstNode                [OUT]         Root node information structure
 *  @return Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_XML_GetRootNode(IN void* handle, IN OUT MV_XML_NODE_FEATURE* pstNode);

/***********************************************************************
 *  @fn         MV_XML_GetChildren
 *  @brief      从xml中获取指定节点的所有子节点，根节点为Root
 *  @param       handle                 [IN]          句柄
 *  @param       pstNode                [IN]          根节点信息结构体
 *  @param       pstNodesList           [OUT]         节点列表结构体
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_XML_GetChildren
 *  @brief      Get all children node of specific node from xml, root node is Root
 *  @param       handle                 [IN]          Handle
 *  @param       pstNode                [IN]          Root node information structure
 *  @param       pstNodesList           [OUT]         Node information structure
 *  @return Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_XML_GetChildren(IN void* handle, IN MV_XML_NODE_FEATURE* pstNode, IN OUT MV_XML_NODES_LIST* pstNodesList);

/***********************************************************************
 *  @fn         MV_XML_GetNodeFeature
 *  @brief      获得当前节点的属性
 *  @param       handle                 [IN]          句柄
 *  @param       pstNode                [IN]          根节点信息结构体
 *  @param       pstFeature             [OUT]         当前节点属性结构体，
                           pstFeature 具体结构体内容参考 MV_XML_FEATURE_x
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_XML_GetNodeFeature
 *  @brief      Get current node feature
 *  @param       handle                 [IN]          Handle
 *  @param       pstNode                [IN]          Root node information structure
 *  @param       pstFeature             [OUT]         Current node feature structure
                           Details of pstFeature refer to MV_XML_FEATURE_x
 *  @return Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_XML_GetNodeFeature(IN void* handle, IN MV_XML_NODE_FEATURE* pstNode, IN OUT void* pstFeature);

/***********************************************************************
 *  @fn         MV_XML_UpdateNodeFeature
 *  @brief      更新节点
 *  @param       handle                 [IN]          句柄
 *  @param       enType                 [IN]          节点类型
 *  @param       pstFeature             [OUT]         当前节点属性结构体
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_XML_UpdateNodeFeature
 *  @brief      Update node
 *  @param       handle                 [IN]          Handle
 *  @param       enType                 [IN]          Node type
 *  @param       pstFeature             [OUT]         Current node feature structure
 *  @return Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_XML_UpdateNodeFeature(IN void* handle, IN enum MV_XML_InterfaceType enType, IN void* pstFeature);

// 有节点需要更新时的回调函数
// 当调用MV_XML_UpdateNodeFeature接口更新节点属性时，注册的回调函数cbUpdate会在pstNodesList中返回与之相关联的节点
/***********************************************************************
 *  @fn         MV_XML_RegisterUpdateCallBack
 *  @brief      注册更新回调
 *  @param       handle                 [IN]          句柄
 *  @param       cbUpdate               [IN]          回调函数指针
 *  @param       pUser                  [IN]          用户自定义变量
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_XML_RegisterUpdateCallBack
 *  @brief      Register update callback
 *  @param       handle                 [IN]          Handle
 *  @param       cbUpdate               [IN]          Callback function pointer
 *  @param       pUser                  [IN]          User defined variable
 *  @return Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_XML_RegisterUpdateCallBack(IN void* handle, 
                                                           IN void(__stdcall* cbUpdate)(enum MV_XML_InterfaceType enType, void* pstFeature, MV_XML_NODES_LIST* pstNodesList, void* pUser),
                                                           IN void* pUser);




/************************************************************************/
/* 附加接口                                   							*/
/* Additional interface                                                 */
/************************************************************************/
/************************************************************************
 *  @fn     MV_CC_SaveImageEx2
 *  @brief  保存图片，支持Bmp和Jpeg.编码质量在50-99之前
 *  @param  handle                 [IN]           句柄地址
 *  @param  pSaveParam             [IN][OUT]          保存图片参数结构体
                       pData;              // [IN]     输入数据缓存
                       nDataLen;           // [IN]     输入数据大小
                       enPixelType;        // [IN]     输入数据的像素格式
                       nWidth;             // [IN]     图像宽
                       nHeight;            // [IN]     图像高
                       pImageBuffer;       // [OUT]    输出图片缓存
                       nImageLen;          // [OUT]    输出图片大小
                       nBufferSize;        // [IN]     提供的输出缓冲区大小
                       enImageType;        // [IN]     输出图片格式
                       nJpgQuality;        // [IN]     编码质量, (50-99]
                       iMethodValue        // [IN]     Bayer格式转为RGB24的插值方法
                       nReserved[4];
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_CC_SaveImageEx2
 *  @brief  Save image, support Bmp and Jpeg. Encoding quality, (50-99]
 *  @param  handle                 [IN]           Handle
 *  @param  pSaveParam             [IN][OUT]           Save image parameters structure
                       pData;              // [IN]     Input data buffer
                       nDataLen;           // [IN]     Input data size
                       enPixelType;        // [IN]     Pixel format of input data
                       nWidth;             // [IN]     Image width
                       nHeight;            // [IN]     Image height
                       pImageBuffer;       // [OUT]    Output image buffer
                       nImageLen;          // [OUT]    Output image size
                       nBufferSize;        // [IN]     Output buffer size provided
                       enImageType;        // [IN]     Output image format
                       nJpgQuality;        // [IN]     Encoding quality, (50-99]
                       iMethodValue        // [IN]     Interpolation method of convert Bayer to RGB24
                       nReserved[4];
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SaveImageEx2(IN void* handle, MV_SAVE_IMAGE_PARAM_EX* pSaveParam);

/************************************************************************
 *  @fn     MV_CC_ConvertPixelType
 *  @brief  像素格式转换
 *  @param  pstCvtParam             [IN][OUT]          保存图片参数结构体
                     unsigned short         nWidth;             // [IN]     图像宽
                     unsigned short         nHeight;            // [IN]     图像高
                     enum MvGvspPixelType   enSrcPixelType;     // [IN]     源像素格式
                     unsigned char*         pSrcData;           // [IN]     输入数据缓存
                     unsigned int           nSrcDataLen;        // [IN]     输入数据大小
                     enum MvGvspPixelType   enDstPixelType;     // [IN]     目标像素格式
                     unsigned char*         pDstBuffer;         // [OUT]    输出数据缓存
                     unsigned int           nDstLen;            // [OUT]    输出数据大小
                     unsigned int           nDstBufferSize;     // [IN]     提供的输出缓冲区大小
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_CC_ConvertPixelType
 *  @brief  Pixel format conversion
 *  @param  pstCvtParam             [IN][OUT]          Save image parameter structure
                     unsigned short         nWidth;             // [IN]     Width
                     unsigned short         nHeight;            // [IN]     Height
                     enum MvGvspPixelType   enSrcPixelType;     // [IN]     Source pixel format
                     unsigned char*         pSrcData;           // [IN]     Input data buffer
                     unsigned int           nSrcDataLen;        // [IN]     Input data size
                     enum MvGvspPixelType   enDstPixelType;     // [IN]     Destination pixel format
                     unsigned char*         pDstBuffer;         // [OUT]    Output data buffer
                     unsigned int           nDstLen;            // [OUT]    Output data size
                     unsigned int           nDstBufferSize;     // [IN]     Provided output buffer size
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_ConvertPixelType(IN void* handle, IN OUT MV_CC_PIXEL_CONVERT_PARAM* pstCvtParam);

/************************************************************************
 *  @fn     MV_CC_SetBayerCvtQuality
 *  @brief  插值算法类型设置
 *  @param  BayerCvtQuality             [IN]          Bayer的插值方法  0-最近邻 1-双线性 2-Hamilton
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_CC_SetBayerCvtQuality
 *  @brief  Interpolation algorithm type setting
 *  @param  BayerCvtQuality             [IN]          Bayer interpolation method  0-nearest neighbour 1-bilinearity 2-Hamilton
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetBayerCvtQuality(IN void* handle, IN unsigned int BayerCvtQuality);

/************************************************************************
 *  @fn     MV_CC_GetTlProxy
 *  @brief  获取GenICam代理
 *  @param  handle                 [IN]           句柄地址
 *  @return GenICam代理类指针 ，正常返回值非NULL；异常返回NULL
 
 *  @fn     MV_CC_GetTlProxy
 *  @brief  Get GenICam proxy
 *  @param  handle                 [IN]           Handle address
 *  @return GenICam proxy pointer, normal, return non-NULL; exception, return NULL
 ************************************************************************/
MV_CAMCTRL_API void* __stdcall MV_CC_GetTlProxy(IN void* handle);


/************************************************************************
 *  @fn     MV_CC_FeatureSave
 *  @brief  保存相机属性
 *  @param  handle                [IN]           句柄地址
 *  @param  pFileName             [IN]          属性文件名
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_CC_FeatureSave
 *  @brief  Save camera feature
 *  @param  handle                [IN]           Handle
 *  @param  pFileName             [IN]          File name
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_FeatureSave(IN void* handle, IN const char* pFileName);

/************************************************************************
 *  @fn     MV_CC_FeatureLoad
 *  @brief  导入相机属性
 *  @param  handle                [IN]           句柄地址
 *  @param  pFileName             [IN]          属性文件名
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_CC_FeatureLoad
 *  @brief  Load camera feature
 *  @param  handle                [IN]           Handle
 *  @param  pFileName             [IN]          File name
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_FeatureLoad(IN void* handle, IN const char* pFileName);


/************************************************************************
 *  @fn     MV_CC_FileAccessRead
 *  @brief  从相机读取文件
 *  @param  handle                [IN]           句柄地址
 *  @param  pstFileAccess         [IN]           文件存取结构体
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_CC_FileAccessRead
 *  @brief  Read the file from the camera
 *  @param  handle                [IN]           Handle
 *  @param  pstFileAccess         [IN]           File access structure
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_FileAccessRead(IN void* handle, IN MV_CC_FILE_ACCESS * pstFileAccess);

/************************************************************************
 *  @fn     MV_CC_FileAccessWrite
 *  @brief  将文件写入相机
 *  @param  handle                [IN]           句柄地址
 *  @param  pstFileAccess         [IN]           文件存取结构体
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_CC_FileAccessWrite
 *  @brief  Write the file to camera
 *  @param  handle                [IN]           Handle
 *  @param  pstFileAccess         [IN]           File access structure
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_FileAccessWrite(IN void* handle, IN MV_CC_FILE_ACCESS * pstFileAccess);

/************************************************************************
 *  @fn     MV_CC_GetFileAccessProgress
 *  @brief  获取文件存取的进度
 *  @param  handle                  [IN]           句柄地址
 *  @param  pstFileAccessProgress   [IN]           进度内容
 *  @return 成功，返回MV_OK；错误，返回错误码 （当前文件存取的状态）
 
 *  @fn     MV_CC_GetFileAccessProgress
 *  @brief  Get File Access Progress 
 *  @param  handle                  [IN]           Handle
 *  @param  pstFileAccessProgress   [IN]           File access Progress
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetFileAccessProgress(IN void* handle, OUT MV_CC_FILE_ACCESS_PROGRESS * pstFileAccessProgress);

/************************************************************************
 *  @fn     MV_CC_StartRecord
 *  @brief  开始录像
 *  @param  handle                [IN]           句柄地址
 *  @param  pstRecordParam         [IN]          录像参数结构体
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_CC_StartRecord
 *  @brief  Start Record
 *  @param  handle                [IN]           Handle
 *  @param  pstRecordParam         [IN]          Record param structure
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_StartRecord(IN void* handle, IN MV_CC_RECORD_PARAM* pstRecordParam);

/************************************************************************
 *  @fn     MV_CC_InputOneFrame
 *  @brief  输入录像数据
 *  @param  handle                [IN]           句柄地址
 *  @param  pstInputFrameInfo         [IN]       录像数据结构体
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_CC_InputOneFrame
 *  @brief  Input RAW data to Record
 *  @param  handle                [IN]           Handle
 *  @param  pstInputFrameInfo         [IN]       Record data structure
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_InputOneFrame(IN void* handle, IN MV_CC_INPUT_FRAME_INFO * pstInputFrameInfo);

/************************************************************************
 *  @fn     MV_CC_StopRecord
 *  @brief  停止录像
 *  @param  handle                [IN]           句柄地址
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_CC_StopRecord
 *  @brief  Stop Record
 *  @param  handle                [IN]           Handle
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_StopRecord(IN void* handle);

/************************************************************************/
/* 弃用的接口                                 							*/
/* Abandoned interface                                                  */
/************************************************************************/
/***********************************************************************
 *  @fn         MV_CC_GetOneFrame
 *  @brief      获取一帧图像，此函数为查询式获取，每次调用查询内部缓存有
                无数据，有数据则范围数据，无数据返回错误码
                （该接口已弃用，建议改用 MV_CC_GetOneFrameTimeOut接口）
 *  @param       handle                 [IN]          句柄
 *  @param       pData                  [OUT]         图像数据接收指针
 *  @param       nDataSize              [IN]          接收缓存大小
 *  @param       pFrameInfo             [OUT]         图像信息结构体
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_CC_GetOneFrame
 *  @brief      Get one frame data, this function is using query to get data, 
                query whether the internal cache has data, return data if there has, return error code if no data
                (This interface is abandoned, it is recommended to use the MV_CC_GetOneFrameTimeOut)
 *  @param       handle                 [IN]          Handle
 *  @param       pData                  [OUT]         Recevied image data pointer
 *  @param       nDataSize              [IN]          Recevied buffer size
 *  @param       pFrameInfo             [OUT]         Image information structure
 *  @return Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetOneFrame(IN void* handle, IN OUT unsigned char * pData , IN unsigned int nDataSize, IN OUT MV_FRAME_OUT_INFO* pFrameInfo);

/***********************************************************************
 *  @fn         MV_CC_GetOneFrameEx
 *  @brief      获取一帧trunck数据，此函数为查询式获取，每次调用查询内部
                缓存有无数据，有数据则范围数据，无数据返回错误码
                （该接口已弃用，建议改用 MV_CC_GetOneFrameTimeOut接口）
 *  @param       handle                 [IN]          句柄
 *  @param       pData                  [OUT]         图像数据接收指针
 *  @param       nDataSize              [IN]          接收缓存大小
 *  @param       pFrameInfo             [OUT]         图像信息结构体
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_CC_GetOneFrameEx
 *  @brief      Get one frame of trunck data, this function is using query to get data, 
                query whether the internal cache has data, return data if there has, return error code if no data
                (This interface is abandoned, it is recommended to use the MV_CC_GetOneFrameTimeOut)
 *  @param       handle                 [IN]          Handle
 *  @param       pData                  [OUT]         Recevied image data pointer
 *  @param       nDataSize              [IN]          Recevied buffer size
 *  @param       pFrameInfo             [OUT]         Image information structure
 *  @return Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetOneFrameEx(IN void* handle, IN OUT unsigned char * pData , IN unsigned int nDataSize, IN OUT MV_FRAME_OUT_INFO_EX* pFrameInfo);

/***********************************************************************
 *  @fn         MV_CC_RegisterImageCallBack
 *  @brief      注册图像数据回调（该接口已弃用，建议改用 MV_CC_RegisterImageCallBackEx接口）
 *  @param       handle                 [IN]          句柄
 *  @param       cbOutput               [IN]          回调函数指针
 *  @param       pUser                  [IN]          用户自定义变量
 *  @return 成功，返回MV_OK；错误，返回错误码
 
 *  @fn         MV_CC_RegisterImageCallBack
 *  @brief      Register image data callback (This interface is abandoned, it is recommended to use the MV_CC_RegisterImageCallBackEx)
 *  @param       handle                 [IN]          Handle
 *  @param       cbOutput               [IN]          Callback function pointer
 *  @param       pUser                  [IN]          User defined variable
 *  @return Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_RegisterImageCallBack(void* handle, 
                                                         void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO* pFrameInfo, void* pUser),
                                                         void* pUser);

/************************************************************************
 *  @fn     MV_CC_SaveImage
 *  @brief  保存图片（该接口已弃用，建议改用 MV_CC_SaveImageEx接口）
 *  @param  pSaveParam             [IN][OUT]          保存图片参数结构体
                       pData;              // [IN]     输入数据缓存
                       nDataLen;           // [IN]     输入数据大小
                       enPixelType;        // [IN]     输入数据的像素格式
                       nWidth;             // [IN]     图像宽
                       nHeight;            // [IN]     图像高
                       pImageBuffer;       // [OUT]    输出图片缓存
                       nImageLen;          // [OUT]    输出图片大小
                       nBufferSize;        // [IN]     提供的输出缓冲区大小
                       enImageType;        // [IN]     输出图片格式
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_CC_SaveImage
 *  @brief  Save image (This interface is abandoned, it is recommended to use the MV_CC_SaveImageEx)
 *  @param  pSaveParam             [IN][OUT]          Save image parameters structure
                       pData;              // [IN]     Input data buffer
                       nDataLen;           // [IN]     Input data size
                       enPixelType;        // [IN]     Input data pixel format
                       nWidth;             // [IN]     Width
                       nHeight;            // [IN]     Height
                       pImageBuffer;       // [OUT]    Output image buffer
                       nImageLen;          // [OUT]    Output image size
                       nBufferSize;        // [IN]     Provided output buffer size
                       enImageType;        // [IN]     Output image type
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SaveImage(IN OUT MV_SAVE_IMAGE_PARAM* pSaveParam);

/************************************************************************
 *  @fn     MV_GIGE_ForceIp
 *  @brief  强制IP（该接口已弃用，建议改用 MV_GIGE_ForceIpEx接口）
 *  @param  handle：设备句柄
 *  @param  nIP               [IN]      设置的IP
 *  @return 见返回错误码
 
 *  @fn     MV_GIGE_ForceIp
 *  @brief  Force IP (This interface is abandoned, it is recommended to use the MV_GIGE_ForceIpEx)
 *  @param  handle Handle
 *  @param  nIP               [IN]      IP to set
 *  @return Refer to error code
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_ForceIp(IN void* handle, unsigned int nIP);

/************************************************************************
 *  @fn     MV_CC_RegisterEventCallBack
 *  @brief  注册事件回调（该接口已弃用，建议改用 MV_CC_RegisterEventCallBackEx接口）
 *  @param  handle：设备句柄
 *  @param  cbEvent           [IN]      事件回调函数指针
 *  @param  pUser             [IN]      用户自定义变量
 *  @return 见返回错误码
 
 *  @fn     MV_CC_RegisterEventCallBack
 *  @brief  Register event callback (this interface has been deprecated and is recommended to be converted to the MV_CC_RegisterEventCallBackEx interface)
 *  @param  handle：设备句柄
 *  @param  cbEvent           [IN]      event callback pointer
 *  @param  pUser             [IN]      User defined value
 *  @return 见返回错误码
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_RegisterEventCallBack(void* handle, 
                                                         void(__stdcall* cbEvent)(unsigned int nExternalEventId, void* pUser),
                                                         void* pUser);

/************************************************************************
 *  @fn     MV_CC_SaveImageEx
 *  @brief  保存图片，支持Bmp和Jpeg.编码质量在50-99之前 （该接口已弃用，建议改用 MV_CC_SaveImageEx2接口）
 *  @param  pSaveParam             [IN][OUT]          保存图片参数结构体
                       pData;              // [IN]     输入数据缓存
                       nDataLen;           // [IN]     输入数据大小
                       enPixelType;        // [IN]     输入数据的像素格式
                       nWidth;             // [IN]     图像宽
                       nHeight;            // [IN]     图像高
                       pImageBuffer;       // [OUT]    输出图片缓存
                       nImageLen;          // [OUT]    输出图片大小
                       nBufferSize;        // [IN]     提供的输出缓冲区大小
                       enImageType;        // [IN]     输出图片格式
                       nJpgQuality;        // [IN]     编码质量, (50-99]
                       nReserved[4];
 *  @return 成功，返回MV_OK；错误，返回错误码 
 
 *  @fn     MV_CC_SaveImageEx
 *  @brief  Save image, support Bmp and Jpeg. Encoding quality, (50-99]
 *  @param  pSaveParam             [IN][OUT]           Save image parameters structure
                       pData;              // [IN]     Input data buffer
                       nDataLen;           // [IN]     Input data size
                       enPixelType;        // [IN]     Pixel format of input data
                       nWidth;             // [IN]     Image width
                       nHeight;            // [IN]     Image height
                       pImageBuffer;       // [OUT]    Output image buffer
                       nImageLen;          // [OUT]    Output image size
                       nBufferSize;        // [IN]     Output buffer size provided
                       enImageType;        // [IN]     Output image format
                       nJpgQuality;        // [IN]     Encoding quality, (50-99]
                       nReserved[4];
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SaveImageEx(IN OUT MV_SAVE_IMAGE_PARAM_EX* pSaveParam);


#ifdef __cplusplus
}
#endif 

#endif //_MV_CAMERA_CTRL_H_
