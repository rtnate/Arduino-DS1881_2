# DS1881_2 Arduino Library


## Basic Usage

### Note on Class Names/Namespace 
The controller class in the source code is MaximDS::Controller.  This is aliased 
to DS1881 or DS1882 in the library header.  For simplicity I will use DS1882 as 
the class name in the documentation, but one can use DS1881 and they are
exactly the same.

## Constructors

### *DS1882(uint8_t address)*

Construct a new Device Controller object using the default Wire instance.

Takes a 3-bit address value corresponding to the state of the hardware pins:


A2   |A1    |A0    |Value
---- | ---- | ---- | ----
L    |L     |L     |0x0
L    |L     |H     |0x1
L    |H     |L     |0x2
L    |H     |H     |0x3
H    |L     |L     |0x4
H    |L     |H     |0x5
H    |H     |L     |0x6
H    |H     |H     |0x7


#### Parameters
* `address` The 3 bit pin-programmed slave address

### *DS1882(uint8_t address,TwoWire & i2cObj)*

Construct a new Device Controller object using the supplied TwoWire instance.

Takes a 3-bit address value corresponding to the state of the hardware pins:


A2   |A1    |A0    |Value
---- | ---- | ---- | ----
L    |L     |L     |0x0
L    |L     |H     |0x1
L    |H     |L     |0x2
L    |H     |H     |0x3
H    |L     |L     |0x4
H    |L     |H     |0x5
H    |H     |L     |0x6
H    |H     |H     |0x7

#### Parameters
* `address` The 3 bit pin-programmed slave address 

* `i2cObj` A reference to the TwoWire instance for transmission

## Public Methods

### *void begin([PotentiometerMode](#Enums) mode)*

Initializes the controller and configures the pot to the mode supplied (33 positions be default).

Should be called in setup().

#### Parameters
* `mode` The PotentiometerMode to use (number of wiper positions) 


### *bool configure(PotentiometerMode mode, bool enableZeroCross, bool enableNVM)*

Set the configuration register of the digital pot.

Use to explicitly set the configuration options, this 
   will transmit these values to the digital pot.

#### Parameters
* `mode` The PotentiometerMode to use (number of wiper positions) 


* `enableZeroCross` Set to false to disable the zero-crossing detector 


* `enableNVM` Set to true to enable non-volatile wiper setting storage 

#### Returns
true on success, false on bus error

### `public uint8_t writePot0(uint8_t value)` {#class_maxim_d_s_1_1_controller_1a204935fe2c5a59a804b76c4b677c9bbf}

Sets the value of Potentiometer 0.

#### Parameters
* `value` The 6 bit wiper position (0 == Fully On, 33 or 63 == MUTE) 





#### Returns
The status code from the Wire interface: 0 .. success 1 .. length to long for buffer 2 .. address send, NACK received 3 .. data send, NACK received 4 .. other twi error (lost bus arbitration, bus error, ..) 5 .. timeout

### `public uint8_t writePot1(uint8_t value)` {#class_maxim_d_s_1_1_controller_1a70e8bcbbb21efb3e273fd4ee1b3ae178}

Sets the value of Potentiometer 1.

#### Parameters
* `value` The 6 bit wiper position (0 == Fully On, 33 or 63 == MUTE) 





#### Returns
The status code from the Wire interface: 0 .. success 1 .. length to long for buffer 2 .. address send, NACK received 3 .. data send, NACK received 4 .. other twi error (lost bus arbitration, bus error, ..) 5 .. timeout

### `public uint8_t writePots(uint8_t pot0,uint8_t pot1)` {#class_maxim_d_s_1_1_controller_1a9f58412ac09b0d34dc9f965340f97d69}

Sets the value of both potentiometers (0 == Fully On, 33 or 63 == MUTE)

#### Parameters
* `pot0` The 6 bit wiper position for Potentiometer 0 


* `pot1` The 6 bit wiper position for Potentiometer 1 





#### Returns
The status code from the Wire interface: 0 .. success 1 .. length to long for buffer 2 .. address send, NACK received 3 .. data send, NACK received 4 .. other twi error (lost bus arbitration, bus error, ..) 5 .. timeout

### `protected TwoWire & i2c` {#class_maxim_d_s_1_1_controller_1a36a82a467a805352314f58fef35a77be}

Reference to the TwoWire object that controls data transmission.



### `protected const uint8_t slaveAddress` {#class_maxim_d_s_1_1_controller_1a928270dab0081ce94c0c545657cab300}

The 7-bit I2C Slave address for the device.



### `protected inline constexpr uint8_t GetPotValueByte(bool index,uint8_t value)` {#class_maxim_d_s_1_1_controller_1a3c6a090203b3c31a3a745e4ffd8b051c}

Get the 8-bit transmission byte for the supplied pot value.

#### Parameters
* `index` Set to false for Pot 0, true for Pot 1 


* `value` The 6 bit potentiometer settings (0 == No Attenuation) 





#### Returns
constexpr uint8_t The 8 bit pot setting byte

### `protected inline void beginTransmission()` {#class_maxim_d_s_1_1_controller_1a1a2f39a2cf79daad9deb9849d02e1f82}

Start a TwoWire transmission.



### `protected inline void transmitByte(uint8_t data)` {#class_maxim_d_s_1_1_controller_1a4ba98d08696be9d9730a2c385f18f7d1}

Transmit a byte over TwoWire.

#### Parameters
* `data` The data byte to transmit

### `protected inline uint8_t endTransmission()` {#class_maxim_d_s_1_1_controller_1a7253b3e97f41aa5adb6fd2fa7621cef0}

End a TwoWrite transmission.



