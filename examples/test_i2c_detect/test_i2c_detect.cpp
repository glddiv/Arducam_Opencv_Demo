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

#if 0
    printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");
    for (int i = 0; i < 128; i+=16) {
        printf("%02x: ", i);
        uint32_t value = 0;
        for (int j = 0; j < 16; j++) {
            int ret = ArduCam_readReg_8_8(cameraHandle, (i + j) << 1, 0x00, &value);

            if (ret)
                printf("-- ");
            else
                printf("%02x ", i+j);
        }
        printf("\n");
    }
#else
    printf("     0  2  4  6  8  a  c  e\n");
    for (int i = 0; i < 256; i+=16) {
        printf("%02x: ", i);
        uint32_t value = 0;
        for (int j = 0; j < 16; j+=2) {
            int ret = ArduCam_readReg_8_8(cameraHandle, i + j, 0x00, &value);

            if (ret)
                printf("-- ");
            else
                printf("%02x ", i+j);
        }
        printf("\n");
    }
#endif
    return 0;
}
