cmake_minimum_required(VERSION 4.1)

set(PROJECT_NAME "FigureViewer")
set(PROJECT_VERSION "1.0.0")
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES C CXX)

# 设置构建类型
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# ========================================================================
# GUI 应用程序
# ========================================================================



# c++ define and qt define
include(${CMAKE_SOURCE_DIR}/cmake/base.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/qt.cmake)
#include(${CMAKE_SOURCE_DIR}/cmake/opengl.cmake)

# 给auto.cmake 传参

#set(LOCAL_SUBDIR engine gui)
set(LOCAL_TARGET  utils)  # 目标名
set(LOCAL_TYPE    SHARED)     # EXECUTABLE | SHARED | STATIC
# set(LOCAL_SUBDIR    widgets)
#set(LOCAL_INC_DIR    widgets)
#set(LOCAL_INC_DIR    ${Qt5Gui_INCLUDE_DIRS} $)
#set(LOCAL_INCLUDE_DIR    ${QT_INC_DIRS})
set(LOCAL_INC_DIR    ${QT_INCLUDE_DIR})
set(LOCAL_LIB_DIR    ${QT_LIBS}) # glfw3 opengl32 gdi32user32 shell32
# set(LOCAL_WIN32_GUI TRUE)         # 想隐藏控制台就设 TRUE

include(${CMAKE_SOURCE_DIR}/cmake/auto.cmake)   # 一键生成

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        "${GLFW_LIB_DIR}/glfw3.dll"
#        $<TARGET_FILE_DIR:${PROJECT_NAME}>
#)

# ========================================================================
# 包配置
# ========================================================================

# 设置包信息
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Code Context Explorer")
set(CPACK_PACKAGE_VENDOR "Your Company")
set(CPACK_PACKAGE_CONTACT "contact@example.com")

set(CPACK_GENERATOR "ZIP;NSIS")
set(CPACK_NSIS_MODIFY_PATH ON)

include(CPack)