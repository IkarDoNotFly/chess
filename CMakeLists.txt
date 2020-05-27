cmake_minimum_required (VERSION 3.10)
project (Chess LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)

set (LIB_NAME archive)
set (RUN_NAME chess)
set (INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (SRC_DIR ${PROJECT_SOURCE_DIR}/src)

add_executable (${RUN_NAME})

target_include_directories (${RUN_NAME} PUBLIC ${INCLUDE_DIR})

include (CTest)

if (BUILD_TESTING)
    add_subdirectory (tests)
endif ()

add_subdirectory (src)
