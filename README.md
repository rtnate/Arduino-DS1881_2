# namespace `MaximDS`



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[``Controller``](#class_maxim_d_s_1_1_controller)    | Class for controlling a [MaximDS](#namespace_maxim_d_s) digital potentiomer (DS1881 or DS1882)
# class `Controller` {#class_maxim_d_s_1_1_controller}


Class for controlling a [MaximDS](#namespace_maxim_d_s) digital potentiomer (DS1881 or DS1882)



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  Controller(uint8_t address)` | Construct a new Device [Controller](#class_maxim_d_s_1_1_controller) object using the default Wire instance.
`public inline  Controller(uint8_t address,TwoWire & i2cObj)` | Construct a new Device [Controller](#class_maxim_d_s_1_1_controller) object using the supplied TwoWire instance.
`public void begin(`[`PotentiometerMode`](#class_maxim_d_s_1_1_controller_1acd744d60d5ff0489be1fdb9a03039fa1)` mode)` | Initializes the controller and configures the pot to the mode supplied (33 positions be default).
`public bool configure(`[`PotentiometerMode`](#class_maxim_d_s_1_1_controller_1acd744d60d5ff0489be1fdb9a03039fa1)` mode,bool enableZeroCross,bool enableNVM)` | Set the configuration register of the digital pot.
`public uint8_t writePot0(uint8_t value)` | Sets the value of Potentiometer 0.
`public uint8_t writePot1(uint8_t value)` | Sets the value of Potentiometer 1.
`public uint8_t writePots(uint8_t pot0,uint8_t pot1)` | Sets the value of both potentiometers (0 == Fully On, 33 or 63 == MUTE)
`protected TwoWire & i2c` | Reference to the TwoWire object that controls data transmission.
`protected const uint8_t slaveAddress` | The 7-bit I2C Slave address for the device.
`protected inline constexpr uint8_t GetPotValueByte(bool index,uint8_t value)` | Get the 8-bit transmission byte for the supplied pot value.
`protected inline void beginTransmission()` | Start a TwoWire transmission.
`protected inline void transmitByte(uint8_t data)` | Transmit a byte over TwoWire.
`protected inline uint8_t endTransmission()` | End a TwoWrite transmission.

## Members

### `public inline  Controller(uint8_t address)` {#class_maxim_d_s_1_1_controller_1a36218404814ebbce004d9b1651129bba}

Construct a new Device [Controller](#class_maxim_d_s_1_1_controller) object using the default Wire instance.

Takes a 3-bit address value corresponding to the state of the hardware pins:


A2   |A1   |A0   |Value
--------- | --------- | --------- | ---------
L   |L   |L   |0x0
L   |L   |H   |0x1
L   |H   |L   |0x2
L   |H   |H   |0x3
H   |L   |L   |0x4
H   |L   |H   |0x5
H   |H   |L   |0x6
H   |H   |H   |0x7


#### Parameters
* `address` The 3 bit pin-programmed slave address

### `public inline  Controller(uint8_t address,TwoWire & i2cObj)` {#class_maxim_d_s_1_1_controller_1aa4858a88c37a60065e324ac144186582}

Construct a new Device [Controller](#class_maxim_d_s_1_1_controller) object using the supplied TwoWire instance.

Takes a 3-bit address value corresponding to the state of the hardware pins:


A2   |A1   |A0   |Value
--------- | --------- | --------- | ---------
L   |L   |L   |0x0
L   |L   |H   |0x1
L   |H   |L   |0x2
L   |H   |H   |0x3
H   |L   |L   |0x4
H   |L   |H   |0x5
H   |H   |L   |0x6
H   |H   |H   |0x7


#### Parameters
* `address` The 3 bit pin-programmed slave address 


* `i2cObj` A reference to the TwoWire instance for transmission

### `public void begin(`[`PotentiometerMode`](#class_maxim_d_s_1_1_controller_1acd744d60d5ff0489be1fdb9a03039fa1)` mode)` {#class_maxim_d_s_1_1_controller_1ac0a5e58051a2bff244b5bc816f7bf960}

Initializes the controller and configures the pot to the mode supplied (33 positions be default).

Should be called in setup().


#### Parameters
* `mode` The PotentiometerMode to use (number of wiper positions) 





**See also**: [PotentiometerMode](#class_maxim_d_s_1_1_controller_1acd744d60d5ff0489be1fdb9a03039fa1)

### `public bool configure(`[`PotentiometerMode`](#class_maxim_d_s_1_1_controller_1acd744d60d5ff0489be1fdb9a03039fa1)` mode,bool enableZeroCross,bool enableNVM)` {#class_maxim_d_s_1_1_controller_1a8bd82d26b2476c449797cc4baffcced4}

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



