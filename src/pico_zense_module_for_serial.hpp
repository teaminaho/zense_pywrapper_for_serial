#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <thread>
#include "Vzense_api2.h"


#define MAX_DEVICECOUNT 10
namespace zense{
  class PicoZenseModuleForSerial
  {
    public:
      PicoZenseModuleForSerial(uint32_t sensor_idx_);
      ~PicoZenseModuleForSerial();
      void closeDevice();
      std::string getSerialNumber();
      uint32_t getDeviceCount();     
    private:
      PsDeviceInfo* pDeviceListInfo;
      PsDeviceHandle deviceHandle;
      uint32_t sessionIndex;

      std::string serialNumber_;
      uint32_t device_idx_;
      uint32_t deviceCount_;
  };
}

