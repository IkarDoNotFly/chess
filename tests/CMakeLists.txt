add_subdirectory(googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set (TARGET unit_tests)

add_executable (${TARGET})

target_include_directories (${TARGET} PUBLIC ${INCLUDE_DIR})

target_link_libraries(${TARGET} PUBLIC gtest gtest_main)


target_sources(
    ${TARGET}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/testPoint.cpp
    ${CMAKE_CURRENT_LIST_DIR}/test-Pawn-Path.cpp
    ${CMAKE_CURRENT_LIST_DIR}/test-King-Path.cpp
    ${CMAKE_CURRENT_LIST_DIR}/testCheckboard.cpp
    ${CMAKE_CURRENT_LIST_DIR}/testFigureFactory.cpp
    )


target_sources(
    ${TARGET}
    PRIVATE
    ${SRC_DIR}/Game.cpp
    ${SRC_DIR}/ViewSide.cpp
    ${SRC_DIR}/Chessboard.cpp
    ${SRC_DIR}/Figure.cpp
    ${SRC_DIR}/Point.cpp
    ${SRC_DIR}/Saver.cpp
    ${SRC_DIR}/PathSystem.cpp
    ${SRC_DIR}/FigureFactory.cpp
    )

