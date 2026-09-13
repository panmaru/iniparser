add_library(iniparser_utils STATIC
	trim.cpp
	split.cpp
)

target_include_directories(iniparser_utils PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)