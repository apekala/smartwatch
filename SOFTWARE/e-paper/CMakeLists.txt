cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(E-ink)

target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/epd1in54_V2.c)
target_sources(app PRIVATE src/epdif.c)
target_sources(app PRIVATE
  src/epdpaint.c
  src/font8.c
  src/font12.c
  src/font16.c
  src/font20.c
  src/font24.c
)
