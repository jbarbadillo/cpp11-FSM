# Main header: Project name & Configuration
# ------------------------------------------------------------------------------------------------------
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11 )

SET(PROJ_MAIN_NAME "FSM")
PROJECT(${PROJ_MAIN_NAME} CXX)

# Configuration types
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
IF(DEFINED CMAKE_BUILD_TYPE AND CMAKE_VERSION VERSION_GREATER "2.8")
  SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})
ENDIF()

#Install binaries

# Configure variables
# ------------------------------------------------------------------------------------------------------

# Paths
SET(CMAKE_MODULE_PATH           "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
SET(LIBRARY_OUTPUT_PATH          ${PROJECT_BINARY_DIR}/bin                   CACHE PATH "Library output" FORCE)
SET(EXECUTABLE_OUTPUT_PATH       ${PROJECT_BINARY_DIR}/bin                   CACHE PATH "Executable output" FORCE)
SET(${PROJ_MAIN_NAME}_PATH_MAIN  ${CMAKE_SOURCE_DIR}                         CACHE PATH "This directory contains initial Path")
SET(${PROJ_MAIN_NAME}_PATH_LIBS  ${PROJECT_BINARY_DIR}/gen                   CACHE PATH "This directory contains all libs")
SET(${PROJ_MAIN_NAME}_PATH_EXE   ${PROJECT_BINARY_DIR}/gen                   CACHE PATH "This directory contains executables")
SET(${PROJ_MAIN_NAME}_PATH_DATA  ${${PROJ_MAIN_NAME}_PATH_MAIN}/extras/data/ CACHE PATH "This directory contains all DATA and RESOURCES")

#SET(GTEST_PATH 			${ALRN_PATH}/../thirdparties/googletest-master 	CACHE PATH "Path for google test")

# Build type
#IF(TARGET_PLATFORM STREQUAL TARGET_WIN32)
#  SET(${PROJ_MAIN_NAME}_LIB_TYPE "STATIC" CACHE STRING "Choose STATIC or SHARED to generate libraries" FORCE)
#ELSEIF(TARGET_PLATFORM STREQUAL TARGET_LINUX)
#  SET(${PROJ_MAIN_NAME}_LIB_TYPE "SHARED" CACHE STRING "Choose STATIC or SHARED to generate libraries" FORCE)
#ELSE()
#   MESSAGE(FATAL_ERROR "ERROR ${PROJ_MAIN_NAME}_LIB_TYPE")
#ENDIF()

add_definitions(-std=c++11)
#enable_testing()

# Configuration current project
# ------------------------------------------------------------------------------------------------------

# Project Logic
# ------------------------------------------------------------------------------------------------------
IF(NOT TARGET_PLATFORM STREQUAL TARGET_NONE)


  ######################################################################################
  # ADD SUB FOLDERS
  ######################################################################################
   ADD_SUBDIRECTORY(modules)
   #ADD_SUBDIRECTORY(tests)


ELSE()
  message(FATAL_ERROR " TARGET no autodetected. Please, select a TARGET manually. ")
ENDIF()

#add configuration file Config.cmake.in
