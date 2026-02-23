# cmake/auto.cmake

# set(LOCAL_TARGET  QtWidgetsDemo)  # 目标名
# set(LOCAL_TYPE    EXECUTABLE)     # EXECUTABLE | SHARED | STATIC
# set(LOCAL_SUBDIR    widgets)        
# set(LOCAL_INC_DIR    widgets)
# set(LOCAL_LIB_DIR    ${QT_LIBS} CCEWidgets)
# set(LOCAL_WIN32_GUI TRUE)         # 想隐藏控制台就设 TRUE

function(make_auto_target)
    # 1. 先编译依赖子目录（如果存在）
    foreach(subdir ${LOCAL_SUBDIR})
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/CMakeLists.txt)
            add_subdirectory(${subdir})
        endif()
    endforeach()

     # 如果调用者没定义就报错
    if(NOT LOCAL_TARGET)
        return()
    endif()
    if(NOT LOCAL_TYPE)
        set(LOCAL_TYPE SHARED)   # 默认动态库
    endif()

    # 2. 自动搜集源/头
    file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
         ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
    file(GLOB_RECURSE HDR CONFIGURE_DEPENDS
         ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
    file(GLOB_RECURSE UI CONFIGURE_DEPENDS
         ${CMAKE_CURRENT_SOURCE_DIR}/include/*.ui)
    file(GLOB_RECURSE QRC CONFIGURE_DEPENDS
         ${CMAKE_CURRENT_SOURCE_DIR}/src/*.qrc)

#    message(STATUS "SRC = ${SRC}")
#    message(STATUS "HDR = ${HDR}")
#    message(STATUS "UI = ${UI}")
#    message(STATUS "QRC = ${QRC}")

    # 3. 创建目标
    if(LOCAL_TYPE STREQUAL EXECUTABLE)
        add_executable(${LOCAL_TARGET} ${SRC} ${HDR} ${UI} ${QRC})
        set_target_properties(${LOCAL_TARGET} PROPERTIES
            AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/include"
        )
        if(WIN32 AND LOCAL_WIN32_GUI)   # 可选：隐藏控制台
            set_target_properties(${LOCAL_TARGET} PROPERTIES WIN32_EXECUTABLE TRUE)
        endif()
    else()
        add_library(${LOCAL_TARGET} ${LOCAL_TYPE} ${SRC} ${HDR} ${UI} ${QRC})
        set_target_properties(${LOCAL_TARGET} PROPERTIES
            AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/include"
        )
    endif()

    # 4. 头文件目录
    target_include_directories(${LOCAL_TARGET} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${LOCAL_INC_DIR})

    # 5. 链接库
    target_link_libraries(${LOCAL_TARGET} PUBLIC
        ${LOCAL_LIB_DIR})

    # 6. 安装
    install(TARGETS ${LOCAL_TARGET} DESTINATION bin)
endfunction()

# 立即调用，保证当前目录变量生效
make_auto_target()