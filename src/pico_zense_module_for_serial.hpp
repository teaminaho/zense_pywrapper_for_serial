#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include "PicoZense_api.h"

#define MAX_DEVICECOUNT 10
namespace zense{
  class PicoZenseModuleForSerial
  {
    public:
      PicoZenseModuleForSerial(int32_t sensor_idx_);
      ~PicoZenseModuleForSerial();
      void closeDevice();
      std::string getSerialNumber();
      int32_t getDeviceCount();     
    private:
      std::string serialNumber_;
      int32_t device_idx_;
      int32_t deviceCount_;
  };

}

