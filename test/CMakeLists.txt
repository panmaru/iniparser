add_executable(iniparsertest test.cpp)

target_link_libraries(iniparsertest PRIVATE
    parser
)
