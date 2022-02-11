cmake_minimum_required(VERSION 3.14)

project(QtEmacsKeyThemePlugin LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Gui Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui Widgets REQUIRED)

add_library(QtEmacsKeyThemePlugin SHARED
  emacskey.h
  emacskeytheme.cpp
  emacskeytheme.h
  emacskeytheme.json
  emacskeythemeplugin.cpp
  emacskeythemeplugin.h
  emacskeywidgethandler.cpp
  emacskeywidgethandler.h
  proxytheme.cpp
  proxytheme.h
)

target_link_libraries(QtEmacsKeyThemePlugin
  PRIVATE
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::GuiPrivate
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_compile_definitions(QtEmacsKeyThemePlugin PRIVATE QTEMACSKEYTHEME_LIBRARY)

set_target_properties(QtEmacsKeyThemePlugin
  PROPERTIES
    OUTPUT_NAME emacskey
)

# https://bugreports.qt.io/browse/QTBUG-51900
get_target_property(QT_QMAKE_EXECUTABLE Qt5::qmake LOCATION)
execute_process(
  COMMAND ${QT_QMAKE_EXECUTABLE} -query QT_INSTALL_PLUGINS
  OUTPUT_VARIABLE QT_INSTALL_PLUGINS
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
install(TARGETS QtEmacsKeyThemePlugin
  LIBRARY DESTINATION "${QT_INSTALL_PLUGINS}/platformthemes"
)
