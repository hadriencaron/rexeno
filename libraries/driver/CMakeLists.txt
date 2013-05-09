cmake_minimum_required (VERSION 2.6)
include_directories ("${PROJECT_SOURCE_DIR}/includes")
add_library (driver dummyDriver.cc calibration.cc)

