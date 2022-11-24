cmake_minimum_required(VERSION 3.18)

project(MyStreamer
	LANGUAGES C CXX ASM
	VERSION 0.1.0
)

add_subdirectory(app)
add_subdirectory(extern)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(tests)
