add_library(testkit INTERFACE
	testkit.h
)

target_include_directories(testkit INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
)
