add_executable( test_i2c_detect
    test_i2c_detect.cpp
)

# message(STATUS "${Boost_LIBRARY_DIRS}" )
target_link_libraries(
    test_i2c_detect
    -lArduCamLib 
    -larducam_config_parser
    -lpthread
    -ldl
)