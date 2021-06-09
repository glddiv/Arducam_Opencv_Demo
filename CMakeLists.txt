set(APP_NAME Arducam_Opencv_Demo)

cmake_minimum_required(VERSION 2.8.12)

project(${APP_NAME})

add_definitions(-D__PC__)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++17 ${CMAKE_CXX_FLAGS}")
    message(STATUS "optional:-std=c++17")   
endif(CMAKE_COMPILER_IS_GNUCXX)

find_package( OpenCV REQUIRED )

include_directories(
    ./src
    ./src/Arducam_SDK
    ${OpenCV_INCLUDE_DIRS}
)

add_executable( ${APP_NAME}
    src/Arducam.cpp
    src/ArduCam_Demo.cpp
    src/Utils.cpp
)

# message(STATUS "${Boost_LIBRARY_DIRS}" )
target_link_libraries(
    ${APP_NAME} 
    -lArduCamLib 
    -larducam_config_parser
    -lpthread
    ${OpenCV_LIBS}
)

add_subdirectory(examples)
# link libraries
# target_link_libraries(
#    ${APP_NAME}
#    PRIVATE
#    -lusb-1.0
#    -lpthread
# )












