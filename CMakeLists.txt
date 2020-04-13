cmake_minimum_required(VERSION 3.5)

project(Pomodoro LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

set(CMAKE_PREFIX_PATH /Users/david/Qt/5.14.2/clang_64/lib/cmake)

# /Users/david/Qt/5.14.2/clang_64/lib/cmake/Qt5/Qt5Config.cmake
#set(CMAKE_MODULES_PATH /Users/david/Qt/5.14.2/clang_64/lib/cmake)

find_package(Qt5 COMPONENTS Core Quick Sql REQUIRED)

if(ANDROID)
    add_library(Pomodoro SHARED
      main.cpp
      qml.qrc
    )
else()
    add_executable(Pomodoro
      main.cpp
      qml.qrc
    )
endif()

target_compile_definitions(Pomodoro
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(Pomodoro
  PRIVATE Qt5::Core Qt5::Quick Qt5::Sql)
