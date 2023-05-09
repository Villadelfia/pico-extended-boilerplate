# Extended RP2040 SDK Boilerplate

This repository contains a good starting point to configure and use the complete Raspberry Pi Pico C SDK including PIO support. In addition, FreeRTOS is pulled in as a dependency.

## Setting up
It is assumed that the user has the pico-sdk, pico-extras and freertos-kernel repositories cloned and ready on their drive. The included scripts expect to find the path of these repositories in the following environment variables:

 - PICO_SDK_PATH
 - PICO_EXTRAS_PATH
 - FREERTOS_KERNEL_PATH

You can test your setup with the following commands:

```sh
mkdir build
cd build
cmake ..
make -j 4
```

If this produces a .uf2 file in your build directory, your setup works.

## Configuring
The included CMakeLists.txt file is designed to easily tailor the project from the out-of-box experience to your own project. A heavily commented configuration section is provided to help you select options.

## The Base Project
The base project simple blinks the on-board LED as well GPIO 10 in an alternating manner using the PIO system every 500ms.

