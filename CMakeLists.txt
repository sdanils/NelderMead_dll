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

if(WIN32)
    target_compile_definitions(NelderMead PRIVATE NELDERMEAD_EXPORTS)
    set_target_properties(NelderMead PROPERTIES SUFFIX ".dll" PREFIX "")
endif()

# Сборка совместно с main приложением, для теста внутри библиотеки.

#add_executable(main src/main.cpp)
#target_link_libraries(main PRIVATE NelderMead)
#target_include_directories(main PRIVATE include
#"${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/nlohmann_json-src/include"    )
    
#if(WIN32)
#    set_target_properties(main PROPERTIES SUFFIX ".exe")
#    add_custom_command(TARGET main POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#            $<TARGET_FILE:NelderMead>
#            $<TARGET_FILE_DIR:main>
#    )
#endif()