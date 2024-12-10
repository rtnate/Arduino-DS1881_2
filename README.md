DS1881_2 Arduino Library
==========================
<<<<<<< Updated upstream
![GitHub License](https://img.shields.io/github/license/rtnate/Arduino-DS1881_2/)
Arduino Library for interfacing with Maxim DS1881 and DS1882 digital potentiometers
=======
![Version](https://img.shields.io/badge/Version-1.0.2-blue.svg)
[![License](https://img.shields.io/badge/License-MIT-lightgrey.svg)](https://opensource.org/licenses/MIT)
![ArduinoVersion](https://img.shields.io/badge/Arduino_Version->=1.8.6-lightgrey.svg)
[![Build Status](https://img.shields.io/github/actions/workflow/status/rtnate/Arduino-DS1881_2/arduino-lint.yaml)](https://github.com/rtnate/Arduino-DS1881_2/actions/workflows/arduino-lint.yaml)


Arduino Library for interfacing with Maxim DS1881 and DS1882 digital potentiometers


## Usage 

```C++
#include <Wire.h>
#include <DS1881_2.h>
//Create By Hardware Address Pins
// A0: HIGH, A1: LOW, A2: LOW
DS1882 digiPot(HIGH, LOW, LOW);

//Create By Address Value 0-7
DS1882 digiPot(0x3); //A0 and A1 high, A2 low

//Use an alternate TwoWire instance
TwoWire Wire2;
DS1882 digiPot(0x3, Wire2);

//Call begin (will initialize Wire)
digiPot.begin();

//Custom configuration (optional)
digiPot.configure(
  DS1882::PotentiometerMode::PotentiometerPositions63,
  true, /* enable zero cross detection */
  false /* don't use non-volatile memory */
);

digiPot.configure(
  DS1882::PotentiometerMode::PotentiometerPositions33,
  false, /* disable zero cross detection */
  true /* DO use non-volatile memory */
);

//THIS IS THE DEFAULT CONFIGURATION
digiPot.configure(
  DS1882::PotentiometerMode::PotentiometerPositions33,
  true, /* enable zero cross detection */
  false /* don't use non-volatile memory */
);

//Wire Pot Values
digiPot.writePot0(0) //Set Ch 0 to Full (-0 dB)
digiPot.writePot1(6) //Set Ch 1 to -6 dB
digiPot.writePots(20, 25) //Set Ch 0 to -20 dB, Ch 1 to -25dB
digiPot.writePots(63, 63) //Set both pots to MUTE
```
>>>>>>> Stashed changes
