# Added as a subdirectory to the smartwindshield project

add_library(sparkfun_ublox_gnss_pico 
    src/SparkFun_u-blox_GNSS_Pico_Library.cpp
    src/ArduinoToPico.cpp
)

target_include_directories(sparkfun_ublox_gnss_pico PRIVATE
    include/
)
target_link_libraries(sparkfun_ublox_gnss_pico 
    pico_stdlib
    hardware_i2c
    hardware_gpio
)
