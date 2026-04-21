cmake_minimum_required(VERSION 3.14)
project(BinaryTreeAlgorithm)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(cpp-terminal)

find_package(ICU REQUIRED COMPONENTS uc i18n)

add_executable(BinaryTreeAlgorithm main.cpp)

target_link_libraries(BinaryTreeAlgorithm PUBLIC
    ICU::uc
    ICU::i18n
    cpp-terminal
)