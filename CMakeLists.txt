cmake_minimum_required(VERSION 3.12)

project(refactoring)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Clang REQUIRED)
list(APPEND CLANG_INCLUDE_DIRS $ENV{Clang_ROOT}include)
include_directories(${CLANG_INCLUDE_DIRS})

message("${CLANG_INCLUDE_DIRS}")

link_directories(${CLANG_LIBRARY_DIRS})

add_executable(refactoring main.cpp)

target_link_libraries(refactoring
    PRIVATE
    clangTooling
    clangBasic
    clangASTMatchers
    clangAST
    clangFrontend
    clangFrontendTool
    clangDriver
    clangSerialization
    clangParse
    clangSema
    clangAnalysis
    clangEdit
    clangLex
    clangToolingCore
    clangRewrite
    clangRewriteFrontend
    clangStaticAnalyzerFrontend
    clangStaticAnalyzerCheckers
    clangStaticAnalyzerCore
    clangCrossTU
    clangIndex
    clangFormat
    clangToolingInclusions
)

