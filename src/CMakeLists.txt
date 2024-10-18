
set(PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/SonCAD.cc)
set(PROJECT_RESOURCES 
    ${CMAKE_SOURCE_DIR}/src/ResourceUtils.h
    ${CMAKE_SOURCE_DIR}/res/SonCAD.qrc)

# Recursively find all source and header files
file(GLOB SUB_DIRECTORY_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*/*.h"
    "${CMAKE_SOURCE_DIR}/src/*/*.cc"
    "${CMAKE_SOURCE_DIR}/src/*/*/*.h"
    "${CMAKE_SOURCE_DIR}/src/*/*/*.cc"
)

list(APPEND PROJECT_SOURCES ${SUB_DIRECTORY_SOURCES})

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
target_include_directories(SonCAD PRIVATE ${OpenCASCADE_INCLUDE_DIR})

target_link_libraries(SonCAD PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(SonCAD PRIVATE SARibbonBar)
target_link_libraries(SonCAD PRIVATE cxxopts)
target_link_libraries(SonCAD PRIVATE qt${QT_VERSION_MAJOR}advanceddocking)

# Link OpenCASCADE libraries
foreach (LIB ${OpenCASCADE_LIBRARIES})
  target_link_libraries(SonCAD PRIVATE debug ${OpenCASCADE_LIBRARY_DIR}d/${LIB}.lib)
  target_link_libraries(SonCAD PRIVATE optimized ${OpenCASCADE_LIBRARY_DIR}/${LIB}.lib)
endforeach()

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

# Install the target executable/library (SonCAD)
include(GNUInstallDirs)

# Install the executable or runtime (if Windows, RUNTIME is used)
install(TARGETS SonCAD
    BUNDLE DESTINATION .                                # For macOS app bundles (if applicable)
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}         # Shared libraries on Linux/macOS
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}         # Executables and Windows DLLs
)

# Use CMake's built-in shared library suffix variable
file(GLOB OPENCASCADE_BINS "${OpenCASCADE_BINARY_DIR}/*${CMAKE_SHARED_LIBRARY_SUFFIX}")

# Install the OpenCASCADE shared libraries
install(FILES ${OPENCASCADE_BINS}
    DESTINATION ${CMAKE_INSTALL_BINDIR}                 # Install libraries to the library directory
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SonCAD)
endif()
