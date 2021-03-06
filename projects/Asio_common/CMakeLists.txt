cmake_minimum_required(VERSION 3.17)

project(Asio_common VERSION 0.1.0 DESCRIPTION "Common codes." LANGUAGES CXX)

include(CheckIncludeFileCXX)
include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)

if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    if(WIN32)
        check_cxx_compiler_flag("/std:c++latest"            support_latest)
        check_cxx_compiler_flag("/clang:-fcoroutines-ts"    support_coroutine)
        check_include_file_cxx("experimental/coroutine" has_coroutine_ts
            "/std:c++latest"
        )
    else()
        check_cxx_compiler_flag("-std=c++2a"          support_latest)
        check_cxx_compiler_flag("-fcoroutines-ts"     support_coroutine)
        check_include_file_cxx("experimental/coroutine" has_coroutine_ts
            "-std=c++2a"
        )
    endif()

elseif(MSVC)
    #
    # Notice that `/std:c++latest` and `/await` is exclusive to each other.
    # With MSVC, we have to distinguish Coroutines TS & C++ 20 Coroutines
    #
    check_cxx_compiler_flag("/std:c++latest"    support_latest)
    check_cxx_compiler_flag("/await"            support_coroutine)
    check_include_file_cxx("coroutine"  has_coroutine
        "/std:c++latest"
    )
    if(NOT has_coroutine)
        message(STATUS "Try <expeirmental/coroutine> (Coroutines TS) instead of <coroutine> ...")
        check_include_file_cxx("experimental/coroutine" has_coroutine_ts
            "/std:c++17"
        )
    endif()
    # has coroutine headers?
    if(NOT has_coroutine AND NOT has_coroutine_ts)
        message(FATAL_ERROR "There are no headers for C++ Coroutines")
    endif()

elseif(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    #
    # expect GCC 10 or later
    #
    check_cxx_compiler_flag("-std=gnu++20"        support_latest)
    check_cxx_compiler_flag("-fcoroutines"        support_coroutine)
    check_include_file_cxx("coroutine" has_coroutine
        "-std=gnu++20 -fcoroutines"
    )
    if(APPLE)
        # -isysroot "/usr/local/Cellar/gcc/${CMAKE_CXX_COMPILER_VERSION}/include/c++/${CMAKE_CXX_COMPILER_VERSION}"
        # -isysroot "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include"
        # -isysroot "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1"
    endif()
    set(try_compile_flags "-fcoroutines")
endif()
# support compiler options for coroutine?
if(NOT support_coroutine)
    message(FATAL_ERROR "The compiler doesn't support C++ Coroutines")
endif()

add_library (Asio_common STATIC
	"include/Asio_common/common.h"
	"include/Asio_common/detail/EndPointString.h"
	"include/Asio_common/detail/Input.h"
	"include/Asio_common/detail/HandledException.h"
	"include/Asio_common/detail/DetachedIOContext.h"
	"include/Asio_common/detail/Message.h"
	"include/Asio_common/detail/Echo.h"
	"src/common.cpp"
	"src/detail/EndPointString.cpp"
	"src/detail/Input.cpp"
	"src/detail/HandledException.cpp"
	"src/detail/DetachedIOContext.cpp"
	"src/detail/Message.cpp"
	"src/detail/Echo.cpp"
)

find_package (Threads REQUIRED)
find_package (Asio REQUIRED)

target_include_directories (Asio_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries (Asio_common PRIVATE asio::asio)
target_link_libraries (Asio_common PRIVATE spdlog)

target_compile_features (Asio_common PUBLIC cxx_std_20)

set (CMAKE_BUILD_TYPE Debug)

if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
target_compile_options(Asio_common PUBLIC -Wall -Wpedantic -std=c++20 -fcoroutines -stdlib=libc++)
target_link_libraries(Asio_common PUBLIC -stdlib=libc++)
elseif(MSVC)
target_compile_options(Asio_common PUBLIC /std:c++latest /await)
elseif(CMAKE_CXX_COMPILER_ID MATCHES GNU)
target_compile_options(Asio_common PUBLIC -Wall -Wpedantic -std=c++20 -fcoroutines)
endif()
