cmake_minimum_required(VERSION 3.10)  
project(NelderMead_DLL)

set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp" )
file(GLOB HEADERS "include/*.h") 
file(GLOB WRAPPER "wrapper.cxx")

# Загружаем nlohmann/json из GitHub
include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0  # Версия
)

FetchContent_MakeAvailable(nlohmann_json)

add_library(NelderMead SHARED ${SOURCES} ${HEADERS} ${WRAPPER})

target_include_directories(NelderMead PUBLIC include)

target_link_libraries(NelderMead PRIVATE nlohmann_json::nlohmann_json)

# Для Windows
if(WIN32)
    target_compile_definitions(NelderMead PRIVATE NELDERMID_EXPORTS)
    target_compile_options(NelderMead PRIVATE /clr)
    target_link_options(NelderMead PRIVATE /CLRIMAGETYPE:IJW)
    set_target_properties(NelderMead PROPERTIES SUFFIX ".dll" PREFIX "")
endif()
