
set(PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/SonCAD.cc)
set(PROJECT_RESOURCES ${CMAKE_SOURCE_DIR}/resources/SonCAD.qrc)

# Recursively find all source and header files
file(GLOB SUB_DIRECTORY_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*/*.h"
    "${CMAKE_SOURCE_DIR}/src/*/*.cc"
)

list(APPEND PROJECT_SOURCES ${SUB_DIRECTORY_SOURCES})

message(STATUS "PROJECT_SOURCES: " ${PROJECT_SOURCES})

# check code style
include(cpplint)
add_cpplint_target(CpplintCheck ${SUB_DIRECTORY_SOURCES})

# add executable target
qt_add_executable(SonCAD
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ${PROJECT_RESOURCES}
)

if (TARGET CpplintCheck)
    add_dependencies(SonCAD CpplintCheck)
endif()

target_include_directories(SonCAD PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(SonCAD PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(SonCAD PRIVATE SARibbonBar)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SonCAD)
endif()
set_target_properties(SonCAD PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SonCAD
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SonCAD)
endif()
