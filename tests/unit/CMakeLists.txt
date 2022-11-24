set(target_name tests-unit)

add_executable(${target_name}
	message_tests.cpp
)

set_target_properties(${target_name}
	PROPERTIES
		C_STANDARD 11
		CXX_STANDARD 17
)

target_link_libraries(${target_name}
	${CMAKE_PROJECT_NAME}_lib
	${CMAKE_PROJECT_NAME}_includes
	gtest_main
)

gtest_discover_tests(${target_name})
