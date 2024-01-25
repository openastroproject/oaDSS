cmake_minimum_required(VERSION 3.10)

add_executable ( TestZPtr
	TestZPtr.cpp
)

target_include_directories ( TestZPtr
    PRIVATE
    ..
)

target_compile_options( TestZPtr PRIVATE -fPIC)
