#ifndef _TOUCHPAD_H
#define _TOUCHPAD_H

#include <Arduino.h>
#include <Wire.h>

#define TOUCHPAD_I2C_ADDRESS                0x1B

#define TOUCHPAD_REGISTER_MAX_ON_DURATION   0x37
#define TOUCHPAD_REGISTER_CALIBRATE         0x38
#define TOUCHPAD_REGISTER_RESET             0x39
#define TOUCHPAD_REGISTER_DETECTION         0x02
#define TOUCHPAD_REGISTER_KEY               0x03

#define TOUCHPAD_NONZERO_VALUE              0xFF

/** Wrapper library for the Atmel AT42QT1070.
 * 
 * Library is designed to work by polling, to play nice with
 * an ESP8266 where the change signal (pin 5) is NOT tied to
 * an interruptable pin on the host device
 */
class TouchPad {
    public:
        TouchPad() {};
        
        void init();
        void calibrate();
        void disableAutoCalibration();
        void reset();
        uint8_t getChipId();


        int readActiveKey();
        int readActiveAddress();
    private:
  
};

#endif