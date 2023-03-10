cmake_minimum_required(VERSION 3.10)
project(ConnectInternet VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(ConnectInternet connect_internet.cpp)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

target_link_libraries(ConnectInternet PUBLIC cpr::cpr)