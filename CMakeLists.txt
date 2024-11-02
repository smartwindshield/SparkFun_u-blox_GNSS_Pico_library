# Added as a subdirectory to the smartwindshield project

add_library(sparkfun_ublox_gnss_pico INTERFACE
    src/SparkFun_u-blox_GNSS_Pico_Library.cpp
)

target_include_directories(sparkfun_ublox_gnss_pico PRIVATE
    src/
)
target_link_libraries(sparkfun_ublox_gnss_pico INTERFACE
    pico_stdlib
    hardware_i2c
    hardware_gpio
)
