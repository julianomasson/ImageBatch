cmake_minimum_required(VERSION 3.14)
project(ImageBatch)

add_definitions(/openmp)

# wxWidgets
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS html core base REQUIRED)
include(${wxWidgets_USE_FILE})

# OpenCV
find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME}  src/Resource.rc
				src/resource.h
				src/App.h
				src/App.cpp
				src/MainFrame.h
				src/MainFrame.cpp
				src/Operation.h
				src/ResizePanel.h
				src/ResizePanel.cpp
				src/RenamePanel.h
				src/RenamePanel.cpp
				src/CropPanel.h
				src/CropPanel.cpp)

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

add_definitions(-DNOMINMAX
		-D_SCR_SECURE_NO_WARNINGS
		-D_CRT_SECURE_NO_WARNINGS)

# INSTALL
INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

# Install the OpenCV dependency
INSTALL(FILES "${OpenCV_DIR}/x64/vc15/bin/opencv_world455.dll" DESTINATION bin)

# send the needed microsoft libraries
include (InstallRequiredSystemLibraries)

#
# CPACK macros below here
#
set (CPACK_PACKAGE_NAME "ImageBatch")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "Image utility software")
set (CPACK_PACKAGE_VERSION "0.0.1")
set (CPACK_PACKAGE_VERSION_MAJOR "0")
set (CPACK_PACKAGE_VERSION_MINOR "0")
set (CPACK_PACKAGE_VERSION_PATCH "1")
set (CPACK_PACKAGE_INSTALL_DIRECTORY "ImageBatch")
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set (CPACK_NSIS_MODIFY_PATH "ON")

# Must be after the last CPACK macros
include(CPack)