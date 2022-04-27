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

bool Controller::configure(PotentiometerMode mode, bool enableZeroCross /* = true */, bool enableNVM /* = false */)
{
    uint8_t configureRegister = ConfigureRegisterBase;
    configureRegister |= NVMEnableValue(enableNVM);
    configureRegister |= ZeroCrossingEnableValue(enableZeroCross);
    configureRegister |= PotentiometerModeValue(mode);
    beginTransmission();
    transmitByte(configureRegister);
    auto result = endTransmission();
    return (result == 0);
}

uint8_t Controller::writePot0(uint8_t value)
{
    uint8_t data = GetPotValueByte(false, value);
    beginTransmission();
    transmitByte(data);
    return endTransmission();
}

uint8_t Controller::writePot1(uint8_t value)
{
    uint8_t data = GetPotValueByte(true, value);
    beginTransmission();
    transmitByte(data);
    return endTransmission();
}

uint8_t Controller::writePots(uint8_t pot0, uint8_t pot1)
{
    uint8_t data0 = GetPotValueByte(false, pot0);
    uint8_t data1 = GetPotValueByte(true, pot1);
    beginTransmission();
    transmitByte(data0);
    transmitByte(data1);
    return endTransmission();
}