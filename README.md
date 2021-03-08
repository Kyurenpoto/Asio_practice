<a href="LICENSE.md" target="_blank">![MIT License](https://img.shields.io/badge/license-MIT-blue)</a>
[![Build Status](https://travis-ci.com/Kyurenpoto/Asio_practice.svg?branch=main)](https://travis-ci.com/Kyurenpoto/Asio_practice)
[![Build status](https://ci.appveyor.com/api/projects/status/m5q2r5169ww4gpyr?svg=true)](https://ci.appveyor.com/project/Kyurenpoto/asio-practice)

# Asio_practice

Practice for basic Asio echo Server/Client.

## How to checkout and build

### Linux

1. Checkout this repository and submodules

```
git clone https://github.com/Kyurenpoto/Asio_practice.git
cd Asio_practice
git submodule init
git submodule update
```

2. CMake & build the project

- Linux, GCC:

```
cmake -DCMAKE_C_COMPILER:FILEPATH=/bin/gcc-10 -DCMAKE_CXX_COMPILER:FILEPATH=/bin/g++-10 CMakeLists.txt
cmake --build . --config Debug --target all -- -j [number of core]
```

- Linux, Clang:

```
cmake -DCMAKE_C_COMPILER:FILEPATH=/bin/clang-12 -DCMAKE_CXX_COMPILER:FILEPATH=/bin/clang++-12 CMakeLists.txt
cmake --build . --config Debug --target all -- -j [number of core]
```

- Windows, MSVC

Using PowerShell,

```
choco install vswhere
$loc = vswhere -latest -property installationPath
cmd /k "${loc}\Common7\Tools\VsDevCmd.bat"
for /f "delims=" %a in ('vswhere -latest -property installationPath') do (set LOC=%a)
set LOC="%LOC%\COMMON7\IDE\COMMONEXTENSIONS\MICROSOFT\CMAKE\CMake\bin\cmake.exe"
%LOC% -G "Ninja" .
```
