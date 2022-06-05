cmake_minimum_required(VERSION 3.19)
project(hikvision_camera_tool)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_BUILD_TYPE RELEASE)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPATH=\"\\\"${PROJECT_SOURCE_DIR}\\\"\"")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D${CMAKE_SYSTEM_NAME}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
SET(BIN_NAME "run")
SET(HIKVISION_CAMERA_DIR "${PROJECT_SOURCE_DIR}/camera/hikvision") # 设置相机SDK工具包目录
SET(YAML_CPP_LIBRARIES /usr/local/lib/libyaml-cpp.so) # 设置yaml-cpp库

add_compile_definitions(PROJECT_DIR="${PROJECT_SOURCE_DIR}")


FIND_PROGRAM(CCACHE_FOUND ccache) # ccache编译器缓存
IF(CCACHE_FOUND)
    SET_PROPERTY(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    SET_PROPERTY(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
    MESSAGE("< Use ccache for compiler >")
ENDIF()


FIND_PACKAGE(OpenCV 4 REQUIRED) # 数字根据实际使用opencv版本更改,例如opencv3.X就改为3，opencv4.X就改为4

# 指定相机动态链接库所在路径
LINK_DIRECTORIES(${HIKVISION_CAMERA_DIR}/64)

# 指定相机库目录
INCLUDE_DIRECTORIES(${HIKVISION_CAMERA_DIR}/include)
INCLUDE_DIRECTORIES(${HIKVISION_CAMERA_DIR}/tool/include)


# 相机拓展工具文件
FILE(GLOB_RECURSE sourcefiles "${HIKVISION_CAMERA_DIR}/src/*.cpp" "${HIKVISION_CAMERA_DIR}/tool/src/*.cpp")
add_executable(${BIN_NAME}  main.cpp ${sourcefiles})

# 链接到目标
TARGET_LINK_LIBRARIES(${BIN_NAME} ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(${BIN_NAME} MvCameraControl)
TARGET_LINK_LIBRARIES(${BIN_NAME} ${YAML_CPP_LIBRARIES})


# 设置配置文件夹的绝对路径
set(HIK_CONFIG_FILE_PATH ${PROJECT_SOURCE_DIR}/camera/hikvision/config) # 设置相机配置目录路径
target_compile_definitions(${BIN_NAME} PRIVATE "HIK_CONFIG_FILE_PATH=\"${HIK_CONFIG_FILE_PATH}\"")

# 设置相机标定相关的配置文件路径
set(HIK_CALI_FILE_PATH ${PROJECT_SOURCE_DIR}/camera/hikvision/config/cameraCaliData)
target_compile_definitions(${BIN_NAME} PRIVATE "HIK_CALI_FILE_PATH=\"${HIK_CALI_FILE_PATH}\"")