# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/mihai/esp/esp-idf/components/bootloader/subproject"
  "/home/mihai/CLionProjects/CIMPLC-Firmware/main/modules/wasm/cmake-build-debug-esp32/bootloader"
  "/home/mihai/CLionProjects/CIMPLC-Firmware/main/modules/wasm/cmake-build-debug-esp32/bootloader-prefix"
  "/home/mihai/CLionProjects/CIMPLC-Firmware/main/modules/wasm/cmake-build-debug-esp32/bootloader-prefix/tmp"
  "/home/mihai/CLionProjects/CIMPLC-Firmware/main/modules/wasm/cmake-build-debug-esp32/bootloader-prefix/src/bootloader-stamp"
  "/home/mihai/CLionProjects/CIMPLC-Firmware/main/modules/wasm/cmake-build-debug-esp32/bootloader-prefix/src"
  "/home/mihai/CLionProjects/CIMPLC-Firmware/main/modules/wasm/cmake-build-debug-esp32/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/mihai/CLionProjects/CIMPLC-Firmware/main/modules/wasm/cmake-build-debug-esp32/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/mihai/CLionProjects/CIMPLC-Firmware/main/modules/wasm/cmake-build-debug-esp32/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
