cmake_minimum_required(VERSION 3.16)

project(Asio_client VERSION 1.0.0 DESCRIPTION "Asio echo client." LANGUAGES CXX)

enable_testing ()

add_executable (Asio_client
	"src/main.cpp"
)

target_link_libraries (Asio_client PRIVATE Asio_common)
