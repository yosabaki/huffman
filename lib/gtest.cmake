set(GOOGLETEST_ROOT gtest/googletest CACHE STRING "Google Test source root")

include_directories(SYSTEM
        ${PROJECT_SOURCE_DIR}/gtest
        ${PROJECT_SOURCE_DIR}/gtest/include
        )

set(GOOGLETEST_SOURCES
        ${PROJECT_SOURCE_DIR}/gtest/gtest-all.cc
        ${PROJECT_SOURCE_DIR}/gtest/gtest_main.cc
        ${PROJECT_SOURCE_DIR}/gtest/gtest.h
        )

foreach(_source ${GOOGLETEST_SOURCES})
    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach()

add_library(gtest ${GOOGLETEST_SOURCES})

