cmake_minimum_required(VERSION 3.7.2)

project(algorithms C CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

# Platform dependent config flags and paths
if (UNIX)
  message("Linux Build")
  set( PLATFORM "linux")
#  add_definitions(-DLINUX)
  add_compile_options(
      -m64 # 64 bits build flag
  )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  set(CMAKE_CXX_STANDARD 14) # C++14...
  set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
  set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11
elseif (WIN32 AND MSVC)  
  message("Microsoft Visual Compiler Build")
  set( PLATFORM "windows")
  set(CMAKE_PREFIX_PATH "$ENV{QT_DIR}" CACHE PATH "Qt root directory")
  add_definitions(
      -DNOMINMAX # https://support.microsoft.com/en-gb/help/143208/prb-using-stl-in-windows-program-can-cause-min-max-conflicts
  )
  add_compile_options(
      /MP # https://msdn.microsoft.com/en-us/library/bb385193.aspx
      /EHsc
  )
endif()

# Header and sources
set(ROOT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(ALGORITHMS_INCLUDE_DIR ${ROOT_INCLUDE_DIR}/algorithms)
set(COMMON_INCLUDE_DIR ${ROOT_INCLUDE_DIR}/common)
set(ALGORITHMS_HEADERS ${ALGORITHMS_INCLUDE_DIR}/sort.h
                       ${ALGORITHMS_INCLUDE_DIR}/graph.h
                       ${ALGORITHMS_INCLUDE_DIR}/algorithms_global.h
                       ${COMMON_INCLUDE_DIR}/common.h
                       )
set(ALGORITHMS_SOURCES ${PROJECT_SOURCE_DIR}/src/graph.cpp
                       )

# Header and sources for gui
set(ALGORITHMS_GUI_INCLUDE_DIR ${ROOT_INCLUDE_DIR}/gui)
set(ALGORITHMS_GUI_HEADERS ${ALGORITHMS_GUI_INCLUDE_DIR}/mainwindow.h
                           ${ALGORITHMS_GUI_INCLUDE_DIR}/renderarea.h
                           ${ALGORITHMS_GUI_INCLUDE_DIR}/algorithms_gui_global.h
                           )
set(ALGORITHMS_GUI_SOURCES ${PROJECT_SOURCE_DIR}/src/gui/mainwindow.cpp
                           ${PROJECT_SOURCE_DIR}/src/gui/renderarea.cpp
                           )
set(ALGORITHMS_GUI_FORMS ${PROJECT_SOURCE_DIR}/forms/mainwindow.ui
                         ${PROJECT_SOURCE_DIR}/forms/renderarea.ui
                         )

# Qt related configuration
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Qt packages
find_package(Qt5Core)
find_package(Qt5Widgets)
qt5_wrap_ui(ALGORITHMS_GUI_FORMS_MOC ${ALGORITHMS_GUI_FORMS})
qt5_wrap_cpp(ALGORITHMS_GUI_HEADERS_MOC ${ALGORITHMS_GUI_HEADERS})

# Algorithms lib
add_library(algorithms-lib SHARED ${ALGORITHMS_HEADERS} ${ALGORITHMS_SOURCES})
target_include_directories(algorithms-lib PUBLIC ${ROOT_INCLUDE_DIR} ${ALGORITHMS_INCLUDE_DIR})
target_compile_definitions(algorithms-lib PRIVATE BUILDING_ALGORITHMS_LIBRARY)

# Algorithms gui
add_library(algorithms-gui SHARED ${ALGORITHMS_GUI_HEADERS} ${ALGORITHMS_GUI_SOURCES}
                                  ${ALGORITHMS_GUI_HEADERS_MOC} ${ALGORITHMS_GUI_FORMS_MOC} )
target_include_directories(algorithms-gui PUBLIC ${ROOT_INCLUDE_DIR} ${ALGORITHMS_GUI_INCLUDE_DIR})
target_link_libraries(algorithms-gui PUBLIC Qt5::Core Qt5::Widgets algorithms-lib )
target_compile_definitions(algorithms-gui PRIVATE BUILDING_ALGORITHMS_GUI_LIBRARY)

# Project related commands
add_executable(algorithms ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(algorithms algorithms-gui)

# Testing
enable_testing()

add_executable(algorithms-test ${PROJECT_SOURCE_DIR}/src/test/main.cpp)
target_include_directories(algorithms-test PUBLIC ${ROOT_INCLUDE_DIR})
#add_test(algorithms-test)


