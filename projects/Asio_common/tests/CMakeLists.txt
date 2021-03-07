cmake_minimum_required(VERSION 3.17)

project(Test_Asio_common VERSION 0.1.0 DESCRIPTION "Common codes." LANGUAGES CXX)

add_executable (Test_Asio_common
	"CoroutineRunner.h"
	"test.h"
	"main.cpp"
	"CoroutineRunner.cpp"
	"MessageSourceTest.cpp"
	"MessageTargetTest.cpp"
 "EchoSourceTest.cpp" "EchoTargetTest.cpp")

add_dependencies (Test_Asio_common Asio_common)

find_package (Asio)

target_link_libraries (Test_Asio_common PRIVATE asio::asio)
target_link_libraries (Test_Asio_common PRIVATE spdlog)
target_link_libraries (Test_Asio_common PRIVATE ut)
target_link_libraries (Test_Asio_common PRIVATE Asio_common)

target_compile_features (Test_Asio_common PUBLIC cxx_std_20)
