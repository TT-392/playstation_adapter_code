cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_compile_options(-Wall -Wextra -Wnull-dereference)

if (TARGET tinyusb_device)
# rest of your project
    add_executable(taiko
        src/main.c
        src/spi.c
        src/settings.c
        src/utils.c
        src/drum.c
        src/keybinds.c
        src/tinyusb/usb.c
        src/tinyusb/usb_descriptors.c
    )

    target_include_directories(taiko PRIVATE src src/tinyusb)

# Add pico_stdlib library which aggregates commonly used features
    target_link_libraries(taiko pico_stdio pico_stdlib pico_bootrom tinyusb_device tinyusb_board pico_multicore hardware_spi hardware_flash)

    pico_enable_stdio_usb(taiko 0)
    pico_enable_stdio_uart(taiko 0)

# create map/bin/hex/uf2 file in addition to ELF.
    pico_add_extra_outputs(taiko)

elseif(PICO_ON_DEVICE)
    message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in
the SDK")
endif()

