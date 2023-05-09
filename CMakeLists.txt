###############################################################################
# Main user settings
###############################################################################
# Project metadata
set(PROJECT_NAME        "pico_rtos_example")
set(PROJECT_DESCRIPTION "Example Raspberry Pi Pico project including FreeRTOS and all pico SDK bells and whistles.")
set(PROJECT_VERSION     "0.1")
set(PROJECT_URL         "https://example.com/")

# The target RP2040 board.
set(PICO_BOARD pico)

# Compiler defines.
set(PROJECT_DEFINES
    EXAMPLE_DEFINE
    # ...
)

# Declare the source files.
set(PROJECT_SRC_FILES
    src/main.cpp
    # ...
)

# Declare the include paths.
set(PROJECT_INCLUDE_PATHS
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# Declare the libraries that will be linked in.
set(PROJECT_LINK_LIBRARIES
    pico_stdlib                   # Pico standard library, includes:
                                  #   - hardware_uart
                                  #   - hardware_gpio
                                  #   - pico_binary_info
                                  #   - pico_runtime
                                  #   - pico_platform
                                  #   - pico_printf
                                  #   - pico_stdio
                                  #   - pico_standard_link
                                  #   - pico_util
    #hardware_adc                 # Pico ADC hardware.
    #hardware_base                # Pico low level MMIO.
    #hardware_claim               # Pico hardware resource management.
    #hardware_clocks              # Pico hardware clocks.
    #hardware_divider             # Pico hardware divider.
    #hardware_dma                 # Pico DMA hardware.
    #hardware_exception           # Pico hardware exception handlers.
    #hardware_flash               # Pico flash hardware.
    #hardware_gpio                # Pico GPIO hardware.
    #hardware_i2c                 # Pico I2C hardware.
    #hardware_interp              # Pico hardware interpolator.
    #hardware_irq                 # Pico IRQ hardware.
    #hardware_pll                 # Pico PLL hardware.
    #hardware_pwm                 # Pico PWM hardware.
    #hardware_resets              # Pico hardware resets.
    #hardware_rtc                 # Pico RTC hardware.
    #hardware_spi                 # Pico SPI hardware.
    #hardware_timer               # Pico hardware timer.
    #hardware_uart                # Pico UART hardware.
    #hardware_vreg                # Pico internal voltage regulator.
    #hardware_watchdog            # Pico hardware watchdog.
    #pico_async_context           # Pico high level threading.
    #pico_multicore               # Pico high level multicore support.
    #pico_i2c_slave               # Pico high level i2c slave support.
    #pico_rand                    # Pico high level rng.
    #pico_sync                    # Pico threading primitives.
    #pico_time                    # Pico timestamps and time based callbacks.
    #pico_unique_id               # Pico device ID.
    #pico_util                    # Pico utilities and data structures.
    #tinyusb_device tinyusb_board # Pico USB support.
    FreeRTOS-Kernel               # FreeRTOS kernel.
    #FreeRTOS-Kernel-Static       # FreeRTOS kernel supporting static allocation.
    #FreeRTOS-Kernel-Heap1        # FreeRTOS heap allocator level 1.
    #FreeRTOS-Kernel-Heap2        # FreeRTOS heap allocator level 2.
    #FreeRTOS-Kernel-Heap3        # FreeRTOS heap allocator level 3.
    FreeRTOS-Kernel-Heap4         # FreeRTOS heap allocator level 4. The default.
    #FreeRTOS-Kernel-Heap5        # FreeRTOS heap allocator level 5.
)

# PIO settings.
set(PROJECT_USES_PIO 1)
set(PROJECT_PIO_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/main.pio
    # ...
)

# Set up stdio behavior. Multiple can be enabled.
set(PROJECT_ENABLE_STDIO_UART        1) # Allows stdio to function over UART0
set(PROJECT_ENABLE_STDIO_USB_CDC     0) # Allows stdio to function over USB CDC, disables other USB usage.
set(PROJECT_ENABLE_STDIO_SEMIHOSTING 0) # Allows stdio to be used directly over the CMSIS-DAP console.

# Miscellaneous options.
set(PICO_CXX_ENABLE_EXCEPTIONS 1) # Enable C++ exceptions.
set(PICO_CXX_ENABLE_RTTI       1) # Enable C++ runtime type information.
###############################################################################

# CMAKE requirements
cmake_minimum_required(VERSION 3.13)

# Find dependencies
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(pico_sdk_import)
include(pico_extras_import)
include(FreeRTOS_Kernel_import)

# Set up our main project.
project(
    ${PROJECT_NAME}
    LANGUAGES C CXX ASM
    DESCRIPTION ${PROJECT_DESCRIPTION}
)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the pico SDK.
pico_sdk_init()

# Add the executable for our project.
add_executable(${PROJECT_NAME} ${PROJECT_SRC_FILES})

# Process PIO files if required.
if(${PROJECT_USES_PIO})
    list(APPEND PROJECT_LINK_LIBRARIES hardware_pio)
    foreach(PIO ${PROJECT_PIO_SOURCES})
        pico_generate_pio_header(${PROJECT_NAME} ${PIO})
        message(${PIO})
    endforeach()
endif()

# Libraries, includes and defines.
target_link_libraries(${PROJECT_NAME}        ${PROJECT_LINK_LIBRARIES})
target_include_directories(${PROJECT_NAME}   PUBLIC ${PROJECT_INCLUDE_PATHS})
target_compile_definitions(${PROJECT_NAME}   PRIVATE ${PROJECT_DEFINES})

# Pico specific metadata for the executable.
pico_set_program_name(${PROJECT_NAME}        "${PROJECT_NAME}")
pico_set_program_description(${PROJECT_NAME} "${PROJECT_DESCRIPTION}")
pico_set_program_url(${PROJECT_NAME}         "${PROJECT_URL}")
pico_set_program_version(${PROJECT_NAME}     "${PROJECT_VERSION}")

# Tell the pico SDK to also output bin/hex/uf2 files.
pico_add_extra_outputs(${PROJECT_NAME})
