cmake_minimum_required(VERSION 3.17)

project(Asio_server VERSION 1.0.0 DESCRIPTION "Asio echo server." LANGUAGES CXX)

enable_testing ()

add_executable (Asio_server
	"src/main.cpp"
)

target_link_libraries (Asio_server PRIVATE Asio_common)
