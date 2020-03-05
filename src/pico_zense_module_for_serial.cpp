#include "pico_zense_module_for_serial.hpp"

using namespace std;
namespace zense{
    PicoZenseModuleForSerial::PicoZenseModuleForSerial(int32_t device_idx)
    {
        device_idx_ = device_idx; 
        PsReturnStatus status;
        status = PsInitialize();
        if (status != PsReturnStatus::PsRetOK)
        {
            cout << "PsInitialize failed!" << endl;
            exit(EXIT_FAILURE);
        }

        deviceCount_ = 0;
        status = PsGetDeviceCount(&deviceCount_);
        if (status != PsReturnStatus::PsRetOK)
        {
            cout << "PsGetDeviceCount failed!" << endl;
            exit(EXIT_FAILURE);
        }
        cout << "Detected " << deviceCount_ << " devices." << endl;
        
        if (deviceCount_ > MAX_DEVICECOUNT)
        {
            cout << "# of devices exceeds maximum of " << MAX_DEVICECOUNT << endl;
            deviceCount_ = MAX_DEVICECOUNT;
        }

    }

    PicoZenseModuleForSerial::~PicoZenseModuleForSerial()
    {
        PsReturnStatus status;
        status = PsShutdown();
        cout << "Shutdown : " << status << endl;
    }

    void PicoZenseModuleForSerial::closeDevice()
    {
        PsReturnStatus status;
        status = PsCloseDevice(device_idx_);
    }

    std::string PicoZenseModuleForSerial::getSerialNumber() {
        PsReturnStatus status;
        
        cout << "sensor_idx_:" << device_idx_ << endl;
        status = PsOpenDevice(device_idx_);
        if (status != PsReturnStatus::PsRetOK)
        {
            cout << "PsOpenDevice failed!" << endl;
            exit(EXIT_FAILURE);
        }

        //get Serial Number
        int32_t lenSerial = 100;
        char buffSerial[lenSerial];
        status = PsGetProperty(device_idx_, PsPropertySN_Str, buffSerial, &lenSerial);
        serialNumber_ = buffSerial;
        cout << "SERIAL : " << buffSerial << endl;

        return serialNumber_;
    }

    int32_t PicoZenseModuleForSerial::getDeviceCount() {
        return deviceCount_;
    }

}
