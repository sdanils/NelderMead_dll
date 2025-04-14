cmake_minimum_required(VERSION 3.10)  
project(NelderMead_DLL)

file(GLOB SOURCES "src/*.cpp")

file(GLOB HEADERS "include/*.h")

# Загружаем nlohmann/json из GitHub
include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0  # Версия
)

FetchContent_MakeAvailable(nlohmann_json)

add_library(NelderMead SHARED ${SOURCES} ${HEADERS})

target_include_directories(NelderMead PUBLIC include)

target_link_libraries(NelderMead PRIVATE nlohmann_json::nlohmann_json)

# Для Windows: определяем макрос MYLIBRARY_EXPORTS
if(WIN32)
    target_compile_definitions(NelderMead PRIVATE NELDERMID_EXPORTS)
endif()

