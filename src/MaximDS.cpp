#include "MaximDS.h"

using namespace MaximDS;

void Controller::begin(PotentiometerMode mode /* = PotentiometerPositions33 */)
{
    i2c.begin();
    if (mode != PotentiometerPositions33)
    {
        configure(mode);
    }
}

void Controller::configure(PotentiometerMode mode, bool enableZeroCross /* = true */, bool enableNVM /* = false */)
{
    uint8_t configureRegister = ConfigureRegisterBase;
    configureRegister |= NVMEnableValue(enableNVM);
    configureRegister |= ZeroCrossingEnableValue(enableZeroCross);
    configureRegister |= PotentiometerModeValue(mode);
    beginTransmission();
    transmitByte(configureRegister);
    endTransmission();
}

void Controller::writePot0(uint8_t value)
{
    uint8_t data = GetPotValueByte(false, value);
    beginTransmission();
    transmitByte(data);
    endTransmission();
}

void Controller::writePot1(uint8_t value)
{
    uint8_t data = GetPotValueByte(true, value);
    beginTransmission();
    transmitByte(data);
    endTransmission();
}

void Controller::writePots(uint8_t pot0, uint8_t pot1)
{
    uint8_t data0 = GetPotValueByte(false, pot0);
    uint8_t data1 = GetPotValueByte(true, pot1);
    beginTransmission();
    transmitByte(data0);
    transmitByte(data1);
    endTransmission();
}