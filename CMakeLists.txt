cmake_minimum_required (VERSION 3.17)

project (Asio_practice VERSION 1.0.0 LANGUAGES CXX)

enable_testing ()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# projects
add_subdirectory (projects/Asio_server)
add_subdirectory (projects/Asio_client)
add_subdirectory (projects/Asio_common)

# submodules
add_subdirectory (submodules/spdlog)
add_subdirectory (submodules/ut)

# dependencies
add_dependencies (Asio_server
	Asio_common
)
add_dependencies (Asio_client
	Asio_common
)
add_dependencies (Asio_common
	spdlog
	ut
	asio::asio
)
