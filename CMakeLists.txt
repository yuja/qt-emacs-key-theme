cmake_minimum_required(VERSION 3.14)

project(QtEmacsKeyThemePlugin LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_QT5 "Forcibly build against Qt5")
option(USE_QT6 "Forcibly build against Qt6")
if(USE_QT5 AND USE_QT6)
  message(FATAL_ERROR "Both USE_QT5 and USE_QT6 are set.")
endif()
if(USE_QT5)
  find_package(Qt5 5.15 REQUIRED COMPONENTS Gui Widgets)
elseif(USE_QT6)
  find_package(Qt6 REQUIRED COMPONENTS Gui Widgets)
else()
  find_package(Qt5 5.15 COMPONENTS Gui Widgets)
  if(NOT Qt5_FOUND)
    find_package(Qt6 REQUIRED COMPONENTS Gui Widgets)
  endif()
endif()

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
    Qt::Gui
    Qt::GuiPrivate
    Qt::Widgets
)

target_compile_definitions(QtEmacsKeyThemePlugin PRIVATE QTEMACSKEYTHEME_LIBRARY)

set_target_properties(QtEmacsKeyThemePlugin
  PROPERTIES
    OUTPUT_NAME emacskey
)

# https://bugreports.qt.io/browse/QTBUG-51900
get_target_property(QT_QMAKE_EXECUTABLE Qt::qmake LOCATION)
execute_process(
  COMMAND ${QT_QMAKE_EXECUTABLE} -query QT_INSTALL_PLUGINS
  OUTPUT_VARIABLE QT_INSTALL_PLUGINS
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
install(TARGETS QtEmacsKeyThemePlugin
  LIBRARY DESTINATION "${QT_INSTALL_PLUGINS}/platformthemes"
)
