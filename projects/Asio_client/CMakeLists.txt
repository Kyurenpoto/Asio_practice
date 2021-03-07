cmake_minimum_required(VERSION 3.17)

project(Asio_client VERSION 0.1.0 DESCRIPTION "Asio echo client." LANGUAGES CXX)

enable_testing ()

add_executable (Asio_client
	"src/main.cpp"
)

target_link_libraries (Asio_client PRIVATE Asio_common)
