# Copyright © 2014-2015 Martin Ueding <dev@martin-ueding.de>
# Licensed under The GNU Public License Version 2 (or later)

cmake_minimum_required(VERSION 2.6)
project(battery-health C CXX)

set(CMAKE_CXX_COMPILER "/usr/bin/g++")

add_definitions("-std=c++11")
add_definitions("-Wall")
add_definitions("-Werror")
add_definitions("-Wpedantic")

find_package(Boost COMPONENTS filesystem program_options system REQUIRED)

add_executable(battery-health
    main.cpp
    )

include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(battery-health ${Boost_LIBRARIES})

install(TARGETS battery-health DESTINATION bin)
install(PROGRAMS

    battery-health-plot
    submit-battery-status

    DESTINATION bin)
