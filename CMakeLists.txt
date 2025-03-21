cmake_minimum_required(VERSION 3.10)  
project(NelderMead_DLL)

add_library(NelderMead SHARED src/NelderMead.cpp)

target_include_directories(NelderMead PUBLIC include)

# Для Windows: определяем макрос MYLIBRARY_EXPORTS
if(WIN32)
    target_compile_definitions(NelderMead PRIVATE MYLIBRARY_EXPORTS)
endif()

