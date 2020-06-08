#include "pico_zense_module_for_serial.hpp"

using namespace std;
namespace zense{
    PicoZenseModuleForSerial::PicoZenseModuleForSerial(uint32_t device_idx)
    {
        device_idx_ = device_idx; 
        PsReturnStatus status;
        status = Ps2_Initialize();
        if (status != PsReturnStatus::PsRetOK)
        {
            cout << "PsInitialize failed!" << endl;
            exit(EXIT_FAILURE);
        }

GET:
        deviceCount_ = 0;
        status = Ps2_GetDeviceCount(&deviceCount_);
        if (status != PsReturnStatus::PsRetOK)
        {
            std::cout << "PsGetDeviceCount failed!" << std::endl;
        }
        std::cout << "Get device count: " << deviceCount_ << std::endl;
        if (0 == deviceCount_)
        {
            this_thread::sleep_for(chrono::seconds(1));
            goto GET;
        }

        pDeviceListInfo = new PsDeviceInfo[deviceCount_];
        status = Ps2_GetDeviceListInfo(pDeviceListInfo, deviceCount_);
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
        status = Ps2_Shutdown();
        cout << "Shutdown : " << status << endl;
    }

    void PicoZenseModuleForSerial::closeDevice()
    {
        PsReturnStatus status;
        status = Ps2_CloseDevice(deviceHandle);
    }

    std::string PicoZenseModuleForSerial::getSerialNumber() {
        PsReturnStatus status;
        deviceHandle = 0;
        std::cout << "sensor_idx_:" << device_idx_ << endl;        
        std::string uri_string = std::string(pDeviceListInfo[0].uri);
        std::cout << "uri_string :" << uri_string << std::endl;
        //status = Ps2_OpenDevice(pDeviceListInfo->uri, &deviceHandle);
        status = Ps2_OpenDevice("/dev/video2", &deviceHandle);
        if (status != PsReturnStatus::PsRetOK)
        {
            std::cout << "PsOpenDevice failed!" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        sessionIndex = 0;
	    Ps2_StartStream(deviceHandle, sessionIndex);
        std::cout << "session index :" << sessionIndex << std::endl;
        
        //get Serial Number
        int32_t lenSerial = 100;
        char buffSerial[lenSerial];
        status = Ps2_GetProperty(deviceHandle, sessionIndex, PsPropertySN_Str, buffSerial, &lenSerial);
        serialNumber_ = buffSerial;
        cout << "SERIAL : " << buffSerial << endl;

        return serialNumber_;
    }

    uint32_t PicoZenseModuleForSerial::getDeviceCount() {
        return deviceCount_;
    }

}
