cmake_minimum_required(VERSION 3.14)

project(QtEmacsKeyThemePlugin LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui REQUIRED)

add_library(QtEmacsKeyThemePlugin SHARED
  emacskeytheme.json
  emacskeythemeplugin.cpp
  emacskeythemeplugin.h
)

target_link_libraries(QtEmacsKeyThemePlugin
  PRIVATE
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::GuiPrivate
)

target_compile_definitions(QtEmacsKeyThemePlugin PRIVATE QTEMACSKEYTHEME_LIBRARY)
