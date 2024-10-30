cmake_minimum_required(VERSION 3.5)

project(SunCAD VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools Test OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Core5Compat Test OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS 3DCore 3DExtras 3DInput 3DRender)

# Find OpenCASCADE package
find_package(OpenCASCADE REQUIRED)
if(OpenCASCADE_FOUND)
	message(STATUS "OpenCASCADE found")
	message(STATUS "OpenCASCADE include directory: ${OpenCASCADE_INCLUDE_DIR}")
	message(STATUS "OpenCASCADE binary directory: ${OpenCASCADE_BINARY_DIR}")
else()
	message(FATAL_ERROR "OpenCASCADE not found")
endif()

####################
# OpenGL
####################

# Find OpenGL package
find_package(OpenGL REQUIRED)
if(OpenGL_FOUND)
	message(STATUS "OpenGL found")
	message(STATUS "OpenGL include directory: ${OPENGL_INCLUDE_DIR}")
	message(STATUS "OpenGL libraries: ${OPENGL_LIBRARIES}")
else()
	message(FATAL_ERROR "OpenGL not found")
endif()

add_subdirectory(deps)
add_subdirectory(src)
add_subdirectory(tests)
