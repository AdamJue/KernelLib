# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(KernelLib VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加头文件目录
include_directories(include)

# 定义是否导出库的选项
option(KERNELLIB_EXPORT "Build KernelLib as a shared library that exports symbols" ON)

# 添加库
add_library(${PROJECT_NAME} SHARED src/KernelLib.cpp)

# 根据构建类型决定是否添加后缀
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(${PROJECT_NAME} PROPERTIES
            OUTPUT_NAME "${PROJECT_NAME}d"
    )
else()
    set_target_properties(${PROJECT_NAME} PROPERTIES
            OUTPUT_NAME "${PROJECT_NAME}"
    )
endif()

# 设置库的版本和SO版本
set_target_properties(${PROJECT_NAME}  PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME}  PROPERTIES SOVERSION 1)

# 设置Debug和Release的编译器标志
target_compile_definitions(${PROJECT_NAME}
        PRIVATE $<$<CONFIG:DEBUG>:DEBUG_MODE>
    PRIVATE $<$<CONFIG:RELEASE>:NDEBUG>
)

# 设置Debug和Release的编译选项
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (CMAKE_HOST_UNIX)
        target_compile_options(${PROJECT_NAME}
                PRIVATE $<$<CONFIG:DEBUG>:-g>
            PRIVATE $<$<CONFIG:RELEASE>:-O3>
        )
    else ()
        target_compile_options(${PROJECT_NAME}
                PRIVATE $<$<CONFIG:RELEASE>:-O3>
        )
    endif ()
endif ()

# 如果是导出编译，添加宏定义KERNELLIB_EXPORT
if(KERNELLIB_EXPORT)
    target_compile_definitions(${PROJECT_NAME}  PRIVATE KERNELLIB_EXPORT)
endif()

# 安装规则
install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)

# 安装头文件
install(FILES include/KernelLib.h DESTINATION include/ )

# 导出项目名
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}
)

install(EXPORT ${PROJECT_NAME}  FILE "${PROJECT_NAME}Config.cmake" DESTINATION "share/")
