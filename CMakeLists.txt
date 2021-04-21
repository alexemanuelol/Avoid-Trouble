cmake_minimum_required(VERSION 3.20.1)

project(AvoidTrouble)

set(EXECUTABLE_NAME "avoid-trouble")

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_subdirectory(src)
