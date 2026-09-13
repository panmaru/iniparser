add_library(iniparserutils STATIC
	trim.cpp
	split.cpp
)

target_include_directories(iniparserutils PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)