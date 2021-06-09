#include <iostream>

#if defined(__linux__)
#include "ArduCamLib.h"
#include <unistd.h>
#endif


int main(int argc, char const *argv[]) {
    ArduCamHandle cameraHandle;
    ArduCamCfg cameraCfg = {
        .u32CameraType = 0x00,
        .u16Vid = 0x00,                              //Micron Imaging Vendor ID for USB
        .u32Width = 640,
        .u32Height = 480,
        .u8PixelBytes = 1,
        .u8PixelBits = 8,
        .u32I2cAddr = 0x0c,
        .u32Size = 0x00,
        .usbType = 0x00,
        .emI2cMode = I2C_MODE_16_16,
        .emImageFmtMode = FORMAT_MODE_RAW,
        .u32TransLvl = 0x00,
    };
    int ret_val = ArduCam_open(cameraHandle, &cameraCfg, 0);

    if (ret_val != USB_CAMERA_NO_ERROR) {
        printf("Error: 0x%04X\n", ret_val);
        exit(-1);
    }

    uint32_t chipAddr = 0x18;
    uint32_t reg = 0x0103;
    uint32_t value;
    ret_val = ArduCam_readReg_16_32(cameraHandle, chipAddr, reg, &value);
    printf("ret: %d, REG=0x%02X, 0x%04X\n", ret_val, reg, value);

    reg = 0x0401;
    ret_val = ArduCam_readReg_16_32(cameraHandle, chipAddr, reg, &value);
    printf("ret: %d, REG=0x%02X, 0x%04X\n", ret_val, reg, value);

    ArduCam_writeReg_16_32(cameraHandle, chipAddr, 0x400, 0x01);

    reg = 0x0401;
    ret_val = ArduCam_readReg_16_32(cameraHandle, chipAddr, reg, &value);
    printf("ret: %d, REG=0x%02X, 0x%04X\n", ret_val, reg, value);


    ret_val = ArduCam_readReg_32_32(cameraHandle, chipAddr, 0x12345678, &value);
    printf("ret: %d, REG=0x%02X, 0x%04X\n", ret_val, reg, value);

    return 0;
}
