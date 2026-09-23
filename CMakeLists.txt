cmake_minimum_required(VERSION 3.16)

project(inventory-system VERSION 0.1 LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Source files
set(SOURCES
    src/Armor.cpp
    src/Item.cpp
    src/Potion.cpp
    src/Weapon.cpp
    src/main.cpp
)

# Header files (explicitly listed so they appear in IDE Solution Explorers)
set(HEADERS
    headers/Armor.hpp
    headers/Character.hpp
    headers/Enums.hpp
    headers/Item.hpp
    headers/Potion.hpp
    headers/Weapon.hpp
)

# Executable target
add_executable(inventory-system ${SOURCES} ${HEADERS})

# Include directory for headers
target_include_directories(inventory-system PRIVATE headers)

# Compiler warnings
if (MSVC)
    target_compile_options(inventory-system PRIVATE /W4 /permissive-)
else()
    target_compile_options(inventory-system PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Visual Studio IDE configuration
# Set inventory-system as the default startup project when opened in Visual Studio
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT inventory-system)

if (MSVC)
    set_target_properties(inventory-system PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    )
endif()

