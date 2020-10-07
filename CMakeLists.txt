cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)

message("PROJECT_SOURCE_DIR:    ${CMAKE_SOURCE_DIR}")
message("PROJECT_BINARY_DIR:    ${CMAKE_BINARY_DIR}")
message("CMAKE_BUILD_DIRECTORY: ${CMAKE_BUILD_DIRECTORY}")

message("SDK SOURCE DIR: ${CMAKE_VS_SDK_SOURCE_DIRECTORIES}")
message("SDK INCLUDE DIR: ${CMAKE_VS_SDK_INCLUDE_DIRECTORIES}")
#message("SDK: ${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}")
#message("SDK: ${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}")

set(WINDOWS_VERSION "10")

set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# Project

project("Uniquis"

		VERSION		 1.0.0.0 
		DESCRIPTION  "This Project is cool!" 
		HOMEPAGE_URL https://www.google.de/ 
		LANGUAGES    CXX)

configure_file("Project/Config/Config.in" "../../../Project/Config/Config.h")

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable("Uniquis" WIN32)

file(GLOB_RECURSE SRC_FILES *.h
                            *.cpp
                            "${CMAKE_CURRENT_SOURCE_DIR}/Project/Resources/Uniquis.rc")

list(FILTER 

	SRC_FILES

	EXCLUDE REGEX 

	.*CMakeCXXCompilerId.*)

message("${SRC_FILES}")

target_sources(Uniquis

	           PRIVATE
	           
	           ${SRC_FILES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})

# Dependencies

target_link_libraries("Uniquis" DelayImp
							    ws2_32
							    DXGI
							    D3DCompiler
							    DXCompiler
							    "${CMAKE_SOURCE_DIR}/bin/lib/assimp-vc142-mt.lib"
                                "${CMAKE_SOURCE_DIR}/bin/lib/freetyped.lib")

if(NOT ${WINDOWS_VERSION} EQUAL 10) 

	target_link_libraries("Uniquis" D3D11)

	set(DEFAULT_GRAPHICS_API DirectX11)

else()

	target_link_libraries("Uniquis" D3D12)

	set(DEFAULT_GRAPHICS_API DirectX12)

endif()

# Compile Flags

target_compile_options("Uniquis"

                       PUBLIC 
					   
		               "/std:c++17"
					   "/arch:AVX2")

# Include Directories

target_include_directories("Uniquis"
	
	                       PRIVATE 
	                       
	                       "${PROJECT_SOURCE_DIR}" 

						   "${PROJECT_SOURCE_DIR}/Project/Precompiled Headers"
	                       
						   "${PROJECT_SOURCE_DIR}/bin/Include"
                           "${PROJECT_SOURCE_DIR}/bin/Include/Assimp"
	                       "${PROJECT_SOURCE_DIR}/bin/Include/FreeType"

	                       "${PROJECT_SOURCE_DIR}/res"
	                       
	                       "${PROJECT_SOURCE_DIR}/src" 
	                       "${PROJECT_SOURCE_DIR}/src/h"
						   
						   "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.23.28105/include")

# Files

file(COPY "res/Icons"    DESTINATION "${PROJECT_BINARY_DIR}/res")
file(COPY "res/Shaders"  DESTINATION "${PROJECT_BINARY_DIR}/res")

set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION "${CPACK_PACKAGE_INSTALL_DIRECTORY}/bin/dll")

# Installer

set(CPACK_GENERATOR NSIS)

set(CPACK_NSIS_COMPONENT_INSTALL TRUE)

# Package

set(CPACK_PACKAGE_NAME "Uniquis")

set(CPACK_PACKAGE_FILE_NAME "Uniquis Setup")

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "PACKAGE DESCRIPTION SUMMARY")

set(CPACK_PACKAGE_VENDOR "DEUTSCHLAND GMBH")

set(CPACK_PACKAGE_CONTACT "CONTACT INFORMATION")

set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/Project/Resources/License.txt")

# Version

set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")

set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

# Directories

#set(CPACK_PACKAGE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/Packaging")

set(CPACK_PACKAGE_INSTALL_DIRECTORY "Uniquis")

# Required System Libraries

include(InstallRequiredSystemLibraries)

# Install

install(TARGETS "Uniquis"
	 
	    COMPONENT   "Core"
	    DESTINATION "Installation"

	    RUNTIME)

# Components

set(CPACK_COMPONENTS_ALL "Core")

set(CPACK_NSIS_MODIFY_PATH ON)

# Include CPack

include(CPack)
