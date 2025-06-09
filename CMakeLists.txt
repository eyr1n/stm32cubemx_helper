cmake_minimum_required(VERSION 3.22)

project(stm32cubemx_helper LANGUAGES CXX)

include(CMSISDeviceHeader.cmake)
if(EXISTS "${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}.ioc")
  FindCMSISDeviceHeader("${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}.ioc")
  configure_file(device.hpp.in include/stm32cubemx_helper/device.hpp)
else()
  message(WARNING "\"${CMAKE_PROJECT_NAME}.ioc\" not found")
endif()

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE
  include
  ${CMAKE_CURRENT_BINARY_DIR}/include
)
target_compile_features(${PROJECT_NAME} INTERFACE
  cxx_std_11
)

# ::printf_float
add_library(${PROJECT_NAME}_printf_float INTERFACE)
add_library(${PROJECT_NAME}::printf_float ALIAS ${PROJECT_NAME}_printf_float)
target_link_libraries(${PROJECT_NAME}_printf_float INTERFACE
  "-u _printf_float"
)

# ::scanf_float
add_library(${PROJECT_NAME}_scanf_float INTERFACE)
add_library(${PROJECT_NAME}::scanf_float ALIAS ${PROJECT_NAME}_scanf_float)
target_link_libraries(${PROJECT_NAME}_scanf_float INTERFACE
  "-u _scanf_float"
)
