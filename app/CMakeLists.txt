set(target_name ${CMAKE_PROJECT_NAME}_cli)

# finding pkg-config is a helper tool
find_package(PkgConfig)

# using pkg-config to getting Gstreamer
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

# GStreamer header files directories
include_directories(
	${GLIB_INCLUDE_DIRS}
	${GSTREAMER_INCLUDE_DIRS}
)

# GStreamer library directories
link_directories(
	${GLIB_LIBRARY_DIRS}
	${GSTREAMER_LIBRARY_DIRS}
)


add_executable(${target_name}
	main.cpp
)

target_link_libraries(${target_name}
	PUBLIC
		${CMAKE_PROJECT_NAME}_includes
		${CMAKE_PROJECT_NAME}_lib
		${GSTREAMER_LIBRARIES}
)

set_target_properties(${target_name}
	PROPERTIES
		C_STANDARD 11
		CXX_STANDARD 17
)

