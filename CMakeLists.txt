cmake_minimum_required(VERSION 3.14)
project(ImageBatch)

add_definitions(/openmp)

# wxWidgets
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS html core base REQUIRED)
include(${wxWidgets_USE_FILE})

# OpenCV
find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} src/App.h
				src/App.cpp
				src/MainFrame.h
				src/MainFrame.cpp
				src/Operation.h
				src/ResizePanel.h
				src/ResizePanel.cpp
				src/RenamePanel.h
				src/RenamePanel.cpp)

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

add_definitions(-DNOMINMAX
		-D_SCR_SECURE_NO_WARNINGS
		-D_CRT_SECURE_NO_WARNINGS)
