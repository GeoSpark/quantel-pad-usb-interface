cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(quantel_pad_usb_interface C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(FAMILY rp2040)
set(BOARD pico_sdk)
set(TOP ${PICO_TINYUSB_PATH})

# If you want debug output from USB (pass -DPICO_STDIO_USB=1) this ensures you don't lose any debug output while USB is set up
#if (NOT DEFINED PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS)
#    set(PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS 3000)
#endif()

#set(PICO_STDIO_USB_ENABLE_RESET_VIA_BAUD_RATE 1)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your my_project

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        )
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()

option(SIMULATED_INPUT "Simulate serial data with a recorded stream" ON)

configure_file(${CMAKE_CURRENT_LIST_DIR}/src/config.h.in ${CMAKE_CURRENT_LIST_DIR}/src/config.h)

add_executable(quantel_pad_usb_interface)

target_sources(quantel_pad_usb_interface PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src/main.c
        ${CMAKE_CURRENT_LIST_DIR}/src/serial.c
        ${CMAKE_CURRENT_LIST_DIR}/src/usb/usb_descriptors.c
        ${CMAKE_CURRENT_LIST_DIR}/src/usb/usb_quantel.c
        ${CMAKE_CURRENT_LIST_DIR}/src/quantel/quantel.c
)

# Make sure TinyUSB can find tusb_config.h
target_include_directories(quantel_pad_usb_interface PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src
        ${CMAKE_CURRENT_LIST_DIR}/src/usb
        ${CMAKE_CURRENT_LIST_DIR}/src/quantel
)

# pull in common dependencies
target_link_libraries(quantel_pad_usb_interface PUBLIC pico_stdlib pico_unique_id tinyusb_device tinyusb_board)

if (PICO_CYW43_SUPPORTED)
    target_link_libraries(quantel_pad_usb_interface pico_cyw43_arch_none)
endif()

pico_enable_stdio_usb(quantel_pad_usb_interface 0)
pico_enable_stdio_uart(quantel_pad_usb_interface 1)

# create map/bin/hex file etc.
pico_add_extra_outputs(quantel_pad_usb_interface)
