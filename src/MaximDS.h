//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//!  @file MaximDS.h
//!  @brief MaximDS Controller class definition
//!
//!  @author Nate Taylor

//!  Contact: nate@rtelectronix.com
//!  @copyright (C) 2020  Nate Taylor - All Rights Reserved.
//
//      |-----------------------------------------------------------------------------------------|
//      |                                                                                         |
//      |                    MMMMMMMMMMMMMMMMMMMMMM   NNNNNNNNNNNNNNNNNN                          |
//      |                    MMMMMMMMMMMMMMMMMMMMMM   NNNNNNNNNNNNNNNNNN                          |
//      |                   MMMMMMMMM    MMMMMMMMMM       NNNNNMNNN                               |
//      |                   MMMMMMMM:    MMMMMMMMMM       NNNNNNNN                                |
//      |                  MMMMMMMMMMMMMMMMMMMMMMM       NNNNNNNNN                                |
//      |                 MMMMMMMMMMMMMMMMMMMMMM         NNNNNNNN                                 |
//      |                 MMMMMMMM     MMMMMMM          NNNNNNNN                                  |
//      |                MMMMMMMMM    MMMMMMMM         NNNNNNNNN                                  |
//      |                MMMMMMMM     MMMMMMM          NNNNNNNN                                   |
//      |               MMMMMMMM     MMMMMMM          NNNNNNNNN                                   |
//      |                           MMMMMMMM        NNNNNNNNNN                                    |
//      |                          MMMMMMMMM       NNNNNNNNNNN                                    |
//      |                          MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM                |
//      |                        MMMMMMM      E L E C T R O N I X         MMMMMM                  |
//      |                         MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM                    |
//      |                                                                                         |
//      |-----------------------------------------------------------------------------------------|
//
//      |-----------------------------------------------------------------------------------------|
//      |                                                                                         |
//      |      [MIT License]                                                                      |
//      |                                                                                         |
//      |      Copyright (c) 2020 Nathaniel Taylor                                                |
//      |                                                                                         |
//      |      Permission is hereby granted, free of charge, to any person obtaining a copy       |
//      |      of this software and associated documentation files (the "Software"), to deal      |
//      |      in the Software without restriction, including without limitation the rights       |
//      |      to use, copy, modify, merge, publish, distribute, sublicense, and/or sell          |
//      |      copies of the Software, and to permit persons to whom the Software is              |
//      |      furnished to do so, subject to the following conditions:                           |
//      |                                                                                         |
//      |      The above copyright notice and this permission notice shall be included in all     |
//      |      copies or substantial portions of the Software.                                    |
//      |                                                                                         |
//      |      THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR         |
//      |      IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,           |
//      |      FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE        |
//      |      AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER             |
//      |      LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,      |
//      |      OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE      |
//      |      SOFTWARE.                                                                          |
//      |                                                                                         |
//      |-----------------------------------------------------------------------------------------|
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef _MAXIM_DS_H_
#define _MAXIM_DS_H_

#include <Arduino.h>
#include <Wire.h>

namespace MaximDS
{
    /**
     * @brief Class for controlling a MaximDS digital potentiomer (DS1881 or DS1882)
     */
    class Controller
    {
    public:
        /**
         * @brief Number of Potentiometer Wiper Positions 
         */
        enum PotentiometerMode : uint8_t
        {
            PotentiometerPositions63 = 0x0,
            PotentiometerPositions33 = 0x1
        };

        /**
         * @brief Construct a new Controller object using the default Wire object
         * 
         * @param address The 3 bit pin-programmed slave address
         */
        Controller(uint8_t address) : Controller(address, Wire){};

        /**
         * @brief Construct a new Controller object
         * 
         * @param address The 3 bit pin-programmed slave address
         * @param i2cObj A reference to the TwoWire object for transmission
         */
        Controller(uint8_t address, TwoWire &i2cObj) :  i2c(i2cObj), slaveAddress(GetSlaveAddress(address)){};

        /**
         * @brief Initialize the controller
         * 
         * @param mode The PotentiometerMode to use (number of wiper positions)
         */
        void begin(PotentiometerMode mode = PotentiometerPositions33);

        /**
         * @brief Set the configuration register
         * 
         * @param mode The PotentiometerMode to use (number of wiper positions)
         * @param enableZeroCross Set to false to disable the zero-crossing detector
         * @param enableNVM Set to true to enable non-volatile wiper setting storage
         */
        void configure(PotentiometerMode mode, bool enableZeroCross = true, bool enableNVM = false);

        /**
         * @brief Sets the value of Potentiomer 0
         * 
         * @param value The 6 bit wiper posistion (0 == Fully On, 33 or 63 == MUTE)
         */
        void writePot0(uint8_t value);

        /**
         * @brief Sets the value of Potentiomer 1
         * 
         * @param value The 6 bit wiper posistion (0 == Fully On, 33 or 63 == MUTE)
         */
        void writePot1(uint8_t value);

        /**
         * @brief Sets the value of both potentiometers  (0 == Fully On, 33 or 63 == MUTE)
         * 
         * @param pot0 The 6 bit wiper posistion for Potentiomer 0
         * @param pot1 The 6 bit wiper posistion for Potentiomer 1
         */
        void writePots(uint8_t pot0, uint8_t pot1);

    protected:
        /**
         * @brief Bit Position for PotentiometerMode configuration
         */
        static constexpr uint8_t PotentiometerModePosition = 0x0;

        /**
         * @brief Get the configuration value for the supplied PotentiometerMode
         * 
         * @param mode The PotentiometerMode (number of wiper positions)
         * @return constexpr uint8_t The 6 bit configruation setting
         */
        static inline constexpr uint8_t PotentiometerModeValue(PotentiometerMode mode)
        {
            return (static_cast<uint8_t>(mode) << PotentiometerModePosition);
        }

        /**
         * @brief Bit Position for zero-crossing detection configuration
         */
        static constexpr uint8_t ZeroCrossingEnablePosition = 0x1;

        /**
         * @brief Get the configuration value for enabled/disabled zero crossing detector
         * 
         * @param enable True to enable zero-crossing detection (false to disable)
         * @return constexpr uint8_t The 6 bit configruation setting
         */
        static inline constexpr uint8_t ZeroCrossingEnableValue(bool enable)
        {
            return enable ? (1 << ZeroCrossingEnablePosition) : 0x0;
        }

        /**
         * @brief Bit Position for non-volatile memory configuration
         */
        static constexpr uint8_t NVMEnablePosition = 0x2;

        /**
         * @brief Get the configuration value for enabled/disabled non-volatile memory storage
         * 
         * @param enable True to enable non-volatile memory (false to disable)
         * @return constexpr uint8_t The 6 bit configruation setting
         */
        static inline constexpr uint8_t NVMEnableValue(bool enable)
        {
            return enable ? 0x0 : (1 << NVMEnablePosition);
        }

        /**
         * @brief Base address for MaximDS I2C slaves
         */
        static constexpr uint8_t SlaveAddressBase = 0x28;

        /**
         * @brief Generate the slave address for a MaximDS device
         * 
         * @param value The 3 bit pin-programmed address
         * @return constexpr uint8_t The 7 bit I2C slave address
         */
        static inline constexpr uint8_t GetSlaveAddress(uint8_t value)
        {
            return (SlaveAddressBase | (value & 0x7));
        }

        /**
         * @brief The base address for the configuration register
         */
        static constexpr uint8_t ConfigureRegisterBase = 0x80;

        /**
         * @brief Reference to the TwoWire object that controls data transmission
         */
        TwoWire &i2c;

        /**
         * @brief The 7-bit I2C Slave address for the device
         */
        const uint8_t slaveAddress;

        /**
         * @brief Get the 8-bit transmission byte for the supplied pot value
         * 
         * @param index Set to false for Pot 0, true for Pot 1
         * @param value The 6 bit potentiometer settings (0 == No Attenuation)
         * @return constexpr uint8_t The 8 bit pot setting byte
         */
        inline constexpr uint8_t GetPotValueByte(bool index, uint8_t value)
        {
            return index ? (0x40 | (value & 0x3F)) : (value & 0x3F);
        }

        /**
         * @brief Start a TwoWire transmission
         */
        void beginTransmission()
        {
            i2c.beginTransmission(slaveAddress);
        }

        /**
         * @brief Transmit a byte over TwoWire
         * 
         * @param data The data byte to transmit
         */
        void transmitByte(uint8_t data)
        {
            i2c.write(data);
        }

        /**
         * @brief End a TwoWrite transmission
         */
        void endTransmission()
        {
            i2c.endTransmission();
        }
    };
} // namespace MaximDS

#endif