# Quantel PAD USB interface

Interfaces a Quantel Paintbox input device (tablet, keyboard, rat/grip) and turns it into three USB
devices.

Requires a Raspberry Pi Pico 2040 and a Waveshare Pico-2CH-RS485 interface board.

Set `PICO_SDK_PATH` in your environment vars to wherever your `pico-sdk` is located. For convenience
I have added it as a submodule for this repo. So if your build directory is `build` then set
`PICO_SDK_PATH=../pico-sdk` That is, it's relative to the build directory not the source root.

## Technical documentation

More documentation can be found [here](docs/index.md)

## Things left to figure out
- The exact range of the tablet.
- Does the range change based on the size of the tablet?
- Is pen data included in a keyboard event?
- Byte 2 bit 5 is always set, but all other unknowns are always unset.
