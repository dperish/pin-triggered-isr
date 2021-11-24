#include "TouchPad.h"

void TouchPad::init()
{
    calibrate();
    reset();
    //disableAutoCalibration();
}

uint8_t TouchPad::getChipId() {
    Wire.beginTransmission(TOUCHPAD_I2C_ADDRESS);
    Wire.write(0);
    Wire.endTransmission();

    Wire.requestFrom(TOUCHPAD_I2C_ADDRESS, 1);
    auto chipId = Wire.read();

    return chipId;
}

uint8_t TouchPad::getFirmwareVersion() {
    Wire.beginTransmission(TOUCHPAD_I2C_ADDRESS);
    Wire.write(1);
    Wire.endTransmission();

    Wire.requestFrom(TOUCHPAD_I2C_ADDRESS, 1);
    auto chipId = Wire.read();

    return chipId;
}

uint8_t TouchPad::getDetectionStatus() {
    Wire.beginTransmission(TOUCHPAD_I2C_ADDRESS);
    Wire.write(2);
    Wire.endTransmission();

    Wire.requestFrom(TOUCHPAD_I2C_ADDRESS, 1);
    auto result = Wire.read();

    return result;
}

/** Sets the number of 8 ms intervals between key
    measurements. Longer intervals between measurements yield a lower power consumption but
    at the expense of a slower response to touch */
uint8_t TouchPad::setLowPowerMode(uint8_t intervals) {
    Wire.beginTransmission(TOUCHPAD_I2C_ADDRESS);
    Wire.write(54);
    Wire.write(intervals);
    Wire.endTransmission();

    Wire.requestFrom(TOUCHPAD_I2C_ADDRESS, 1);
    auto chipId = Wire.read();

    return chipId;
}

void TouchPad::calibrate()
{
    Wire.beginTransmission(TOUCHPAD_I2C_ADDRESS);
    Wire.write(TOUCHPAD_REGISTER_CALIBRATE);
    Wire.write(TOUCHPAD_NONZERO_VALUE);
    Wire.endTransmission();
    delay(1000);
}

void TouchPad::reset()
{
    Wire.beginTransmission(TOUCHPAD_I2C_ADDRESS);
    Wire.write(TOUCHPAD_REGISTER_RESET);
    Wire.write(TOUCHPAD_NONZERO_VALUE);
    Wire.endTransmission();

    delay(1000);
    Wire.begin();
    delay(1000);
}

/** Sets Max On Duration to zero, effectively disabling immediate/auto calibration */
void TouchPad::disableAutoCalibration() {
    Wire.beginTransmission(TOUCHPAD_I2C_ADDRESS);
    Wire.write(TOUCHPAD_REGISTER_MAX_ON_DURATION);
    Wire.write(0);
    Wire.endTransmission();
    delay(1000);
}

/** Reads the active key being pushed */
int TouchPad::readActiveKey()
{
    int keyAddress = readActiveAddress();

    int keyValue = 0;
    for (int i = keyAddress; i > 0; i = i >> 1)
    {
        keyValue++;
    }

    return keyValue;
}

int TouchPad::readActiveAddress()
{
    int isTouching = 0;
    int keyNumber = 0;

    Wire.beginTransmission(TOUCHPAD_I2C_ADDRESS);
    Wire.write(TOUCHPAD_REGISTER_DETECTION);
    Wire.endTransmission();
    Wire.requestFrom(TOUCHPAD_I2C_ADDRESS, 1);
    isTouching = Wire.read();

    Wire.beginTransmission(TOUCHPAD_I2C_ADDRESS);
    Wire.write(TOUCHPAD_REGISTER_KEY);
    Wire.endTransmission();
    Wire.requestFrom(TOUCHPAD_I2C_ADDRESS, 1);
    keyNumber = Wire.read();

    if (isTouching == 1) {
        return keyNumber;
    }

    return -1;
}