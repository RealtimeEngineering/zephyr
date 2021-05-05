# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

# START added for CLion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#set(ENV{BOARD} frdm_k64f)
#set(ENV{BOARD} smartguardcom)
set(ENV{BOARD} nucleo_h743zi)

set(ENV{ZEPHYR_SDK_INSTALL_DIR} /usr/local/zephyr-sdk-0.12.3)
set(ENV{ZEPHYR_TOOLCHAIN_VARIANT} gnuarmemb)
# STOP added for CLion

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(modbus-serial-backend)

target_sources(app PRIVATE src/main.c)
