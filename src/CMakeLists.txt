set(target_name ${CMAKE_PROJECT_NAME}_lib)

add_library(${target_name}
	OBJECT
		message.cpp
)

target_link_libraries(${target_name}
	PUBLIC
		${CMAKE_PROJECT_NAME}_includes
)

set_target_properties(${target_name}
	PROPERTIES
		C_STANDARD 11
		CXX_STANDARD 17
)
