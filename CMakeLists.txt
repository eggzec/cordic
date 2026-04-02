cmake_minimum_required(VERSION 3.10)

project(cordic
    VERSION 0.1.0
    LANGUAGES C
)

# ----------------------------
# Library sources
# ----------------------------

set(CORDIC_SRC
    src/cordic.c
)

# ----------------------------
# Static library
# ----------------------------

add_library(cordic STATIC ${CORDIC_SRC})

target_include_directories(cordic
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(cordic PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 0
)

# ----------------------------
# Shared library
# ----------------------------

add_library(cordic_shared SHARED ${CORDIC_SRC})

target_include_directories(cordic_shared
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(cordic_shared PROPERTIES
    OUTPUT_NAME cordic
    VERSION ${PROJECT_VERSION}
    SOVERSION 0
)

# ----------------------------
# Installation
# ----------------------------

install(
    FILES src/cordic.h
    DESTINATION include
)

install(
    TARGETS cordic cordic_shared
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# ----------------------------
# Tests
# ----------------------------

option(CORDIC_BUILD_TESTS "Build C tests" ON)

if(CORDIC_BUILD_TESTS)

    enable_testing()

    add_executable(test_cordic
        tests/test_cordic.c
    )

    target_link_libraries(test_cordic
        cordic
        $<$<NOT:$<PLATFORM_ID:Windows>>:m>
    )

    add_test(
        NAME cordic_tests
        COMMAND test_cordic
    )

endif()

message(STATUS "CORDIC C library CMake setup complete.")
