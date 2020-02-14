include_directories(${PROJECT_SOURCE_DIR}/src)
add_executable("ray_tracing_test" ray_tracing_test.cpp)
add_test(NAME ray_tracing_test COMMAND ray_tracing_test)