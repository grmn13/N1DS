cmake_minimum_required(VERSION 3.10)

# 1. Project Name
project(NetworkIDS VERSION 1.0 LANGUAGES CXX)

# 2. Set C++ Standard (C++17 is great for modern features like std::filesystem or string_view)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. Find libpcap
# This tells CMake to look for pcap headers and library files on your system
find_library(PCAP_LIB pcap)
if(NOT PCAP_LIB)
    message(FATAL_ERROR "libpcap not found! Please install it (e.g., sudo apt install libpcap-dev)")
endif()

# 4. Include Directories
# This makes it so you can use #include "parser.hpp" instead of #include "../include/parser.hpp"
include_directories(include)

# 5. Define Source Files
# List all your implementation files here
set(SOURCES 
    src/main.cpp 
    src/parser.cpp 
    src/packet_handler.cpp
    src/net_manager.cpp
)

# 6. Create the Executable
add_executable(my_nids ${SOURCES})

# 7. Link libpcap to your executable
target_link_libraries(my_nids ${PCAP_LIB})
