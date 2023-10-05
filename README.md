# DS1881_2 Arduino Library


## Basic Usage

```C++

//Create a digital pot with address pins all low
DS1882 digitalPot(0x0);

void setup() {
//Begin using the pot with 33 wiper positions
    digitalPot.begin(PotentiometerPositions33);
//Reconfigure the pot with 63 wiper positions, 
//enable the zero crossing, and disable non-volatile memory
    digitalPot.configure(PotentiometerPositions63, true, false);
}

void run() {
//Mute Pot 0 and set Pot 1 to full
    digitalPot.writePot0(63);
    digitalPot.writePot1(0);
    delay(3000);
//Mute Pot 1 and set Pot 0 to full
    digitalPot.writePot0(0);
    digitalPot.writePot1(63);
    delay(3000);
//Set both pots to -12 db 
    digitalPot.writePots(12, 12);
    delay(3000);
//Set Pot 0 to -18 db and Pot 1 to -4 db
    digitalPot.writePots(18, 4);
    delay(3000);
}
```
### Note on Class Names/Namespace 
The controller class in the source code is MaximDS::Controller.  This is aliased 
to DS1881 or DS1882 in the library header.  For simplicity I will use DS1882 as 
the class name in the documentation, but one can use DS1881 and they are
exactly the same.

---

## Constructors

### `DS1882(uint8_t address)`

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

---

### `DS1882(uint8_t address, TwoWire & i2cObj)`

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

---

## Public Methods

### `void begin(`[`PotentiometerMode`](#Enums)` mode)`

Initializes the controller and configures the pot to the mode supplied (33 positions be default).

Should be called in setup().

#### Parameters
* `mode` The PotentiometerMode to use (number of wiper positions) 

---

### `bool configure(`[`PotentiometerMode`](#Enums)` mode, bool enableZeroCross, bool enableNVM)`

Set the configuration register of the digital pot.

Use to explicitly set the configuration options, this 
   will transmit these values to the digital pot.

#### Parameters
* `mode` The PotentiometerMode to use (number of wiper positions) 


* `enableZeroCross` Set to false to disable the zero-crossing detector 


* `enableNVM` Set to true to enable non-volatile wiper setting storage 

#### Returns
true on success, false on bus error

---

### `uint8_t writePot0(uint8_t value)`

Sets the value of Potentiometer 0.

#### Parameters
* `value` The 6 bit wiper position (0 == Fully On, 33 or 63 == MUTE) 

#### Returns
The status code from the Wire interface: 0 .. success 1 .. length to long for buffer 2 .. address send, NACK received 3 .. data send, NACK received 4 .. other twi error (lost bus arbitration, bus error, ..) 5 .. timeout

---

### `public uint8_t writePot1(uint8_t value)`

Sets the value of Potentiometer 1.

#### Parameters
* `value` The 6 bit wiper position (0 == Fully On, 33 or 63 == MUTE) 

#### Returns
The status code from the Wire interface: 0 .. success 1 .. length to long for buffer 2 .. address send, NACK received 3 .. data send, NACK received 4 .. other twi error (lost bus arbitration, bus error, ..) 5 .. timeout

---

### `public uint8_t writePots(uint8_t pot0,uint8_t pot1)` 
Sets the value of both potentiometers (0 == Fully On, 33 or 63 == MUTE)

#### Parameters
* `pot0` The 6 bit wiper position for Potentiometer 0 

* `pot1` The 6 bit wiper position for Potentiometer 1 

#### Returns
The status code from the Wire interface: 0 .. success 1 .. length to long for buffer 2 .. address send, NACK received 3 .. data send, NACK received 4 .. other twi error (lost bus arbitration, bus error, ..) 5 .. timeout

---

## Enums

### `PotentiometerMode`

#### Members
* `PotentiometerPositions63` Will use the pot with 63 wiper positions (0 max - 63 mute).
* `PotentiometerPositions33` Will use the pot with 33 wiper position (0 max - 33+ mute).
