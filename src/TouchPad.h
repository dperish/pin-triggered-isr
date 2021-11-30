#ifndef _TOUCHPAD_H
#define _TOUCHPAD_H

#include <Arduino.h>
#include <Wire.h>

#define TOUCHPAD_I2C_ADDRESS 0x1B

#define TOUCHPAD_REGISTER_CHIPID 0x00
#define TOUCHPAD_REGISTER_FIRMWARE_VERSION 0x01
#define TOUCHPAD_REGISTER_DETECTION 0x02
#define TOUCHPAD_REGISTER_KEY 0x03
#define TOUCHPAD_REGISTER_LPMODE 0x36
#define TOUCHPAD_REGISTER_MAX_ON_DURATION 0x37
#define TOUCHPAD_REGISTER_CALIBRATE 0x38
#define TOUCHPAD_REGISTER_RESET 0x39

#define TOUCHPAD_NONZERO_VALUE 0xFF

/** Wrapper library for the Atmel AT42QT1070.
 * 
 * Library is designed to work by polling, to play nice with
 * an ESP8266 where the change signal (pin 5) is NOT tied to
 * an interruptable pin on the host device
 */
class TouchPad
{
public:
    TouchPad(){};

    void init();
    // void init(int sda, int scl, int isrPin, std::function<void(int keyAddress)> callback);
    void calibrate();
    void disableAutoCalibration();
    void reset();

    uint8_t getChipId();
    uint8_t getFirmwareVersion();
    uint8_t getDetectionStatus();

    uint8_t setLowPowerMode(uint8_t intervals);

    int readActiveKey();
    int readActiveAddress();

    void keyPress(int keyAddress);

private:
    // std::function<void(int)> _onKeyPress;
};

#endif