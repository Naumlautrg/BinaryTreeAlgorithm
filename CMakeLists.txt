cmake_minimum_required(VERSION 3.14)
project(BinaryTreeAlgorithm)

set(CMAKE_CXX_STANDARD 20)

find_package(ICU REQUIRED COMPONENTS uc i18n)
find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(BinaryTreeAlgorithm main.cpp)

target_link_libraries(BinaryTreeAlgorithm PUBLIC
    ICU::uc
    ICU::i18n
    cpr::cpr
    nlohmann_json::nlohmann_json
)