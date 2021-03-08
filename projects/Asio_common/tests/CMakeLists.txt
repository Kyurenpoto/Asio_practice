cmake_minimum_required(VERSION 3.16)

project(Test_Asio_common VERSION 1.0.0 DESCRIPTION "Common codes." LANGUAGES CXX)

enable_testing ()

add_executable (Test_Asio_common
	"test.h"
	"main.cpp"
	"MessageSourceTest.cpp"
	"MessageTargetTest.cpp"
	"EchoSourceTest.cpp"
	"EchoTargetTest.cpp"
)

add_dependencies (Test_Asio_common Asio_common)

add_test (Test_Asio_common Test_Asio_common)

find_package (Threads REQUIRED)
find_package (Asio REQUIRED)

target_link_libraries (Test_Asio_common PRIVATE asio::asio)
target_link_libraries (Test_Asio_common PRIVATE ut)
target_link_libraries (Test_Asio_common PRIVATE Asio_common)

target_compile_features (Test_Asio_common PUBLIC cxx_std_20)

if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
target_compile_options(Test_Asio_common PUBLIC -Wall -Wpedantic -std=c++20 -stdlib=libc++)
target_link_libraries(Test_Asio_common PUBLIC -stdlib=libc++)
elseif(CMAKE_CXX_COMPILER_ID MATCHES GNU)
target_compile_options(Test_Asio_common PUBLIC -Wall -Wpedantic -std=c++20 -fcoroutines)
endif()
