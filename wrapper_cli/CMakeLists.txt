cmake_minimum_required(VERSION 3.15)
project(NelderMid_CLI)

if(CMAKE_GENERATOR MATCHES "Visual Studio 16|Visual Studio 17")
    message(STATUS "Сборка через Visual Studio 2019/2022 - поддерживается.")
elseif(CMAKE_GENERATOR MATCHES "Visual Studio")
    message(FATAL_ERROR "Требуется Visual Studio 2019 (v16) или выше! Текущий генератор: ${CMAKE_GENERATOR}")
else()
    message(FATAL_ERROR "Проект поддерживает только сборку через Visual Studio!")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc") 
set(CMAKE_CXX_STANDARD 17) 

file(GLOB SOURCES_lib "../dll/src/*.cpp" )
file(GLOB HEADERS_lib "../dll/include/*.h") 

include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(nlohmann_json)

add_library(NelderMid_lib SHARED ${SOURCES_lib})
target_include_directories(NelderMid_lib PUBLIC "../dll/include")
target_link_libraries(NelderMid_lib PRIVATE nlohmann_json::nlohmann_json)

#Сборка managed-обёртки
add_library(NelderMid_cli SHARED
    manager_expression_tree.cpp
    manager_expression_tree.h
)
target_include_directories(NelderMid_cli PUBLIC "../dll/include" .)
target_link_libraries(NelderMid_cli PRIVATE NelderMid_lib nlohmann_json::nlohmann_json)

# Ключевые настройки для CLI:
target_compile_options(NelderMid_cli PRIVATE /clr)
set_target_properties(NelderMid_cli PROPERTIES
    COMMON_LANGUAGE_RUNTIME ""
    VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.8"
    DOTNET_TARGET_FRAMEWORK_VERSION "v4.8"
)

target_include_directories(NelderMid_cli PUBLIC "../dll/include"
                            "C:/Program Files (x86)/Reference Assemblies/Microsoft/Framework/.NETFramework/v4.8" #Здесь указать адрес на заголовки .Net
)
target_link_libraries(NelderMid_cli PRIVATE NelderMid_lib)

target_compile_options(NelderMid_cli PRIVATE /clr)

if(WIN32)
    target_compile_definitions(NelderMid_lib PRIVATE NELDERMID_EXPORTS)
endif()