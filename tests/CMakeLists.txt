include(GoogleTest)
enable_testing()

include_directories("${CMAKE_SOURCE_DIR}/src")

add_subdirectory(perf)
add_subdirectory(unit)
