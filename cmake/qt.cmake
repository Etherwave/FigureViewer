# -------------- Qt 路径与包查找 --------------
if(NOT QT_PATH)
    set(QT_PATH "D:/code_tools/qt/install/6.10.1/mingw_64")
endif()
list(APPEND CMAKE_PREFIX_PATH "${QT_PATH}")
find_package(Qt6 REQUIRED COMPONENTS Core Widgets OpenGLWidgets)

# 把 Qt 库列表存到变量，主脚本直接链接
set(QT_LIBS Qt6::Core Qt6::Widgets Qt6::OpenGLWidgets)

set(CMAKE_AUTOMOC ON) # 启用 MOC 自动处理
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)