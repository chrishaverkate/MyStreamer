set(target_name tests-perf)

add_executable(${target_name}
	message_perf.cpp
)

set_target_properties(${target_name}
	PROPERTIES
		C_STANDARD 11
		CXX_STANDARD 17
)

target_link_libraries(${target_name}
	${CMAKE_PROJECT_NAME}_lib
	${CMAKE_PROJECT_NAME}_includes
	benchmark::benchmark_main
)
