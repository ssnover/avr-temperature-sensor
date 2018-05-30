## How to Build
Requires: CMake 3.5, avr-gcc Toolchain, avrdude

`mkdir debug && cd debug`

`cmake .. -DCMAKE_C_COMPILER=avr-gcc -DCMAKE_CXX_COMPILER=avr-g++`

`make avr_temperature_sensor`

To Flash to Your Board
`make flash-arduino`

You may need to change the USB port path in the top level CMakeLists. You can check which port your Arduino is on with the Arduino IDE. Or methodically unplugging devices from USB ports. Change the value of `ARDUINO_DEVICE_PORT` appropriately.