cmake_minimum_required(VERSION 3.10)  
project(NelderMead_CLI LANGUAGES CXX)

# Включаем поддержку C++/CLI
set(CMAKE_CXX_CLR_TARGET "net48")
enable_language(CXX_CLR)

file(GLOB SOURCES_lib "../dll/src/*.cpp" )
file(GLOB HEADERS_lib "../dll/include/*.h") 

include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0  
)
FetchContent_MakeAvailable(nlohmann_json)
add_library(NelderMead_lib STATIC ${SOURCES_lib} ${HEADERS_lib})
target_include_directories(NelderMead_lib PUBLIC ../dll/include)
target_link_libraries(NelderMead_lib PRIVATE nlohmann_json::nlohmann_json)

#Сборка managed-обёртки
add_library(NelderMead_cli SHARED
    manager_expression_tree.cpp
    manager_expression_tree.h
)
target_include_directories(NelderMead_cli PUBLIC ../dll/include .)
target_link_libraries(NelderMead_cli PRIVATE NelderMead_lib)

# Ключевые настройки для CLI:
target_compile_options(NelderMead_cli PRIVATE /clr)
set_target_properties(NelderMead_cli PROPERTIES
    COMMON_LANGUAGE_RUNTIME ""
    VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.8"
    DOTNET_TARGET_FRAMEWORK_VERSION "v4.8"
)

if(WIN32)
    target_compile_definitions(NelderMead_lib PRIVATE NELDERMEAD_LIB_EXPORTS)
endif()
