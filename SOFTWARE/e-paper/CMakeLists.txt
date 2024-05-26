cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(E-ink)

target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/epd1in54_V2.c)
target_sources(app PRIVATE src/epdif.c)
