﻿cmake_minimum_required(VERSION 3.7.2)

project(calculator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(calculator calculator.cpp main.cpp include/calculator.hpp)
target_include_directories(calculator PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(calculator PRIVATE Qt5::Core Qt5::Widgets)

install(TARGETS calculator
	RUNTIME DESTINATION "/usr/local/bin"
	DESTINATION "/usr/local/bin")

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "zavelskiymm-dev")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Simple calculator built with Qt engine")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "8")
set(CPACK_PACKAGE_VERSION_PATCH "9")

include(CPack)