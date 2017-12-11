SET(PROJ_NAME fsm_test)
PROJECT(${PROJ_NAME})

# Include directories with headers
#---------------------------------------------------#
INCLUDE_DIRECTORIES( ${${PROJ_MAIN_NAME}_PATH_MAIN}/modules/state-machine/include )

# Source
#---------------------------------------------------#
FILE(GLOB ${PROJ_NAME}_SRC
    "src/*.cpp"
)

# Link libraries with Project
#---------------------------------------------------#
LINK_DIRECTORIES( ${${PROJ_MAIN_NAME}_PATH_LIBS} )

# Create Library
#---------------------------------------------------#
ADD_EXECUTABLE(${PROJ_NAME} ${${PROJ_NAME}_HEADERS} ${${PROJ_NAME}_SRC} )

TARGET_LINK_LIBRARIES(${PROJ_NAME} libgtest)
TARGET_LINK_LIBRARIES(${PROJ_NAME} state_machine )

add_test(NAME ${PROJ_NAME} COMMAND ${PROJ_NAME})
