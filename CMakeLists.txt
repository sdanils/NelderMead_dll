cmake_minimum_required(VERSION 3.10)  
project(NelderMead_DLL)

file(GLOB SOURCES "src/*.cpp")

file(GLOB HEADERS "include/*.h")

add_library(NelderMead SHARED ${SOURCES} ${HEADERS})

target_include_directories(NelderMead PUBLIC include)

# Для Windows: определяем макрос MYLIBRARY_EXPORTS
if(WIN32)
    target_compile_definitions(NelderMead PRIVATE NELDERMID_EXPORTS)
endif()

