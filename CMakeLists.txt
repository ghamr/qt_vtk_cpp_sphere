cmake_minimum_required(VERSION 3.16)

project(BallMover)

set(CMAKE_CXX_STANDARD 17)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Find VTK
find_package(VTK REQUIRED)

if (NOT VTK_FOUND)
    message(FATAL_ERROR "VTK not found. Please set the VTK_DIR variable to the location of VTKConfig.cmake")
endif()

# Include VTK directories
include_directories(${VTK_INCLUDE_DIRS})

# Add the UI files
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

# Link VTK libraries
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets ${VTK_LIBRARIES})
