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
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  set(CMAKE_CXX_STANDARD 14) # C++14...
  set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
  set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11
elseif (WIN32 AND MSVC)  
  message("Microsoft Visual Compiler Build")
  set( PLATFORM "windows")
  set(CMAKE_PREFIX_PATH "$ENV{QT_DIR}")
  add_definitions(
      -DNOMINMAX # https://support.microsoft.com/en-gb/help/143208/prb-using-stl-in-windows-program-can-cause-min-max-conflicts
  )
  add_compile_options(
      /MP # https://msdn.microsoft.com/en-us/library/bb385193.aspx
  )
endif()

# Header and sources
set(ALGORITHMS_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(ALGORITHMS_HEADERS ${ALGORITHMS_INCLUDE_DIR}/algorithms/sort.h
                       ${ALGORITHMS_INCLUDE_DIR}/algorithms/graph.h)
set(ALGORITHMS_SOURCES ${PROJECT_SOURCE_DIR}/src/main.cpp)

# Header and sources for gui
set(ALGORITHMS_GUI_HEADERS ${ALGORITHMS_INCLUDE_DIR}/gui/mainwindow.h
                           ${ALGORITHMS_INCLUDE_DIR}/gui/renderarea.h
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

# Algorithms gui lib
add_library(algui STATIC ${ALGORITHMS_GUI_HEADERS} ${ALGORITHMS_GUI_HEADERS_MOC} ${ALGORITHMS_GUI_FORMS_MOC} ${ALGORITHMS_GUI_SOURCES})
target_include_directories(algui PUBLIC ${ALGORITHMS_INCLUDE_DIR} ${ALGORITHMS_INCLUDE_DIR}/gui)
target_link_libraries(algui PUBLIC Qt5::Core Qt5::Widgets )

# Project related commands
add_executable(algorithms ${ALGORITHMS_SOURCES})
target_link_libraries(algorithms algui)

# Testing
enable_testing()

add_executable(algorithms-test ${PROJECT_SOURCE_DIR}/src/test/main.cpp)
target_include_directories(algorithms-test PUBLIC ${ALGORITHMS_INCLUDE_DIR})
#add_test(algorithms-test)


