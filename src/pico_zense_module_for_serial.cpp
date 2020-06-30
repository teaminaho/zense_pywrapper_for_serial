#include "pico_zense_module_for_serial.hpp"

using namespace std;
namespace zense {
PicoZenseModuleForSerial::PicoZenseModuleForSerial(uint32_t sensor_idx_) {
  deviceIndex_ = sensor_idx_;
  PsReturnStatus status;
  status = Ps2_Initialize();
  if (status != PsReturnStatus::PsRetOK) {
    cout << "PsInitialize failed!" << endl;
    exit(EXIT_FAILURE);
  }

GET:
  deviceCount_ = 0;
  status = Ps2_GetDeviceCount(&deviceCount_);
  if (status != PsReturnStatus::PsRetOK) {
    std::cout << "PsGetDeviceCount failed!" << std::endl;
  }
  std::cout << "Get device count: " << deviceCount_ << std::endl;
  if (0 == deviceCount_) {
    this_thread::sleep_for(chrono::seconds(1));
    goto GET;
  }

  pDeviceListInfo = new PsDeviceInfo[deviceCount_];
  status = Ps2_GetDeviceListInfo(pDeviceListInfo, deviceCount_);
  if (status != PsReturnStatus::PsRetOK) {
    cout << "PsGetDeviceCount failed!" << endl;
    exit(EXIT_FAILURE);
  }
  cout << "Detected " << deviceCount_ << " devices." << endl;

  if (deviceCount_ > MAX_DEVICECOUNT) {
    cout << "# of devices exceeds maximum of " << MAX_DEVICECOUNT << endl;
    deviceCount_ = MAX_DEVICECOUNT;
  }
}

PicoZenseModuleForSerial::~PicoZenseModuleForSerial() {
  closeDevice();
}

void PicoZenseModuleForSerial::closeDevice() {
  PsReturnStatus status;
  status = Ps2_StopStream(deviceHandle, sessionIndex);
  status = Ps2_CloseDevice(deviceHandle);
  if (status != PsReturnStatus::PsRetOK) {
    cout << "CloseDevice failed!" << endl;
  } else {
    cout << "Device Closed: " << sessionIndex << endl;
  }
  status = Ps2_Shutdown(); //cause segmentation fault
  cout << "Shutdown : " << status << endl;
}

std::string PicoZenseModuleForSerial::getSerialNumber() {
  PsReturnStatus status;
  deviceHandle = 0;
  std::cout << "sensor_idx_:" << deviceIndex_ << endl;
  std::string uri_string = std::string(pDeviceListInfo[deviceIndex_].uri);
  std::cout << "uri_string :" << uri_string << std::endl;
  status = Ps2_OpenDevice(uri_string.c_str(), &deviceHandle);
  if (status != PsReturnStatus::PsRetOK) {
    std::cout << "PsOpenDevice failed!" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  sessionIndex = 0;

  Ps2_StartStream(deviceHandle, sessionIndex);
  std::cout << "session index :" << sessionIndex << std::endl;

  // get Serial Number
  int32_t lenSerial = 100;
  char buffSerial[lenSerial];
  status = Ps2_GetProperty(deviceHandle, sessionIndex, PsPropertySN_Str,
                           buffSerial, &lenSerial);
  serialNumber_ = buffSerial;
  cout << "SERIAL : " << buffSerial << endl;

  // set Depth Camera Parameter
  PsCameraParameters camera_parameters;
  status = Ps2_GetCameraParameters(deviceHandle, sessionIndex, PsDepthSensor,
                                   &camera_parameters);

  cout << "serial_no = \"" << serialNumber_ << "\"" << endl;
  camera_param_.fx = camera_parameters.fx;
  camera_param_.fy = camera_parameters.fy;
  camera_param_.cx = camera_parameters.cx;
  camera_param_.cy = camera_parameters.cy;
  camera_param_.p1 = camera_parameters.p1;
  camera_param_.p2 = camera_parameters.p2;
  camera_param_.k1 = camera_parameters.k1;
  camera_param_.k2 = camera_parameters.k2;
  camera_param_.k3 = camera_parameters.k3;
  camera_param_.k4 = camera_parameters.k4;
  camera_param_.k5 = camera_parameters.k5;
  camera_param_.k6 = camera_parameters.k6;

  PsCameraParameters camera_parameters_rgb;
  status = Ps2_GetCameraParameters(deviceHandle, sessionIndex, PsRgbSensor,
                                   &camera_parameters_rgb);
  camera_param_rgb_.fx = camera_parameters_rgb.fx;
  camera_param_rgb_.fy = camera_parameters_rgb.fy;
  camera_param_rgb_.cx = camera_parameters_rgb.cx;
  camera_param_rgb_.cy = camera_parameters_rgb.cy;
  camera_param_rgb_.p1 = camera_parameters_rgb.p1;
  camera_param_rgb_.p2 = camera_parameters_rgb.p2;
  camera_param_rgb_.k1 = camera_parameters_rgb.k1;
  camera_param_rgb_.k2 = camera_parameters_rgb.k2;
  camera_param_rgb_.k3 = camera_parameters_rgb.k3;
  camera_param_rgb_.k4 = camera_parameters_rgb.k4;
  camera_param_rgb_.k5 = camera_parameters_rgb.k5;
  camera_param_rgb_.k6 = camera_parameters_rgb.k6;

  PsCameraExtrinsicParameters pCameraExtrinsicParameters;
  Ps2_GetCameraExtrinsicParameters(deviceHandle, sessionIndex,
                                   &pCameraExtrinsicParameters);
  std::vector<double> _rotation(std::begin(pCameraExtrinsicParameters.rotation),
                                std::end(pCameraExtrinsicParameters.rotation));
  std::vector<double> _translation(
      std::begin(pCameraExtrinsicParameters.translation),
      std::end(pCameraExtrinsicParameters.translation));
  extrinsic_param_.rotation = _rotation;
  extrinsic_param_.translation = _translation;

  return serialNumber_;
}

uint32_t PicoZenseModuleForSerial::getDeviceCount() { return deviceCount_; }

std::vector<std::vector<double>> PicoZenseModuleForSerial::getExtrinsicParameter() {
  std::vector<std::vector<double>> extrinsic_parameter_vec;
  extrinsic_parameter_vec.push_back(extrinsic_param_.rotation);
  extrinsic_parameter_vec.push_back(extrinsic_param_.translation);
  return extrinsic_parameter_vec;
}

std::vector<double> PicoZenseModuleForSerial::getCameraParameter() {
  std::vector<double> camera_parameter_vec;
  camera_parameter_vec.push_back(camera_param_.fx);
  camera_parameter_vec.push_back(camera_param_.fy);
  camera_parameter_vec.push_back(camera_param_.cx);
  camera_parameter_vec.push_back(camera_param_.cy);
  camera_parameter_vec.push_back(camera_param_.p1);
  camera_parameter_vec.push_back(camera_param_.p2);
  camera_parameter_vec.push_back(camera_param_.k1);
  camera_parameter_vec.push_back(camera_param_.k2);
  camera_parameter_vec.push_back(camera_param_.k3);
  camera_parameter_vec.push_back(camera_param_.k4);
  camera_parameter_vec.push_back(camera_param_.k5);
  camera_parameter_vec.push_back(camera_param_.k6);
  return camera_parameter_vec;
}

std::vector<double> PicoZenseModuleForSerial::getRGBCameraParameter() {
  std::vector<double> camera_parameter_vec;
  camera_parameter_vec.push_back(camera_param_rgb_.fx);
  camera_parameter_vec.push_back(camera_param_rgb_.fy);
  camera_parameter_vec.push_back(camera_param_rgb_.cx);
  camera_parameter_vec.push_back(camera_param_rgb_.cy);
  camera_parameter_vec.push_back(camera_param_rgb_.p1);
  camera_parameter_vec.push_back(camera_param_rgb_.p2);
  camera_parameter_vec.push_back(camera_param_rgb_.k1);
  camera_parameter_vec.push_back(camera_param_rgb_.k2);
  camera_parameter_vec.push_back(camera_param_rgb_.k3);
  camera_parameter_vec.push_back(camera_param_rgb_.k4);
  camera_parameter_vec.push_back(camera_param_rgb_.k5);
  camera_parameter_vec.push_back(camera_param_rgb_.k6);
  return camera_parameter_vec;
}

}  // namespace zense
