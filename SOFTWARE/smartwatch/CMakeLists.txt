cmake_minimum_required(VERSION 3.20.0)

set(SHIELD npm1300_ek)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(BMA456-example)

include_directories(${CMAKE_SOURCE_DIR}/src)

target_sources(app PRIVATE src/main.c)

target_sources(app PRIVATE src/BLE/BLE.c)
target_sources(app PRIVATE src/BLE/step_count_service.c)
target_sources(app PRIVATE src/BLE/notification_service.c)
target_sources(app PRIVATE src/BLE/time_sync_service.c)

target_sources(app PRIVATE src/accelerometer/accelerometer.c)
target_sources(app PRIVATE src/accelerometer/bma4.c)
target_sources(app PRIVATE src/accelerometer/bma456w.c)
target_sources(app PRIVATE src/accelerometer/common.c)

target_sources(app PRIVATE src/watch_controller/watch_controller.c)

target_sources(app PRIVATE src/RTC/rtc.c)

target_sources(app PRIVATE src/power/npm1300func.c)
target_sources(app PRIVATE src/power/npm1300.c)

target_sources(app PRIVATE src/UI/vibration.c)
target_sources(app PRIVATE src/UI/ui_controller.c)
target_sources(app PRIVATE src/UI/display.c)

target_sources(app PRIVATE src/UI/epd/epd1in54_V2.c)
target_sources(app PRIVATE src/UI/epd/epdif.c)
target_sources(app PRIVATE
  src/UI/epd/epdpaint.c
  src/UI/epd/font8.c
  src/UI/epd/font12.c
  src/UI/epd/font16.c
  src/UI/epd/font20.c
  src/UI/epd/font24.c
)

# if(CONFIG_BUILD_WITH_TFM)
#   target_include_directories(app PRIVATE
#     $<TARGET_PROPERTY:tfm,TFM_BINARY_DIR>/api_ns/interface/include
#   )
# endif()
