#pragma once
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "Vzense_api2.h"

struct CameraParameter {
  int image_width;
  int image_height;
  float fx;  //!< Focal length x (pixel)
  float fy;  //!< Focal length y (pixel)
  float cx;  //!< Principal point x (pixel)
  float cy;  //!< Principal point y (pixel)
  float p1;  //!< Tangential distortion coefficient
  float p2;  //!< Tangential distortion coefficient
  float k1;  //!< Radial distortion coefficient, 1st-order
  float k2;  //!< Radial distortion coefficient, 2nd-order
  float k3;  //!< Radial distortion coefficient, 3rd-order
  float k4;  //!< Radial distortion coefficient, 4st-order
  float k5;  //!< Radial distortion coefficient, 5nd-order
  float k6;  //!< Radial distortion coefficient, 6rd-order
};

struct ExtrinsicParameter {
  std::vector<double> rotation;
  std::vector<double> translation;
};

#define MAX_DEVICECOUNT 10
namespace zense {
class PicoZenseModuleForSerial {
 public:
  PicoZenseModuleForSerial(int32_t sensor_idx_);
  ~PicoZenseModuleForSerial();
  void closeDevice();
  void shutdown();

  std::vector<double> getCameraParameter();
  std::vector<std::vector<double>> getExtrinsicParameter();
  std::vector<double> getRGBCameraParameter();
  std::string getSerialNumber();
  uint32_t getDeviceCount();

 private:
  PsDeviceInfo* pDeviceListInfo;
  PsDeviceHandle deviceHandle;
  uint32_t sessionIndex;

  std::string serialNumber_;
  uint32_t deviceIndex_;
  uint32_t deviceCount_;
  CameraParameter camera_param_;
  CameraParameter camera_param_rgb_;
  ExtrinsicParameter extrinsic_param_;
};
}  // namespace zense
