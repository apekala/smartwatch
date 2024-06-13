# Install script for directory: D:/aplikacje/nRF/v2.6.0/zephyr

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/Zephyr-Kernel")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "D:/aplikacje/nRF/toolchains/cf2149caf2/opt/zephyr-sdk/arm-zephyr-eabi/bin/arm-zephyr-eabi-objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/zephyr/arch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/zephyr/lib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/zephyr/soc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/zephyr/boards/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/zephyr/subsys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/zephyr/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/nrf/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/hostap/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/mcuboot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/mbedtls/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/trusted-firmware-m/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/cjson/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/azure-sdk-for-c/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/cirrus-logic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/openthread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/memfault-firmware-sdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/canopennode/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/chre/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/lz4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/nanopb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/zscilib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/cmsis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/cmsis-dsp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/cmsis-nn/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/fatfs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/hal_nordic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/st/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/hal_wurthelektronik/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/libmetal/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/liblc3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/littlefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/loramac-node/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/lvgl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/mipi-sys-t/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/nrf_hw_models/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/open-amp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/picolibc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/segger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/tinycrypt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/uoscore-uedhoc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/zcbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/nrfxlib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/modules/connectedhomeip/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/zephyr/kernel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/zephyr/cmake/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/zephyr/cmake/usage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/franz/Documents/studia/eity/PBL4/smartwatch2/smartwatch/SOFTWARE/e-paper3/build/zephyr/cmake/reports/cmake_install.cmake")
endif()

