add_executable( test_i2c
    test_i2c
)

# message(STATUS "${Boost_LIBRARY_DIRS}" )
target_link_libraries(
    test_i2c
    -lArduCamLib 
    -larducam_config_parser
    -lpthread
    -ldl
)