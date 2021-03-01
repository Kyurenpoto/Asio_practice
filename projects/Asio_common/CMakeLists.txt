cmake_minimum_required(VERSION 3.17)

project(Asio_common VERSION 0.1.0 DESCRIPTION "Common codes." LANGUAGES CXX)

add_library (Asio_common STATIC
	"include/Asio_common/common.h"
	"src/common.cpp"
)

find_package (Asio)

target_include_directories (Asio_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries (Asio_common PRIVATE asio::asio)
target_link_libraries (Asio_common PRIVATE spdlog)
target_link_libraries (Asio_common PRIVATE scn::scn)

target_compile_features (Asio_common PUBLIC cxx_std_20)
