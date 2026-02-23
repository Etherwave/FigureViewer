#----------------------------------------------------------
# 1. glad（源码方式加入）
#----------------------------------------------------------
#add_library(glad STATIC
#        ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c
#)
#target_include_directories(glad PUBLIC
#        ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
#)

#----------------------------------------------------------
# 2. glfw3：仅使用官方提供的动态库
#----------------------------------------------------------
set(GLFW_DIR      "D:/code_tools/glfw-3.4.bin.WIN64")
set(GLFW_INCLUDE  "${GLFW_DIR}/include")
set(GLFW_LIB_DIR  "${GLFW_DIR}/lib-mingw-w64")
# 导入库（.dll.a）和真正的动态库（.dll）
set(GLFW_IMPLIB   "${GLFW_LIB_DIR}/libglfw3dll.a")
set(GLFW_DLL      "${GLFW_LIB_DIR}/glfw3.dll")

#add_library(glfw3 SHARED IMPORTED GLOBAL)
#set_target_properties(glfw3 PROPERTIES
#        IMPORTED_LOCATION         "${GLFW_DLL}"
#        IMPORTED_IMPLIB           "${GLFW_IMPLIB}"
#        INTERFACE_INCLUDE_DIRECTORIES "${GLFW_INCLUDE}"
#)
#
##----------------------------------------------------------
## 3. 可执行文件
##----------------------------------------------------------
#add_executable(${PROJECT_NAME}
#        main.cpp
#)
#
#target_link_libraries(${PROJECT_NAME}
#        PRIVATE
#        glad
#        glfw3
#        opengl32      # Windows 自带的 OpenGL 导入库
#        gdi32         # glfw 在 Windows 上依赖的系统库
#        user32
#        shell32
#)
#
## 把 glfw3.dll 复制到跟 exe 同级目录，防止运行时找不到
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        "${GLFW_LIB_DIR}/glfw3.dll"
#        $<TARGET_FILE_DIR:${PROJECT_NAME}>
#)