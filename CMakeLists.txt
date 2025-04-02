cmake_minimum_required(VERSION 3.10)  
project(NelderMead_DLL)

add_library(NelderMead SHARED src/node_classes.cpp src/classes.cpp src/create_tree.cpp src/checking_func.cpp src/infen_expr_to_rpn.cpp src/operators_func.cpp src/rpn_expr_to_tree.cpp src/core_api.cpp)

target_include_directories(NelderMead PUBLIC include)

# Для Windows: определяем макрос MYLIBRARY_EXPORTS
if(WIN32)
    target_compile_definitions(NelderMead PRIVATE MYLIBRARY_EXPORTS)
endif()

