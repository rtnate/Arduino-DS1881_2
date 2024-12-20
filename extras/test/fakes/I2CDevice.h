#ifndef TEST_FAKES_I2CDEVICE
#define TEST_FAKES_I2CDEVICE

#include <stdint.h>
#include <Wire.h>
namespace PCA9546A_Fakes {
    /**
     * @brief Fake I2C Device Library
     * 
     */
    class I2CDevice {
    public:
        //Bus result constants
        /**
         * @brief I2C Bus reutrn value on successful transmission.
         */
        static constexpr uint8_t SUCCESS = 0x0;
        /**
         * @brief I2C Bus return value on data overrun (data longer than expected)
         */
        static constexpr uint8_t DATA_TOO_LONG = 0x1;
        /**
         * @brief I2C Bus return value on device NACK on address transmission
         */
        static constexpr uint8_t NACK_ON_ADDRESS = 0x2;
        /**
         * @brief I2C Bus return value on device NACK on data transmission
         */
        static constexpr uint8_t NACK_ON_DATA = 0x3;
        /**
         * @brief I2C Bus return value for all other errors
         */
        static constexpr uint8_t OTHER_ERROR = 0x4;

        /**
         * @brief Standard I2CDevice constructor
         * 
         * @param tw A reference to the TwoWire object that will manage hardware 
         *           transmission.  Defaults to "Wire".
         * @param address The 7-bit I2C device address, defaults to 0x0
         */
        I2CDevice(TwoWire& tw = Wire, uint8_t address = 0x0):
        wire(tw), dev_address(address){};

        /**
         * @brief Get the I2C device address
         * 
         * @return The 7-bit I2C device address 
         */
        inline uint8_t getAddress() const {
        return dev_address;
        }
        
        /**
         * @brief Get the I2C bus return status
         * 
         * @return uint8_t 
         */
        inline uint8_t getStatus() const { 
        return m_status;
        }

        /**
         * @brief Begin a bus transmission.  Call before all calls to write(), 
         *        requestBytes() or read().
         * 
         */
        inline void beginTransmission() {}

        /**
         * @brief Write data to the I2C bus.  Queue's the data, 
         *        actual tranmission occurs with endTransmission()
         * 
         * @param data The data byte to write.
         * @return The number of bytes written (1 on success, 0 on failure)
         */
        inline size_t write(uint8_t data) {
            return wire.write(data);
        }

        /**
         * @brief Write data to the I2C bus.  Queue's the data, 
         *        actual tranmission occurs with endTransmission()
         * 
         * @param data A pointer to the data buffer to write
         * @param size The size of the data buffer in bytes
         * @return The number of bytes written
         */
        inline size_t write(const uint8_t* data, size_t size)  {
            return wire.write(data, size);
        }

        /**
         * @brief The number of data bytes stored in the I2C receive buffer.
         * 
         * @return The number of bytes stored, greather than 0 if bytes are stored.
         */
        inline int available() {
            return wire.available();
        }

        /**
         * @brief Reads a byte from the bus (data is stored in a buffer after 
         *        a call to requestBytes())
         * 
         * @return int The data byte or -1 if the buffer is empty
         */
        inline int read() {
            return wire.read();
        }

        /**
         * @brief Call to end an I2C bus transmission.  
         *        This will transmit data queued by calls to write()
         * 
         * @return The I2C Bus result
         *         0 : success
         *         1 : data too long
         *         2 : NACK on transmit of address
         *         3 : NACK on transmit of data
         *         4 : other
         */
        inline uint8_t endTransmission() {
            m_status = wire.endTransmission();
            return m_status;
        }

        /**
         * @brief Call to end an I2C bus transmission.  
         *        This will transmit data queued by calls to write()
         * 
         * @param sendStop Set to 1 to send stop condition, 0 to not.
         * 
         * @return The I2C Bus result
         *         0 : success
         *         1 : data too long
         *         2 : NACK on transmit of address
         *         3 : NACK on transmit of data
         *         4 : other
         */
        inline uint8_t endTransmission(uint8_t sendStop) {
        m_status = wire.endTransmission(sendStop);
        return m_status;
        }

        /**
         * @brief Call to requiest bytes from the I2C device
         * 
         * @param noBytes The number of bytes to request
         * @return The number of bytes returned and stored in the buffer 
         */
        inline uint8_t requestBytes(uint8_t noBytes) {
            return wire.requestFrom(getAddress(), noBytes);
        }

        /**
         * @brief Get the I2C bus return status
         * 
         * @return 0 : success
         *         1 : data too long
         *         2 : NACK on transmit of address
         *         3 : NACK on transmit of data
         *         4 : other
         */
        inline uint8_t getBusStatus() const { return m_status; };

        /**
         * @brief Prints the I2C bus return status value
         * 
         * @param printable The printable object to print to.  
         *                  Must inherit from Arduino's Print class.  
         *                  Defaults to Serial.
         */
        inline void printBusStatus(Print& printable = Serial) const
        {
            printable.print("Current I2C status : ");
            printable.println(m_status);
        };
        
        /**
         * @brief Get the TwoWire object that is managed by this class.
         * 
         * @return TwoWire& A reference to the TwoWire object
         */
        TwoWire& getWireInstance() const {
            return wire;
        }

        /**
         * @brief Get the Wire Hardware Address object
         * 
         * @return uint16_t 
         */
        uintptr_t getWireHardwareAddress() const {
            TwoWire* ptr = &wire;
            return reinterpret_cast<uintptr_t>(ptr);
        }

        /**
         * @brief Attempts to detect the presence of a device on the bus.
         *        Attempts communication on the bus by sending the device
         *        address.
         * 
         * @return bool True if there is an ACK on address transmission
         */
        inline bool detect() {
            this->wire.beginTransmission(dev_address);
            return (this->wire.endTransmission() == 0);
        }

        protected:
            const uint8_t dev_address; //!< The 7-bit device I2C slave address
            TwoWire& wire; //!< A reference to the TwoWire object that manages hardware transmission
            uint8_t m_status; //!< The stored bus status (set after each transmission)
    };
    /**
     * @brief Simple class designed to be inherited by classes that have 
     *        I2C devices as one of their components.
     */
    class HasI2CDevice {
    public:
        HasI2CDevice(TwoWire& tw = Wire, uint8_t address = 0x0):
            bus(tw, address){};

        /**
         * @brief Get the I2C bus return status
         * 
         * @return 0 : success
         *         1 : data too long
         *         2 : NACK on transmit of address
         *         3 : NACK on transmit of data
         *         4 : other
         */
        uint8_t getBusStatus() const { return bus.getBusStatus(); };

        /**
         * @brief Prints the I2C bus return status value
         * 
         * @param printable The printable object to print to.  
         *                  Must inherit from Arduino's Print class.  
         *                  Defaults to Serial.
         */
        void printBusStatus(Print& printable = Serial) const
        {
            bus.printBusStatus(printable);
        };

        /**
         * @brief Attempts to detect the presence of a device on the bus.
         *        Attempts communication on the bus by sending the device
         *        address.
         * 
         * @return bool True if there is an ACK on address transmission
         */
        inline bool detect() {
            return this->bus.detect();
        }
    protected:
        I2CDevice bus; //!< The I2C Device object this class manages
    };
}

using I2CDevice = PCA9546A_Fakes::I2CDevice;
using HasI2CDevice = PCA9546A_Fakes::HasI2CDevice;

#endif /* TEST_FAKES_I2CDEVICE */
